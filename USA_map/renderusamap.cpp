#include "renderusamap.h"

RenderUsaMap::RenderUsaMap(QWidget *parent) : QWidget(parent)
{
    resize(1000, 750);

    setWindowTitle(tr("The map of the USA by Daniel Bondarkov"));
    map_ = GetDictionaryFromFile("sentiments.csv");
    GetPolygonsFromJson();
    SetStatesColors();
}

void RenderUsaMap::DrawStates() const
{
    painter_->setPen(Qt::black);
    for (const auto &state : states_)
    {
       state.DrawState(painter_);
    }
}
void RenderUsaMap::GetPolygonsFromJson()
{
    jObject_ = GetJsonFromFile("coords.json");
    keys_ = jObject_.keys();
    for (auto i = 0; i < keys_.size(); ++i)
    {
        states_.push_back(State());
    }
    QPolygonF polygon;
    size_t counter = 0;
    for (const auto &key : keys_)
    {
        for (const auto &i : jObject_[key].toArray())
        {
            polygon.clear();
            auto coordsArray = i.toArray().size() > 1 ? i.toArray() : i.toArray().first().toArray();
            for (const auto &j : coordsArray)
            {
                auto c = QPointF((j.toArray().first().toDouble() + biasX) * sizeRatio,
                                 (biasY - j.toArray().last().toDouble())*sizeRatio);
                polygon << c;
            }
            states_[counter].AddPolygon(polygon);
        }
        ++counter;
    }
}

void RenderUsaMap::SetStatesColors()
{
    QPointF tweetPoint;
    QFile tweets = QFile("tweets.txt");
    tweets.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&tweets);
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
            for (auto &state : states_)
            {
                auto matchTime = time.match(line);
                auto tweet = line.remove(0, matchTime.capturedEnd()).trimmed().toLower();
                state.CalculateProductivity(tweetPoint, tweet, map_);
            }
        }
    }
    tweets.close();
}

void RenderUsaMap::paintEvent(QPaintEvent*)
{
    painter_ = new QPainter(this);
    DrawStates();
    delete painter_;
}

RenderUsaMap::~RenderUsaMap()
{
    if (painter_)
        delete painter_;
}

