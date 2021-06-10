#include "Pop.hpp"

int Pop::getPopId() const
{
	return popId;
}

void Pop::setPopId(int value)
{
	popId = value;
}

int Pop::getQuantity() const
{
	return quantity;
}

void Pop::setQuantity(int value)
{
	quantity = value;
}

int Pop::getAreaID() const
{
	if(area) return area->getAreaID();
	else return 0;
}

int Pop::getRaceId() const
{
	if(race) return race->getRaceID();
	else return 0;
}

int Pop::getReligionID() const
{
	if(religion) return religion->getReligionID();
	else return 0;
}

int Pop::getOccupationID() const
{
	if(occupation) return occupation->getOccupationID();
	else return 0;
}


int Pop::getAgegroupID() const
{
	if(agegroup) return agegroup->getAgeGroupID();
	else return 0;
}

bool Pop::getFemale() const
{
	return female;
}

void Pop::setFemale(bool value)
{
	female = value;
}

void Pop::saveToJson(QJsonObject &json) const
{
	json["popId"] = this->popId;
	json["quantity"] = this->quantity;
	json["areaID"] = getAreaID();
	json["raceId"] = getRaceId();
	json["religionID"] = getReligionID();
	json["occupationID"] = getOccupationID();
	json["agegroupID"] = getAgegroupID();
	json["female"] = this->female;
}

QJsonObject Pop::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Pop::loadFromJson(const QJsonObject &json, const AreaResolver &areaResolv, const RaceResolver &raceResolv, const ReligionResolver &religionResolv, const OccupationResolver &occupationResolv, const AgeGroupResolver &agegroupResolv)
{
	if(json.contains("popId")) {
		this->popId = json["popId"].toInt();
	}
	if(json.contains("quantity")) {
		this->quantity = json["quantity"].toInt();
	}
	if(json.contains("areaID")) {
		this->area = areaResolv.resolve(json["areaId"].toInt(1));
	}
	if(json.contains("raceId")) {
		this->race = raceResolv.resolve(json["raceId"].toInt(1));
	}
	if(json.contains("religionID")) {
		this->religion = religionResolv.resolve(json["religionID"].toInt(1));
	}
	if(json.contains("occupationID")) {
		this->occupation = occupationResolv.resolve(json["occupationID"].toInt(1));
	}
	if(json.contains("agegroupID")) {
		this->agegroup = agegroupResolv.resolve(json["agegroupID"].toInt(1));
	}
	if(json.contains("female")) {
		this->female = json["female"].toBool();
	}
}

const QSharedPointer<Area> &Pop::getArea() const
{
	return area;
}

void Pop::setArea(const QSharedPointer<Area> &value)
{
	area = value;
}

QSharedPointer<Race> Pop::getRace() const
{
	return race;
}

void Pop::setRace(const QSharedPointer<Race> &value)
{
	race = value;
}

QSharedPointer<Religion> Pop::getReligion() const
{
	return religion;
}

void Pop::setReligion(const QSharedPointer<Religion> &value)
{
	religion = value;
}

QSharedPointer<Occupation> Pop::getOccupation() const
{
	return occupation;
}

void Pop::setOccupation(const QSharedPointer<Occupation> &value)
{
	occupation = value;
}

QSharedPointer<AgeGroup> Pop::getAgegroup() const
{
	return agegroup;
}

void Pop::setAgegroup(const QSharedPointer<AgeGroup> &value)
{
	agegroup = value;
}

Pop Pop::splitOff(int toSplit)
{
	const int toReduce = std::min(toSplit,quantity);
	Pop tmp(*this);
	this->quantity -= toReduce;
	tmp.quantity = toReduce;
	return tmp;
}

Pop::Pop(QObject *parent) : QObject(parent)
{

}

Pop::Pop(int rowCnt, QObject *parent)
	: QObject(parent), popId(rowCnt)
{

}

Pop::Pop(const QJsonObject &json, const AreaResolver &areaResolv, const RaceResolver &raceResolv, const ReligionResolver &religionResolv, const OccupationResolver &occupationResolv, const AgeGroupResolver &agegroupResolv, QObject *parent)
	: QObject(parent)
{
	this->popId = json["popId"].toInt(1);
	this->quantity = json["quantity"].toInt(0);
	this->area = areaResolv.resolve(json["areaID"].toInt(1));
	this->race = raceResolv.resolve(json["raceId"].toInt(1));
	this->religion = religionResolv.resolve(json["religionID"].toInt(1));
	this->occupation = occupationResolv.resolve(json["occupationID"].toInt(1));
	this->agegroup = agegroupResolv.resolve(json["agegroupID"].toInt(1));
	this->female = json["female"].toBool(false);
}

Pop::Pop(int id, int quantity, QSharedPointer<Area> area, QSharedPointer<Race> race, QSharedPointer<Religion> religion, QSharedPointer<Occupation> occupation, QSharedPointer<AgeGroup> agegroup, bool female) : QObject(nullptr),
	popId(id), quantity(quantity), area(area), race(race), religion(religion), occupation(occupation), agegroup(agegroup), female(female)
{

}

Pop::Pop(const Pop &cpy)
	: QObject(cpy.parent())
{
	this->popId = cpy.popId;
	this->quantity = cpy.quantity;
	this->area = cpy.area;
	this->race = cpy.race;
	this->religion = cpy.religion;
	this->occupation = cpy.occupation;
	this->agegroup = cpy.agegroup;
	this->female = cpy.female;
}

void Pop::operator=(const Pop &cpy)
{
	this->popId = cpy.popId;
	this->quantity = cpy.quantity;
	this->area = cpy.area;
	this->race = cpy.race;
	this->religion = cpy.religion;
	this->occupation = cpy.occupation;
	this->agegroup = cpy.agegroup;
	this->female = cpy.female;
}
