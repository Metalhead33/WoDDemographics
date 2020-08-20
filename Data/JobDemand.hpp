#ifndef JOBDEMAND_HPP
#define JOBDEMAND_HPP

#include <QObject>
#include <QFlag>
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include "Occupation.hpp"
#include "Race.hpp"
#include "Religion.hpp"
#include "AgeGroup.hpp"
#include "Pop.hpp"

class JobDemand : public QObject
{
	Q_OBJECT
public:
	enum Gender {
		NONE = 0x00,
		MALE_ONLY = 0x01,
		FEMALE_ONLY = 0x02,
		ALL = (MALE_ONLY | FEMALE_ONLY)
	};
	Q_DECLARE_FLAGS(GendersAllowed, Gender)
	Q_FLAG(GendersAllowed)
	typedef QSet<QSharedPointer<Race>> RaceSet;
	typedef QSet<QSharedPointer<Religion>> ReligionSet;
	typedef QSet<QSharedPointer<AgeGroup>> AgeGroupSet;

private:
	Q_PROPERTY(GendersAllowed gendersAllowed READ getGendersAllowed WRITE setGendersAllowed)
	Q_PROPERTY(int jobOpenings READ getJobOpenings WRITE setJobOpenings)
	GendersAllowed gendersAllowed;
	RaceSet allowedRaces; // Empty set assumed to be DONT_CARE
	ReligionSet allowedReligions; // Empty set assumed to be DONT_CARE
	AgeGroupSet allowedAgeGroups; // Empty set assumed to be DONT_CARE
	QSharedPointer<Occupation> jobOutput;
	int jobOpenings;

	void getRacesFromJson(const QJsonArray& json, const RaceResolver& resolv);
	void getReligionsFromJson(const QJsonArray& json, const ReligionResolver& resolv);
	void getAgeGroupsFromJson(const QJsonArray& json, const AgeGroupResolver& resolv);
	void saveRacesToJson(QJsonArray& json) const;
	void saveReligionsToJson(QJsonArray& json) const;
	void saveAgeGroupsToJson(QJsonArray& json) const;
	QJsonArray saveRacesToJson(void) const;
	QJsonArray saveReligionsToJson(void) const;
	QJsonArray saveAgeGroupsToJson(void) const;
public:
	explicit JobDemand(QObject *parent = nullptr);
	explicit JobDemand(const QJsonObject& json, const OccupationResolver& occupResolv, const RaceResolver& raceResolv,
					  const ReligionResolver& religionResolv, const AgeGroupResolver& agegrpResolv, QObject *parent = nullptr);
	JobDemand(const JobDemand& cpy);
	JobDemand(JobDemand&& mov);
	void operator=(const JobDemand& cpy);
	void operator=(JobDemand&& mov);

	const GendersAllowed &getGendersAllowed() const;
	GendersAllowed &getGendersAllowed();
	void setGendersAllowed(const GendersAllowed &value);

	RaceSet& getAllowedRaces();
	const RaceSet& getAllowedRaces() const;
	ReligionSet& getAllowedReligions();
	const ReligionSet& getAllowedReligions() const;
	AgeGroupSet& getAllowedAgeGroups();
	const AgeGroupSet& getAllowedAgeGroups() const;

	int getJobOpenings() const;
	void setJobOpenings(int value);


	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json, const OccupationResolver& occupResolv,
					  const RaceResolver& raceResolv, const ReligionResolver& religionResolv, const AgeGroupResolver& agegrpResolv);
	QSharedPointer<Occupation> getJobOutput() const;
	void setJobOutput(const QSharedPointer<Occupation> &value);
	bool doesPopMeetRequirements(const Pop& pop) const;
	Pop splitPopIfReqsAreMet(Pop& pop, int maxJobTakers);

signals:

};
Q_DECLARE_OPERATORS_FOR_FLAGS(JobDemand::GendersAllowed)


#endif // JOBDEMAND_HPP
