#ifndef RENDERUSAMAP_H
#define RENDERUSAMAP_H
#include "State.h"
#include "Reader_Parser.h"
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonArray>
#include <QRegularExpression>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
using namespace std;
class RenderUsaMap : public QWidget
{
    Q_OBJECT

public:
    RenderUsaMap(QWidget *parent = nullptr);
    ~RenderUsaMap();
private:
    size_t biasX = 180;
    size_t biasY = 100;
    size_t sizeRatio = 7;
    QPainter *painter_;
    QFile file_;
    QJsonObject jObject_;
    QMap<QString, double> map_;
    QList<State> states_;
    QList<QString> keys_;
    void GetPolygonsFromJson();
    void SetStatesColors();
    void DrawStates() const;
    void paintEvent(QPaintEvent*);
};
#endif // RENDERUSAMAP_H
