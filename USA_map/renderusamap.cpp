#include "renderusamap.h"
#include <QThread>
RenderUsaMap::RenderUsaMap(QWidget *parent) : QWidget(parent)
{
    resize(1000, 750);
    setWindowTitle(tr("The map of the USA by Daniel Bondarkov"));
    GetJsonFromFile();
    GetPolygonsFromJson();
    GetSentiments();
    SetPolygonsColors();
}

void RenderUsaMap::GetSentiments()
{
    QFile* dictionary = new QFile("sentiments.csv");
    dictionary->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(dictionary);
    while (!in.atEnd())
    {
        auto line = QString(in.readLine());
        auto pair = line.trimmed().split(QLatin1Char(','));
        map_.insert(pair.first(), pair.last().toDouble());
    }
    dictionary->close();
    delete dictionary;
}

void RenderUsaMap::GetJsonFromFile()
{
    file_.setFileName("coords.json");
    file_.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(file_.readAll());
    file_.close();
    jObject_ = QJsonObject(doc.object()); //get the jsonObject
}
void RenderUsaMap::GetPolygonsFromJson()
{
    auto keys = jObject_.keys();
    QPolygonF polygon;
    for (const auto &key : keys)
    {
        polygon.clear();
        for (const auto &i : jObject_[key].toArray())
        {
            auto coordsArray = i.toArray().size() > 1 ? i.toArray() : i.toArray().first().toArray();
            for (const auto &j : coordsArray)
            {
                auto c = QPointF((j.toArray().first().toDouble() + biasX) * sizeRatio, (biasY - j.toArray().last().toDouble())*sizeRatio);
                polygon << c;
            }
        }
        polygons_.push_back(qMakePair(polygon, 0.0));
    }
}

void RenderUsaMap::SetPolygonsColors()
{
    QPointF tweetPoint;
    QFile *tweets = new QFile("tweets.txt");
    tweets->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(tweets);
    QRegularExpression coords(".{1}(-?\\d*\\.?\\d+).{2}(-?\\d*.?\\d+)");
    QRegularExpression time("\\d{2}:\\d{2}:\\d{2}");
    while (!in.atEnd())
    {
        auto line = QString(in.readLine() + "\n");
        auto matchCoords = coords.match(line);
        if (matchCoords.hasMatch())
        {
            tweetPoint = QPointF((biasX + matchCoords.captured().split('[').last().split(", ").last().toDouble()) * sizeRatio,
                                 (biasY - matchCoords.captured().split('[').last().split(", ").first().toDouble()) * sizeRatio);
            for (auto &polygon : polygons_)
            {
                if (polygon.first.containsPoint(tweetPoint, Qt::OddEvenFill))
                {
                    auto matchTime = time.match(line);
                    auto tweet = line.remove(0, matchTime.capturedEnd()).trimmed().toLower().split(QRegularExpression("\\s+"));
                    for (const auto &d : map_)
                    {
                        if (tweet.contains(map_.key(d)))
                            polygon.second += d;
                    }
                    /*for (const auto &word : line.remove(0, matchTime.capturedEnd()).trimmed().split(QRegularExpression("\\s+")))
                    {
                        if (map_.contains(word.toLower()))
                            polygon.second += map_[word.toLower()];
                    }*/
                    break;
                }
            }
        }
    }
    tweets->close();
    delete tweets;
}

void RenderUsaMap::DrawPolygons() const
{
    painter_->setPen(Qt::black);
    for (auto i = 1; i < polygons_.size(); ++i)
    {
        if (polygons_[i].second >= 0)
            painter_->setBrush(QColor(qRgb(polygons_[i].second * 25, 255, 255)));
        else painter_->setBrush(QColor(qRgb(255, 255, abs(polygons_[i].second) * 25)));
        painter_->drawPolygon(polygons_[i].first);
    }
}

void RenderUsaMap::paintEvent(QPaintEvent*)
{
    painter_ = new QPainter(this);
    DrawPolygons();
    delete painter_;
}

RenderUsaMap::~RenderUsaMap()
{
    if (painter_)
        delete painter_;
}
