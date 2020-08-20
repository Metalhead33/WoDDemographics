#include "JobDemand.hpp"

const JobDemand::GendersAllowed& JobDemand::getGendersAllowed() const
{
	return gendersAllowed;
}

JobDemand::GendersAllowed &JobDemand::getGendersAllowed()
{
	return gendersAllowed;
}

void JobDemand::setGendersAllowed(const GendersAllowed &value)
{
	gendersAllowed = value;
}

int JobDemand::getJobOpenings() const
{
	return jobOpenings;
}

void JobDemand::setJobOpenings(int value)
{
	jobOpenings = value;
}

void JobDemand::saveToJson(QJsonObject &json) const
{
	json["jobOpenings"] = this->jobOpenings;
	json["isMaleAllowed"] = this->gendersAllowed.testFlag(MALE_ONLY);
	json["isFemaleAllowed"] = this->gendersAllowed.testFlag(FEMALE_ONLY);
	if(jobOutput) json["jobOutput"] = this->jobOutput->getOccupationID();
	else json["jobOutput"] = 0;
	json["allowedRaces"] = saveRacesToJson();
	json["allowedReligions"] = saveReligionsToJson();
	json["allowedAgeGroups"] = saveAgeGroupsToJson();
}

QJsonObject JobDemand::saveToJson() const
{
	QJsonObject tmp;
	saveToJson(tmp);
	return tmp;
}

void JobDemand::loadFromJson(const QJsonObject &json, const OccupationResolver &occupResolv, const RaceResolver &raceResolv,
							 const ReligionResolver &religionResolv, const AgeGroupResolver &agegrpResolv)
{
	this->jobOpenings = json["jobOpenings"].toInt(0);
	this->gendersAllowed.setFlag(MALE_ONLY,json["isMaleAllowed"].toBool());
	this->gendersAllowed.setFlag(FEMALE_ONLY,json["isFemaleAllowed"].toBool());
	this->jobOutput = occupResolv.resolve(json["jobOutput"].toInt(0));
	if(json.contains(QStringLiteral("allowedRaces"))) {
		getRacesFromJson(json["allowedRaces"].toArray(),raceResolv);
	}
	if(json.contains(QStringLiteral("allowedReligions"))) {
		getReligionsFromJson(json["allowedReligions"].toArray(),religionResolv);
	}
	if(json.contains(QStringLiteral("allowedAgeGroups"))) {
		getAgeGroupsFromJson(json["allowedAgeGroups"].toArray(),agegrpResolv);
	}
}

QSharedPointer<Occupation> JobDemand::getJobOutput() const
{
	return jobOutput;
}

void JobDemand::setJobOutput(const QSharedPointer<Occupation> &value)
{
	jobOutput = value;
}

bool JobDemand::doesPopMeetRequirements(const Pop &pop) const
{
	const bool isRaceGood = (allowedRaces.isEmpty()) ? true : allowedRaces.contains(pop.getRace()); // Empty = don't care
	const bool isReligionGood = (allowedReligions.isEmpty()) ? true : allowedReligions.contains(pop.getReligion()); // Empty = don't care
	const bool isAgeGroupGood = (allowedAgeGroups.isEmpty()) ? true : allowedAgeGroups.contains(pop.getAgegroup()); // Empty = don't care
	const bool isGenderGood = (pop.getFemale()) ? gendersAllowed.testFlag(FEMALE_ONLY) : gendersAllowed.testFlag(MALE_ONLY);
	return (isRaceGood && isReligionGood && isAgeGroupGood && isGenderGood);
}

Pop JobDemand::splitPopIfReqsAreMet(Pop &pop, int maxJobTakers)
{
	if(jobOpenings && pop.getQuantity() && doesPopMeetRequirements(pop)) {
		const int toReduce = std::min(pop.getQuantity(),std::min(jobOpenings,maxJobTakers));
		auto newPop = pop.splitOff(toReduce);
		jobOpenings -= toReduce;
		newPop.setOccupation(jobOutput);
		return newPop;
	} else return Pop();
}

void JobDemand::getRacesFromJson(const QJsonArray &json, const RaceResolver &resolv)
{
	for(const auto& it: json) {
		auto resolved = resolv.resolve(it.toInt(0));
		if(resolved) allowedRaces.insert(resolved);
	}
}

void JobDemand::getReligionsFromJson(const QJsonArray &json, const ReligionResolver &resolv)
{
	for(const auto& it: json) {
		auto resolved = resolv.resolve(it.toInt(0));
		if(resolved) allowedReligions.insert(resolved);
	}
}

void JobDemand::getAgeGroupsFromJson(const QJsonArray &json, const AgeGroupResolver &resolv)
{
	for(const auto& it: json) {
		auto resolved = resolv.resolve(it.toInt(0));
		if(resolved) allowedAgeGroups.insert(resolved);
	}
}

void JobDemand::saveRacesToJson(QJsonArray &json) const
{
	for(const auto& it : allowedRaces) {
		json.push_back(it->getRaceID());
	}
}

void JobDemand::saveReligionsToJson(QJsonArray &json) const
{
	for(const auto& it : allowedReligions) {
		json.push_back(it->getReligionID());
	}
}

void JobDemand::saveAgeGroupsToJson(QJsonArray &json) const
{
	for(const auto& it : allowedAgeGroups) {
		json.push_back(it->getAgeGroupID());
	}
}

QJsonArray JobDemand::saveRacesToJson() const
{
	QJsonArray tmp;
	saveRacesToJson(tmp);
	return tmp;
}

QJsonArray JobDemand::saveReligionsToJson() const
{
	QJsonArray tmp;
	saveReligionsToJson(tmp);
	return tmp;
}

QJsonArray JobDemand::saveAgeGroupsToJson() const
{
	QJsonArray tmp;
	saveAgeGroupsToJson(tmp);
	return tmp;
}

JobDemand::JobDemand(QObject *parent) : QObject(parent), gendersAllowed(ALL)
{

}

JobDemand::JobDemand(const QJsonObject &json, const OccupationResolver &occupResolv, const RaceResolver &raceResolv,
					 const ReligionResolver &religionResolv, const AgeGroupResolver &agegrpResolv, QObject *parent)
	: QObject(parent)
{
	this->jobOpenings = json["jobOpenings"].toInt(0);
	this->gendersAllowed.setFlag(MALE_ONLY,json["isMaleAllowed"].toBool());
	this->gendersAllowed.setFlag(FEMALE_ONLY,json["isFemaleAllowed"].toBool());
	this->jobOutput = occupResolv.resolve(json["jobOutput"].toInt(0));
	if(json.contains(QStringLiteral("allowedRaces"))) {
		getRacesFromJson(json["allowedRaces"].toArray(),raceResolv);
	}
	if(json.contains(QStringLiteral("allowedReligions"))) {
		getReligionsFromJson(json["allowedReligions"].toArray(),religionResolv);
	}
	if(json.contains(QStringLiteral("allowedAgeGroups"))) {
		getAgeGroupsFromJson(json["allowedAgeGroups"].toArray(),agegrpResolv);
	}
}

JobDemand::JobDemand(const JobDemand &cpy) : QObject(cpy.parent()), gendersAllowed(cpy.gendersAllowed),
	  jobOpenings(cpy.jobOpenings), jobOutput(cpy.jobOutput), allowedRaces(cpy.allowedRaces),
	  allowedReligions(cpy.allowedReligions), allowedAgeGroups(cpy.allowedAgeGroups)
{

}

JobDemand::JobDemand(JobDemand &&mov) : QObject(mov.parent()), gendersAllowed(mov.gendersAllowed),
	  jobOpenings(mov.jobOpenings), jobOutput(std::move(mov.jobOutput)), allowedRaces(std::move(mov.allowedRaces)),
	  allowedReligions(std::move(mov.allowedReligions)), allowedAgeGroups(std::move(mov.allowedAgeGroups))
{

}

void JobDemand::operator=(const JobDemand &cpy)
{
	this->gendersAllowed = cpy.gendersAllowed;
	this->jobOpenings = cpy.jobOpenings;
	this->jobOutput = cpy.jobOutput;
	this->allowedRaces = cpy.allowedRaces;
	this->allowedReligions = cpy.allowedReligions;
	this->allowedAgeGroups = cpy.allowedAgeGroups;
}

void JobDemand::operator=(JobDemand &&mov)
{
	this->gendersAllowed = mov.gendersAllowed;
	this->jobOpenings = mov.jobOpenings;
	this->jobOutput = std::move(mov.jobOutput);
	this->allowedRaces = std::move(mov.allowedRaces);
	this->allowedReligions = std::move(mov.allowedReligions);
	this->allowedAgeGroups = std::move(mov.allowedAgeGroups);
}

JobDemand::RaceSet& JobDemand::getAllowedRaces()
{
	return allowedRaces;
}
const JobDemand::RaceSet& JobDemand::getAllowedRaces() const
{
	return allowedRaces;
}
JobDemand::ReligionSet& JobDemand::getAllowedReligions()
{
	return allowedReligions;
}
const JobDemand::ReligionSet& JobDemand::getAllowedReligions() const
{
	return allowedReligions;
}
JobDemand::AgeGroupSet& JobDemand::getAllowedAgeGroups()
{
	return allowedAgeGroups;
}
const JobDemand::AgeGroupSet& JobDemand::getAllowedAgeGroups() const
{
	return allowedAgeGroups;
}
