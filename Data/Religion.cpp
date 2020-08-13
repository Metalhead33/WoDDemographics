#include "Religion.hpp"

int Religion::getReligionID() const
{
	return religionID;
}

void Religion::setReligionID(int value)
{
	religionID = value;
}

QString Religion::getReligionName() const
{
	return religionName;
}

void Religion::setReligionName(const QString &value)
{
	religionName = value;
}

void Religion::saveToJson(QJsonObject &json) const
{
	json["religionID"] = this->religionID;
	json["religionName"] = this->religionName;
}

QJsonObject Religion::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Religion::loadFromJson(const QJsonObject &json)
{
	if(json.contains("religionID")) {
		this->religionID = json["religionID"].toInt();
	}
	if(json.contains("religionName")) {
		this->religionName = json["religionName"].toString();
	}
}

void Religion::operator=(const QJsonObject &json)
{
	loadFromJson(json);
}

Religion::Religion(QObject *parent) : QObject(parent)
{

}

Religion::Religion(int rowCnt, QObject *parent)
	: QObject(parent), religionID(rowCnt)
{

}

Religion::Religion(const QJsonObject &json, QObject *parent)
	: QObject(parent)
{
	this->religionID = json["religionID"].toInt(1);
	this->religionName = json["religionName"].toString();
}

Religion::Religion(const Religion &cpy)
	: QObject(cpy.parent())
{
	this->religionID = cpy.religionID;
	this->religionName = cpy.religionName;
}

void Religion::operator=(const Religion &cpy)
{
	this->religionID = cpy.religionID;
	this->religionName = cpy.religionName;
}
