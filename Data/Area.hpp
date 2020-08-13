#ifndef AREA_HPP
#define AREA_HPP

#include <QObject>
#include <QJsonObject>
#include <QSharedPointer>
#include "Region.hpp"
#include "../Resolver/Resolver.hpp"

class Area : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int areaID READ getAreaID WRITE setAreaID)
	Q_PROPERTY(QString areaName READ getAreaName WRITE setAreaName)
	Q_PROPERTY(QSharedPointer<Region> region READ getRegion WRITE setRegion)
	Q_PROPERTY(bool rural READ getRural WRITE setRural)
private:
	int areaID;
	QString areaName;
	QSharedPointer<Region> region;
	bool rural;
public:
	explicit Area(QObject *parent = nullptr);
	explicit Area(int rowCnt, QObject *parent = nullptr);
	explicit Area(const QJsonObject& json, const RegionResolver& resolver, QObject *parent = nullptr);
	Area(const Area& cpy);
	void operator=(const Area& cpy);

	int getAreaID() const;
	void setAreaID(int value);

	QString getAreaName() const;
	void setAreaName(const QString &value);

	int getRegionID() const;

	bool getRural() const;
	void setRural(bool value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json, const RegionResolver& resolver);

	QSharedPointer<Region> getRegion() const;
	void setRegion(const QSharedPointer<Region> &value);

signals:

};
typedef Resolver<Area> AreaResolver;

#endif // AREA_HPP
