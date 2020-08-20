#ifndef OCCUPATION_HPP
#define OCCUPATION_HPP

#include <QObject>
#include <QJsonObject>
#include <QFlag>
#include "../Resolver/Resolver.hpp"

class Occupation : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int occupationID READ getOccupationID WRITE setOccupationID)
	Q_PROPERTY(QString occupationName READ getOccupationName WRITE setOccupationName)
private:
	int occupationID;
	QString occupationName;
public:
	explicit Occupation(QObject *parent = nullptr);
	explicit Occupation(int rowCnt, QObject *parent = nullptr);
	explicit Occupation(const QJsonObject& json, QObject *parent = nullptr);
	Occupation(const Occupation& cpy);
	void operator=(const Occupation& cpy);

	int getOccupationID() const;
	void setOccupationID(int value);

	QString getOccupationName() const;
	void setOccupationName(const QString &value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json);
	void operator=(const QJsonObject& json);

signals:

};
typedef Resolver<Occupation> OccupationResolver;

#endif // OCCUPATION_HPP
