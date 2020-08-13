#include "Region.hpp"

int Region::getRegionID() const
{
	return regionID;
}

void Region::setRegionID(int value)
{
	regionID = value;
}

const QString& Region::getRegionName() const
{
	return regionName;
}

void Region::setRegionName(const QString &value)
{
	regionName = value;
}

int Region::getCountryID() const
{
	if(country) return country->getCountryID();
	else return 0;
}

void Region::saveToJson(QJsonObject &json) const
{
	json["regionID"] = this->regionID;
	json["regionName"] = this->regionName;
	json["countryID"] = this->getCountryID();
}

QJsonObject Region::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Region::loadFromJson(const QJsonObject &json, const CountryResolver &resolver)
{
	if(json.contains("regionID")) {
		this->regionID = json["regionID"].toInt();
	}
	if(json.contains("regionName")) {
		this->regionName = json["regionName"].toString();
	}
	if(json.contains("countryID")) {
		this->country = resolver.resolve(json["countryID"].toInt(1));
	}
}

QSharedPointer<Country> Region::getCountry() const
{
    return country;
}

void Region::setCountry(const QSharedPointer<Country> &value)
{
    country = value;
}

Region::Region(QObject *parent) : QObject(parent)
{
    
}

Region::Region(int rowCnt, QObject *parent)
    : QObject(parent), regionID(rowCnt)
{
    
}

Region::Region(const QJsonObject &json, const CountryResolver &resolver, QObject *parent)
	: QObject(parent)
{
	this->regionID = json["regionID"].toInt(1);
	this->regionName = json["regionName"].toString();
	this->country = resolver.resolve(json["countryID"].toInt(1));
}

Region::Region(const Region &cpy)
	: QObject(cpy.parent())
{
	this->regionID = cpy.regionID;
	this->regionName = cpy.regionName;
	this->country = cpy.country;
}

void Region::operator=(const Region &cpy)
{
	this->regionID = cpy.regionID;
	this->regionName = cpy.regionName;
	this->country = cpy.country;
}
