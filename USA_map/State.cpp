#include "State.h"

State::State() : negativity_(0)
{

}
State::~State()
{

}
void State::AddPolygon(const QPolygonF &new_polygon)
{
    polygons_.push_back(new_polygon);
}
void State::CalculateProductivity(const QPointF &coords, const QString &tweet, QMap<QString, double> &map_)
{
   for (const auto &polygon : polygons_)
   {
       if (polygon.containsPoint(coords, Qt::OddEvenFill) || polygon.containsPoint(coords, Qt::WindingFill))
       {
            foreach (const auto &key, map_.keys())
            {
                if (tweet.contains(key))
                    negativity_ += map_[key];
            }
            break;
       }
   }
}

void State::DrawState(QPainter* painter) const
{
    for (const auto& polygon : polygons_)
    {
        if (negativity_ >= 0)
                   painter->setBrush(QColor(qRgb(negativity_ * 25, 255, 255)));
               else painter->setBrush(QColor(qRgb(255, 255, abs(negativity_) * 25)));
        painter->drawPolygon(polygon);
    }
}
