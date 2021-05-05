#ifndef READER_PARSER_H
#define READER_PARSER_H
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>

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
}

#endif // READER_PARSER_H
