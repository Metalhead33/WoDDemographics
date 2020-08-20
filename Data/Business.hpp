#ifndef BUSINESS_HPP
#define BUSINESS_HPP

#include <QObject>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include "JobDemand.hpp"

class Business : public QObject
{
	Q_OBJECT
public:
	enum Location {
		NOWHERE = 0x00,
		RURAL_ONLY = 0x01,
		URBAN_ONLY = 0x02,
		ANYWHERE = (RURAL_ONLY | URBAN_ONLY)
	};
	Q_DECLARE_FLAGS(Locations, Location)
	Q_FLAG(Locations)
	typedef QMap<QString,JobDemand> DemandList;
	typedef QList<JobDemand> DemandVector;
private:
	Q_PROPERTY(QString name READ getName WRITE setName)
	Q_PROPERTY(int supportValue READ getSupportValue WRITE setSupportValue)
	Q_PROPERTY(Locations location READ getLocation WRITE setLocation)
	Locations location;
	QString name;
	int supportValue;
	DemandList jobsOffered;
	void loadOfferedJobsFromJson(const QJsonObject& json, const OccupationResolver& occupationResolv, const RaceResolver& raceResolv,
								 const ReligionResolver& religionResolv, const AgeGroupResolver& ageGroupResolv);
	void saveJobsOfferedToJson(QJsonObject& json) const;
	QJsonObject saveJobsOfferedToJson(void) const;
public:
	explicit Business(QObject *parent = nullptr);
	explicit Business(const QJsonObject& json, const OccupationResolver& occupResolv, const RaceResolver& raceResolv,
					  const ReligionResolver& religionResolv, const AgeGroupResolver& agegrpResolv, QObject *parent = nullptr);
	Business(const Business& cpy);
	Business(Business&& mov);
	void operator=(const Business& cpy);
	void operator=(Business&& mov);

	QString getName() const;
	void setName(const QString &value);

	int getSupportValue() const;
	void setSupportValue(int value);

	Locations getLocation() const;
	void setLocation(const Business::Locations &value);

	bool isAllowedInRural() const;
	bool isAllowedInUrbanl() const;

	const DemandList& getJobsOffered() const;
	DemandList& getJobsOffered();

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json, const OccupationResolver& occupResolv,
					  const RaceResolver& raceResolv, const ReligionResolver& religionResolv, const AgeGroupResolver& agegrpResolv);
	void querryDemands(DemandVector& destination, int multiplier) const;
	void querryDemands(DemandVector& destination, double multiplier) const;
	DemandVector querryDemands(int multiplier) const;
	DemandVector querryDemands(double multiplier) const;

signals:

};

Q_DECLARE_OPERATORS_FOR_FLAGS(Business::Locations)

#endif // BUSINESS_HPP
