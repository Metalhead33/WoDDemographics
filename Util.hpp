#ifndef UTIL_HPP
#define UTIL_HPP

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

namespace Util
{
void loadFromJSON(QObject& obj, const QJsonObject& json);
void saveToJSON(const QObject& obj, QJsonObject& json);
void saveJson(const QJsonDocument& json);
void loadJson(QJsonDocument& json);
QJsonDocument loadJson(void);
}

#endif // UTIL_HPP
