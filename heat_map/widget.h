#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <QPushButton>
#include <tuple>
#include <QRegularExpression>
#include <QQueue>
#include <QObject>
#include <QDebug>
#include <QPointF>
#include <QPoint>
#include <QPair>
#include <QIcon>
#include <QUrl>
#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QPixmap>
#include <QFile>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QEventLoop>
#include <vector>

using namespace std;


class Widget : public QWidget
{
    Q_OBJECT


private:

    const QString kACCESS_KEY = "0e22b09c086d4baaa16141706212306";
    QString kAPIUrl = "http://api.weatherapi.com/v1/current.json?key=" + kACCESS_KEY + "&q=";

    struct Point_Data
    {
        Point_Data(QPoint point_, long double temperature_, long double pressure_) : point(point_), temperature(temperature_), pressure(pressure_)
        {
        }
        QPoint point;
        long double temperature;
        long double pressure;
    };

    static const size_t kWidth_ = 1000, kHeight_ = 750;
    static const int kScaleFactor_x = 70;
    static const int kOffSet_x = -1550;
    static const int kScaleFactor_y = -100;
    static const int kOffSet_y = 5650;

    QPainter *painter_;
    QNetworkAccessManager *API_handler_;
    QQueue<Point_Data> queue_;
    QStringList cities_;
    QMap<QPair<int, int>, bool> usedPoints_;
    vector<QJsonObject> data_;
    QPolygon polygon_;
    void GetCitiesFromFile();
    double GetTemperatureFromJson(const QJsonObject&) const;
    double GetPressureFromJson(const QJsonObject&);
    long double TempPressMap(const long double &x, const long double&, const long double&, const long double&, const long double&);

    void GetPolygonsFromJson();
    QJsonObject GetJsonFromFile(const QString&) const;

    void paintEvent(QPaintEvent*);
    void GetDataFromAPI();

public:     

    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
