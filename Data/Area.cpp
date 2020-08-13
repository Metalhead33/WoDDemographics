#include "Area.hpp"

int Area::getAreaID() const
{
	return areaID;
}

void Area::setAreaID(int value)
{
	areaID = value;
}

QString Area::getAreaName() const
{
	return areaName;
}

void Area::setAreaName(const QString &value)
{
	areaName = value;
}

int Area::getRegionID() const
{
	if(region) return region->getRegionID();
}

bool Area::getRural() const
{
	return rural;
}

void Area::setRural(bool value)
{
	rural = value;
}

void Area::saveToJson(QJsonObject &json) const
{
	json["areaID"] = this->areaID;
	json["areaName"] = this->areaName;
	json["regionID"] = getRegionID();
	json["rural"] = this->rural;
}

QJsonObject Area::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Area::loadFromJson(const QJsonObject &json, const RegionResolver& resolver)
{
	if(json.contains("areaID")) {
		this->areaID = json["areaID"].toInt();
	}
	if(json.contains("areaName")) {
		this->areaName = json["areaName"].toString();
	}
	if(json.contains("regionID")) {
		this->region = resolver.resolve(json["regionID"].toInt());
	}
	if(json.contains("rural")) {
		this->rural = json["rural"].toBool();
	}
}

QSharedPointer<Region> Area::getRegion() const
{
	return region;
}

void Area::setRegion(const QSharedPointer<Region> &value)
{
	region = value;
}

Area::Area(QObject *parent) : QObject(parent)
{

}

Area::Area(int rowCnt, QObject *parent)
	: QObject(parent), areaID(rowCnt)
{

}

Area::Area(const QJsonObject &json, const RegionResolver &resolver, QObject *parent)
	: QObject(parent)
{
	this->areaID = json["areaID"].toInt(1);
	this->areaName = json["areaName"].toString();
	this->region = resolver.resolve(json["regionID"].toInt(1));
	this->rural = json["rural"].toBool(false);
}

Area::Area(const Area &cpy)
	: QObject(cpy.parent())
{
	this->areaID = cpy.areaID;
	this->areaName = cpy.areaName;
	this->region = cpy.region;
	this->rural = cpy.rural;
}

void Area::operator=(const Area &cpy)
{
	this->areaID = cpy.areaID;
	this->areaName = cpy.areaName;
	this->region = cpy.region;
	this->rural = cpy.rural;
}
