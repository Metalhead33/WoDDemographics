#ifndef RACE_HPP
#define RACE_HPP

#include <QObject>
#include <QJsonObject>
#include "../Resolver/Resolver.hpp"

class Race : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int raceID READ getRaceID WRITE setRaceID)
	Q_PROPERTY(QString raceName READ getRaceName WRITE setRaceName)
	Q_PROPERTY(QString raceName_hun READ getRaceName_hun WRITE setRaceName_hun)
private:
	int raceID;
	QString raceName;
	QString raceName_hun;
public:
	explicit Race(QObject *parent = nullptr);
	explicit Race(int rowCnt, QObject *parent = nullptr);
	explicit Race(const QJsonObject& json, QObject *parent = nullptr);
	Race(const Race& cpy);
	void operator=(const Race& cpy);

	int getRaceID() const;
	void setRaceID(int value);

	QString getRaceName() const;
	void setRaceName(const QString &value);

	QString getRaceName_hun() const;
	void setRaceName_hun(const QString &value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json);
	void operator=(const QJsonObject& json);

signals:

};
typedef Resolver<Race> RaceResolver;

#endif // RACE_HPP
