#include "AgeGroup.hpp"

int AgeGroup::getAgeGroupID() const
{
	return agegrpID;
}

void AgeGroup::setAgeGroupID(int value)
{
	agegrpID = value;
}

QString AgeGroup::getAgeGroupName() const
{
	return agegrpName;
}

void AgeGroup::setAgeGroupName(const QString &value)
{
	agegrpName = value;
}

void AgeGroup::saveToJson(QJsonObject &json) const
{
	json["agegrpID"] = this->agegrpID;
	json["agegrpName"] = this->agegrpName;
}

QJsonObject AgeGroup::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void AgeGroup::loadFromJson(const QJsonObject &json)
{
	if(json.contains("agegrpID")) {
		this->agegrpID = json["agegrpID"].toInt();
	}
	if(json.contains("agegrpName")) {
		this->agegrpName = json["agegrpName"].toString();
	}
}

void AgeGroup::operator=(const QJsonObject &json)
{
	loadFromJson(json);
}

AgeGroup::AgeGroup(QObject *parent)
	: QObject(parent)
{

}

AgeGroup::AgeGroup(int rowCnt, QObject *parent)
	: QObject(parent), agegrpID(rowCnt)
{

}

AgeGroup::AgeGroup(const QJsonObject &json, QObject *parent)
	: QObject(parent)
{
	this->agegrpID = json["agegrpID"].toInt(1);
	this->agegrpName = json["agegrpName"].toString();
}

AgeGroup::AgeGroup(const AgeGroup &cpy)
	: QObject(cpy.parent())
{
	this->agegrpID = cpy.agegrpID;
	this->agegrpName = cpy.agegrpName;
}

void AgeGroup::operator=(const AgeGroup &cpy)
{
	this->agegrpID = cpy.agegrpID;
	this->agegrpName = cpy.agegrpName;
}
