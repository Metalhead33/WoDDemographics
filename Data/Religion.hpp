#ifndef RELIGION_HPP
#define RELIGION_HPP

#include <QObject>
#include <QJsonObject>
#include "../Resolver/Resolver.hpp"

class Religion : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int religionID READ getReligionID WRITE setReligionID)
	Q_PROPERTY(QString religionName READ getReligionName WRITE setReligionName)
private:
	int religionID;
	QString religionName;
public:
	explicit Religion(QObject *parent = nullptr);
	explicit Religion(int rowCnt, QObject *parent = nullptr);
	explicit Religion(const QJsonObject& json, QObject *parent = nullptr);
	Religion(const Religion& cpy);
	void operator=(const Religion& cpy);

	int getReligionID() const;
	void setReligionID(int value);

	QString getReligionName() const;
	void setReligionName(const QString &value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json);
	void operator=(const QJsonObject& json);

signals:

};
typedef Resolver<Religion> ReligionResolver;

#endif // RELIGION_HPP
