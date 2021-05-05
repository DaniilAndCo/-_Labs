/*#include "Reader_Parser.h"

QMap<QString, double> GetDictionaryFromFile(const QString path)
{
    QFile dictionary = QFile(path);
    dictionary.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&dictionary);
    QMap<QString, double> map_;
    while (!in.atEnd())
    {
        auto line = QString(in.readLine());
        auto pair = line.trimmed().split(QLatin1Char(','));
        map_.insert(pair.first(), pair.last().toDouble());
    }
    dictionary.close();
    return map_;
}

QJsonObject GetJsonFromFile(const QString path)
{
    QFile file_ = QFile(path);
    file_.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(file_.readAll());
    file_.close();
    return QJsonObject(doc.object()); //get the jsonObject
}*/
