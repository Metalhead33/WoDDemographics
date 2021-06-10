#ifndef POP_HPP
#define POP_HPP

#include <QObject>
#include <QJsonObject>
#include "AgeGroup.hpp"
#include "Area.hpp"
#include "Occupation.hpp"
#include "Race.hpp"
#include "Religion.hpp"
#include "../Resolver/Resolver.hpp"

class Pop : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int popId READ getPopId WRITE setPopId)
	Q_PROPERTY(int quantity READ getQuantity WRITE setQuantity)
	Q_PROPERTY(QSharedPointer<Area> area READ getArea WRITE setArea)
	Q_PROPERTY(QSharedPointer<Race> race READ getRace WRITE setRace)
	Q_PROPERTY(QSharedPointer<Religion> religion READ getReligion WRITE setReligion)
	Q_PROPERTY(QSharedPointer<Occupation> occupation READ getOccupation WRITE setOccupation)
	Q_PROPERTY(QSharedPointer<AgeGroup> agegroup READ getAgegroup WRITE setAgegroup)
	Q_PROPERTY(bool female READ getFemale WRITE setFemale)
private:
	int popId;
	int quantity;
	QSharedPointer<Area> area;
	QSharedPointer<Race> race;
	QSharedPointer<Religion> religion;
	QSharedPointer<Occupation> occupation;
	QSharedPointer<AgeGroup> agegroup;
	bool female;
public:
	explicit Pop(QObject *parent = nullptr);
	explicit Pop(int rowCnt, QObject *parent = nullptr);
	explicit Pop(const QJsonObject& json, const AreaResolver& areaResolv, const RaceResolver& raceResolv, const ReligionResolver& religionResolv, const OccupationResolver& occupationResolv, const AgeGroupResolver& agegroupResolv, QObject *parent = nullptr);
	explicit Pop(int id, int quantity, QSharedPointer<Area> area, QSharedPointer<Race> race, QSharedPointer<Religion> religion, QSharedPointer<Occupation> occupation,
				 QSharedPointer<AgeGroup> agegroup, bool female);
	Pop(const Pop& cpy);
	void operator=(const Pop& cpy);
	int getPopId() const;
	void setPopId(int value);

	int getQuantity() const;
	void setQuantity(int value);

	int getAreaID() const;
	int getRaceId() const;
	int getReligionID() const;
	int getOccupationID() const;
	int getAgegroupID() const;

	bool getFemale() const;
	void setFemale(bool value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json, const AreaResolver& areaResolv, const RaceResolver& raceResolv,
					  const ReligionResolver& religionResolv, const OccupationResolver& occupationResolv, const AgeGroupResolver& agegroupResolv);

	const QSharedPointer<Area> &getArea() const;
	void setArea(const QSharedPointer<Area> &value);

	QSharedPointer<Race> getRace() const;
	void setRace(const QSharedPointer<Race> &value);

	QSharedPointer<Religion> getReligion() const;
	void setReligion(const QSharedPointer<Religion> &value);

	QSharedPointer<Occupation> getOccupation() const;
	void setOccupation(const QSharedPointer<Occupation> &value);

	QSharedPointer<AgeGroup> getAgegroup() const;
	void setAgegroup(const QSharedPointer<AgeGroup> &value);

	Pop splitOff(int toSplit);

signals:

};
typedef Resolver<Pop> PopResolver;

#endif // POP_HPP
