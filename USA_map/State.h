#ifndef STATE_H
#define STATE_H
#include <QPolygonF>
#include <QList>
#include <QMap>
#include <QPainter>
class State
{
private:
    QList<QPolygonF> polygons_;
    double negativity_;
public:
    State();
    ~State();
    void AddPolygon(const QPolygonF&);
    void CalculateProductivity(const QPointF&, const QString&, QMap<QString, double>&);
    void DrawState(QPainter*) const;
};
#endif // STATE_H
