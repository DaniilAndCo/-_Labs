#include "widget.h"
Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(kWidth_, kHeight_);
    setWindowTitle(tr("Long Live Belarus!"));
    setWindowIcon(QIcon("blr.png"));
    GetCitiesFromFile();
    GetPolygonsFromJson();
    API_handler_ = new QNetworkAccessManager(this);
    GetDataFromAPI();
    update();
}

void Widget::GetCitiesFromFile(){
    QFile file("cities.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString input;
    while (!file.atEnd()){
        input = file.readLine();
        input.remove('\n');
        cities_.push_back(input);
    }
    file.close();
}

double Widget::GetTemperatureFromJson(const QJsonObject& object) const
{
    return object["current"].toObject()["temperature"].toDouble();

}
double Widget::GetPressureFromJson(const QJsonObject& object)
{
    return object["current"]["pressure"].toDouble();
}

long double Widget::TempPressMap(const long double &x, const long double &in_min,
                            const long double &in_max, const long double &out_min, const long double &out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void Widget::GetDataFromAPI()
{  
    for(int i = 0; i < cities_.size(); ++i){
        QEventLoop eventLoop;
        connect(API_handler_, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
        QNetworkRequest request;
        request.setUrl(kAPIUrl + cities_[i]);
        QNetworkReply* reply = API_handler_->get(request);
        eventLoop.exec();
        QJsonDocument document = QJsonDocument::fromJson(((QString) reply->readAll()).toUtf8());
        QJsonObject json = document.object();
        Point_Data infoPoint(QPoint(0, 0), 0, 0);
        infoPoint.point = QPoint(json["location"].toObject()["lon"].toDouble() * kScaleFactor_x + kOffSet_x,
                json["location"].toObject()["lat"].toDouble() * kScaleFactor_y + kOffSet_y);
        infoPoint.temperature = TempPressMap(json["current"].toObject()["temp_c"].toDouble(), -40, 40, 0, 255);
        infoPoint.pressure = TempPressMap(json["current"].toObject()["pressure_mb"].toDouble(), 950, 1050, 0, 255);

        qDebug() << infoPoint.point;
        queue_.push_back(infoPoint);
        delete reply;

    }

}

void Widget::GetPolygonsFromJson()
{
    QFile file = QFile("boundaries.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    auto jObject = QJsonObject(doc.object()); //get the jsonObject

    auto polygons = jObject["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray();
    for (auto polygon : polygons)
    {
        for (auto coords : polygon.toArray())
        {
            polygon_ << QPoint(coords.toArray().first().toDouble() * kScaleFactor_x + kOffSet_x,
                                   coords.toArray().last().toDouble() * kScaleFactor_y + kOffSet_y);
        }
    }
}

void Widget::paintEvent(QPaintEvent*)
{    
    painter_ = new QPainter(this);
    painter_->setPen(Qt::black);
    painter_->drawPolygon(polygon_);


    while(!queue_.empty()){

        Point_Data p = queue_.head();
        queue_.pop_front();
        int x = p.point.x();
        int y = p.point.y();
        int temperature = p.temperature;
        int pressure = p.pressure;


        if(usedPoints_[qMakePair(x + 1, y)] == 0 && polygon_.containsPoint(QPoint(x + 1, y), Qt::OddEvenFill)){
            queue_.push_back(Point_Data(QPoint(x + 1, y), temperature, pressure));
            usedPoints_[qMakePair(x + 1,y)] = true;
        }
        if(usedPoints_[qMakePair(x - 1, y)] == 0 && polygon_.containsPoint(QPoint(x - 1, y), Qt::OddEvenFill)){
            queue_.push_back(Point_Data(QPoint(x - 1, y), temperature, pressure));
            usedPoints_[qMakePair(x - 1, y)] = true;
        }
        if(usedPoints_[qMakePair(x, y + 1)] == 0 && polygon_.containsPoint(QPoint(x, y + 1), Qt::OddEvenFill)){
            queue_.push_back(Point_Data(QPoint(x, y + 1), temperature, pressure));
            usedPoints_[qMakePair(x, y + 1)] = true;
        }
        if(usedPoints_[qMakePair(x, y - 1)] == 0 && polygon_.containsPoint(QPoint(x, y - 1), Qt::OddEvenFill)){
            queue_.push_back(Point_Data(QPoint(x, y - 1), temperature, pressure));
            usedPoints_[qMakePair(x, y - 1)] = true;
        }

        painter_->setPen(QColor(0, temperature, 255 - temperature, 255));
        painter_->drawPoint(x, y);
    }

    delete painter_;
}

Widget::~Widget()
{
}

