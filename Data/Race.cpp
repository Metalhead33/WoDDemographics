#include "Race.hpp"

int Race::getRaceID() const
{
	return raceID;
}

void Race::setRaceID(int value)
{
	raceID = value;
}

QString Race::getRaceName() const
{
	return raceName;
}

void Race::setRaceName(const QString &value)
{
	raceName = value;
}

QString Race::getRaceName_hun() const
{
	return raceName_hun;
}

void Race::setRaceName_hun(const QString &value)
{
	raceName_hun = value;
}

void Race::saveToJson(QJsonObject &json) const
{
	json["raceID"] = this->raceID;
	json["raceName"] = this->raceName;
	json["raceName_hun"] = this->raceName_hun;
}

QJsonObject Race::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Race::loadFromJson(const QJsonObject &json)
{
	if(json.contains("raceID")) {
		this->raceID = json["raceID"].toInt();
	}
	if(json.contains("raceName")) {
		this->raceName = json["raceName"].toString();
	}
	if(json.contains("raceName_hun")) {
		this->raceName_hun = json["raceName_hun"].toString();
	}
}

void Race::operator=(const QJsonObject &json)
{
	loadFromJson(json);
}

Race::Race(QObject *parent) : QObject(parent)
{

}

Race::Race(int rowCnt, QObject *parent)
	: QObject(parent), raceID(rowCnt)
{

}

Race::Race(const QJsonObject &json, QObject *parent)
	: QObject(parent)
{
	this->raceID = json["raceID"].toInt(1);
	this->raceName = json["raceName"].toString();
	this->raceName_hun = json["raceName_hun"].toString();
}

Race::Race(const Race &cpy)
	: QObject(cpy.parent())
{
	this->raceID = cpy.raceID;
	this->raceName = cpy.raceName;
	this->raceName_hun = cpy.raceName_hun;
}

void Race::operator=(const Race &cpy)
{
	this->raceID = cpy.raceID;
	this->raceName = cpy.raceName;
	this->raceName_hun = cpy.raceName_hun;
}
