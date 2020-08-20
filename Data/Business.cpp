#include "Business.hpp"

QString Business::getName() const
{
	return name;
}

void Business::setName(const QString &value)
{
	name = value;
}

int Business::getSupportValue() const
{
	return supportValue;
}

void Business::setSupportValue(int value)
{
	supportValue = value;
}

Business::Locations Business::getLocation() const
{
	return location;
}

void Business::setLocation(const Locations &value)
{
	location = value;
}

bool Business::isAllowedInRural() const
{
	return location.testFlag(RURAL_ONLY);
}

bool Business::isAllowedInUrbanl() const
{
	return location.testFlag(URBAN_ONLY);
}

const Business::DemandList &Business::getJobsOffered() const
{
	return jobsOffered;
}

Business::DemandList &Business::getJobsOffered()
{
	return jobsOffered;
}

void Business::saveToJson(QJsonObject &json) const
{
	json["name"] = this->name;
	json["supportValue"] = this->supportValue;
	json["allowedInRural"] = this->location.testFlag(RURAL_ONLY);
	json["allowedInUrban"] = this->location.testFlag(URBAN_ONLY);
	json["jobsOffered"] = saveJobsOfferedToJson();
}

QJsonObject Business::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void Business::loadFromJson(const QJsonObject &json, const OccupationResolver &occupResolv, const RaceResolver &raceResolv,
							const ReligionResolver &religionResolv, const AgeGroupResolver &agegrpResolv)
{
	this->name = json["name"].toString();
	this->supportValue = json["supportValue"].toInt();
	this->location.setFlag(RURAL_ONLY,json["allowedInRural"].toBool());
	this->location.setFlag(URBAN_ONLY,json["allowedInUrban"].toBool());
	if(json.contains(QStringLiteral("jobsOffered")))
		loadOfferedJobsFromJson(json["jobsOffered"].toObject(),occupResolv,raceResolv,religionResolv,agegrpResolv);
}

void Business::querryDemands(Business::DemandVector &destination, int multiplier) const
{
	Business::DemandVector tmp;
	for(const auto& it : jobsOffered) {
		tmp.push_back(it);
		tmp.back().setJobOpenings(it.getJobOpenings() * multiplier);
	}
	destination.append(tmp);
}

void Business::querryDemands(Business::DemandVector &destination, double multiplier) const
{
	Business::DemandVector tmp;
	for(const auto& it : jobsOffered) {
		tmp.push_back(it);
		tmp.back().setJobOpenings(int(double(it.getJobOpenings()) * multiplier));
	}
	destination.append(tmp);
}

Business::DemandVector Business::querryDemands(int multiplier) const
{
	Business::DemandVector tmp;
	for(const auto& it : jobsOffered) {
		tmp.push_back(it);
		tmp.back().setJobOpenings(it.getJobOpenings() * multiplier);
	}
	return tmp;
}

Business::DemandVector Business::querryDemands(double multiplier) const
{
	Business::DemandVector tmp;
	for(const auto& it : jobsOffered) {
		tmp.push_back(it);
		tmp.back().setJobOpenings(int(double(it.getJobOpenings()) * multiplier));
	}
	return tmp;
}

void Business::loadOfferedJobsFromJson(const QJsonObject &json, const OccupationResolver &occupationResolv, const RaceResolver &raceResolv, const ReligionResolver &religionResolv, const AgeGroupResolver &ageGroupResolv)
{
	for(auto it = std::begin(json); it != std::end(json); ++it) {
		JobDemand tmpDemand(it.value().toObject(),occupationResolv,raceResolv,religionResolv,ageGroupResolv,parent());
		jobsOffered.insert(it.key(),tmpDemand);
	}
}

void Business::saveJobsOfferedToJson(QJsonObject &json) const
{
	for(auto it = std::begin(jobsOffered); it != std::end(jobsOffered); ++it) {
		json.insert(it.key(), it.value().saveToJson());
	}
}

QJsonObject Business::saveJobsOfferedToJson() const
{
	QJsonObject tmp;
	saveJobsOfferedToJson(tmp);
	return tmp;
}

Business::Business(QObject *parent) : QObject(parent), location(ANYWHERE)
{

}

Business::Business(const QJsonObject &json, const OccupationResolver &occupResolv, const RaceResolver &raceResolv,
				   const ReligionResolver &religionResolv, const AgeGroupResolver &agegrpResolv, QObject *parent)
	: QObject(parent)
{
	this->name = json["name"].toString();
	this->supportValue = json["supportValue"].toInt();
	this->location.setFlag(RURAL_ONLY,json["allowedInRural"].toBool());
	this->location.setFlag(URBAN_ONLY,json["allowedInUrban"].toBool());
	if(json.contains(QStringLiteral("jobsOffered")))
		loadOfferedJobsFromJson(json["jobsOffered"].toObject(),occupResolv,raceResolv,religionResolv,agegrpResolv);
}

Business::Business(const Business &cpy)
	: QObject(cpy.parent()), name(cpy.name), supportValue(cpy.supportValue),
	  location(cpy.location), jobsOffered(cpy.jobsOffered)
{

}

Business::Business(Business &&mov)
	: QObject(mov.parent()), name(std::move(mov.name)), supportValue(mov.supportValue),
	  location(mov.location), jobsOffered( std::move(mov.jobsOffered) )
{

}

void Business::operator=(const Business &cpy)
{
	this->name = cpy.name;
	this->supportValue = cpy.supportValue;
	this->location = cpy.location;
	this->jobsOffered = cpy.jobsOffered;
}

void Business::operator=(Business &&mov)
{
	this->name = std::move(mov.name);
	this->supportValue = mov.supportValue;
	this->location = mov.location;
	this->jobsOffered = std::move(mov.jobsOffered);
}
