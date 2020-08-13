#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <QObject>
#include <QJsonObject>
#include "../Resolver/Resolver.hpp"

class Country : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int countryID READ getCountryID WRITE setCountryID)
	Q_PROPERTY(QString countryName READ getCountryName WRITE setCountryName)
private:
	int countryID;
	QString countryName;
public:
	explicit Country(QObject *parent = nullptr);
	explicit Country(int rowCnt, QObject *parent = nullptr);
	explicit Country(const QJsonObject& json, QObject *parent = nullptr);
	Country(const Country& cpy);
	void operator=(const Country& cpy);

	int getCountryID() const;
	void setCountryID(int value);

	const QString& getCountryName() const;
	void setCountryName(const QString &value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json);
	void operator=(const QJsonObject& json);

signals:

};
typedef Resolver<Country> CountryResolver;

#endif // COUNTRY_HPP
