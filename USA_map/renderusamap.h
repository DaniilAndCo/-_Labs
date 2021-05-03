#ifndef RENDERUSAMAP_H
#define RENDERUSAMAP_H
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMap>
#include <QRegularExpression>
using namespace std;
class RenderUsaMap : public QWidget
{
    Q_OBJECT

public:
    RenderUsaMap(QWidget *parent = nullptr);
    ~RenderUsaMap();
private:
    size_t biasX = 170;
    size_t biasY = 100;
    size_t sizeRatio = 7;
    QPainter *painter_;
    QFile file_;
    QJsonObject jObject_;
    QMap<QString, double> map_;
    QList<QPair<QPolygonF, double>> polygons_;
    void SetPolygonsColors();
    void GetSentiments();
    void DrawPolygons() const;
    void GetJsonFromFile();
    void GetPolygonsFromJson();
    void paintEvent(QPaintEvent*);
};
#endif // RENDERUSAMAP_H
