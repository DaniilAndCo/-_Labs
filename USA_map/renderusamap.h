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
private slots:
    void GetFile();
private:
    int biasX = 170;
    int biasY = 100;
    int sizeRatio = 7;
    QPainter *painter;
    QFile file;
    QJsonObject jObject;
    QMap<QString, double> map;
    void SetPolygonsColors();
    void GetSentiments();
    void SetFontSize(const int&);
    void DrawPolygons() const;
    void GetJsonFromFile();
    void GetPolygonsFromJson();
    QList<QPair<QPolygonF, double>> polygons;
    void paintEvent(QPaintEvent*);
};
#endif // RENDERUSAMAP_H
