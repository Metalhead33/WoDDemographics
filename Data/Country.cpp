#include "Country.hpp"

int Country::getCountryID() const
{
	return countryID;
}

void Country::setCountryID(int value)
{
	countryID = value;
}

const QString &Country::getCountryName() const
{
	return countryName;
}

void Country::setCountryName(const QString &value)
{
	countryName = value;
}

void Country::saveToJson(QJsonObject &json) const
{
	json["countryID"] = this->countryID;
	json["countryName"] = this->countryName;
}

QJsonObject Country::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Country::loadFromJson(const QJsonObject &json)
{
	if(json.contains("countryID")) {
		this->countryID = json["countryID"].toInt();
	}
	if(json.contains("countryName")) {
		this->countryName = json["countryName"].toString();
	}
}

void Country::operator=(const QJsonObject &json)
{
	loadFromJson(json);
}

Country::Country(QObject *parent) : QObject(parent)
{

}

Country::Country(int rowCnt, QObject *parent)
	: QObject(parent), countryID(rowCnt)
{

}

Country::Country(const QJsonObject &json, QObject *parent)
	: QObject(parent)
{
	this->countryID = json["countryID"].toInt(1);
	this->countryName = json["countryName"].toString();
}

Country::Country(const Country &cpy)
	: QObject(cpy.parent())
{
	this->countryID = cpy.countryID;
	this->countryName = cpy.countryName;
}

void Country::operator=(const Country &cpy)
{
	this->countryID = cpy.countryID;
	this->countryName = cpy.countryName;
}
