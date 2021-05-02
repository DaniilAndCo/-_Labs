#include "renderusamap.h"
#include <QThread>
RenderUsaMap::RenderUsaMap(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1000, 750);
    setWindowTitle(tr("The map of the USA by Daniel Bondarkov"));
    GetFile();
    GetJsonFromFile();
    GetPolygonsFromJson();
    GetSentiments();
    SetPolygonsColors();
    update();
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
        map.insert(pair.first(), pair.last().toDouble());
    }
    dictionary->close();
    delete dictionary;
}

void RenderUsaMap::GetFile()
{
    file.setFileName("coords.json");
}
void RenderUsaMap::GetJsonFromFile()
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    jObject = QJsonObject(doc.object()); //get the jsonObject
}
void RenderUsaMap::GetPolygonsFromJson()
{
    auto keys = jObject.keys();
    QPolygonF polygon;
    for (auto &key : keys)
    {
        polygon.clear();
        for (const auto &i : jObject[key].toArray())
        {
            auto coordsArray = i.toArray().size() > 1 ? i.toArray() : i.toArray().first().toArray();
            for (const auto &j : coordsArray)
            {
                polygon << QPointF((j.toArray().first().toDouble() + biasX) * sizeRatio, (biasY - j.toArray().last().toDouble())*sizeRatio);
            }
        }
        polygons.push_back(qMakePair(polygon, 0.0));
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
            tweetPoint = QPointF((biasX + matchCoords.captured().split('[').last().split(", ").last().toDouble()) * sizeRatio, (biasY - matchCoords.captured().split('[').last().split(", ").first().toDouble()) * sizeRatio);
            for (auto &polygon : polygons)
            {
                if (polygon.first.containsPoint(tweetPoint, Qt::OddEvenFill))
                {
                    auto matchTime = time.match(line);
                    for (const auto &word : line.remove(0, matchTime.capturedEnd()).trimmed().split(QRegularExpression("\\s+")))
                    {
                        if (map.contains(word.toLower()))
                            polygon.second += map[word.toLower()];
                    }
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
    painter->setPen(Qt::black);
    for (auto i = 1; i < polygons.size(); ++i)
    {
        if (polygons[i].second >= 0)
            painter->setBrush(QColor(qRgb(polygons[i].second * 25, 0, 0)));
        else painter->setBrush(QColor(qRgb(0, 0, polygons[i].second * 25)));
        painter->drawPolygon(polygons[i].first);
    }
}

void RenderUsaMap::paintEvent(QPaintEvent*)
{
    painter = new QPainter(this);
    DrawPolygons();
    delete painter;
}

RenderUsaMap::~RenderUsaMap()
{
    if (painter)
        delete painter;
}
