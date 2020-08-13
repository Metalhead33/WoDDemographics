#include "Occupation.hpp"

int Occupation::getOccupationID() const
{
	return occupationID;
}

void Occupation::setOccupationID(int value)
{
	occupationID = value;
}

QString Occupation::getOccupationName() const
{
	return occupationName;
}

void Occupation::setOccupationName(const QString &value)
{
	occupationName = value;
}

void Occupation::saveToJson(QJsonObject &json) const
{
	json["occupationID"] = this->occupationID;
	json["occupationName"] = this->occupationName;
}

QJsonObject Occupation::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Occupation::loadFromJson(const QJsonObject &json)
{
	if(json.contains("occupationID")) {
		this->occupationID = json["occupationID"].toInt();
	}
	if(json.contains("occupationName")) {
		this->occupationName = json["occupationName"].toString();
	}
}

void Occupation::operator=(const QJsonObject &json)
{
	loadFromJson(json);
}

Occupation::Occupation(QObject *parent) : QObject(parent)
{

}

Occupation::Occupation(int rowCnt, QObject *parent)
	: QObject(parent), occupationID(rowCnt)
{

}

Occupation::Occupation(const QJsonObject &json, QObject *parent)
	: QObject(parent)
{
	this->occupationID = json["occupationID"].toInt(1);
	this->occupationName = json["occupationName"].toString();
}

Occupation::Occupation(const Occupation &cpy)
	: QObject(cpy.parent())
{
	this->occupationID = cpy.occupationID;
	this->occupationName = cpy.occupationName;
}

void Occupation::operator=(const Occupation &cpy)
{
	this->occupationID = cpy.occupationID;
	this->occupationName = cpy.occupationName;
}
