#ifndef REGION_HPP
#define REGION_HPP

#include <QObject>
#include <QJsonObject>
#include <QSharedPointer>
#include "Country.hpp"
#include "../Resolver/Resolver.hpp"

class Region : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int regionID READ getRegionID WRITE setRegionID)
	Q_PROPERTY(QString regionName READ getRegionName WRITE setRegionName)
	Q_PROPERTY(QSharedPointer<Country> country READ getCountry WRITE setCountry)
private:
	int regionID;
	QString regionName;
	QSharedPointer<Country> country;
public:
	explicit Region(QObject *parent = nullptr);
	explicit Region(int rowCnt, QObject *parent = nullptr);
	explicit Region(const QJsonObject& json, const CountryResolver& resolver, QObject *parent = nullptr);
	Region(const Region& cpy);
	void operator=(const Region& cpy);

	int getRegionID() const;
	void setRegionID(int value);

	const QString &getRegionName() const;
	void setRegionName(const QString &value);

	int getCountryID() const;

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json, const CountryResolver& resolver);

	QSharedPointer<Country> getCountry() const;
	void setCountry(const QSharedPointer<Country> &value);

signals:

};
typedef Resolver<Region> RegionResolver;

#endif // REGION_HPP
