#ifndef AGEGROUP_HPP
#define AGEGROUP_HPP

#include <QObject>
#include <QJsonObject>
#include "../Resolver/Resolver.hpp"

class AgeGroup : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int agegrpID READ getAgeGroupID WRITE setAgeGroupID)
	Q_PROPERTY(QString agegrpName READ getAgeGroupName WRITE setAgeGroupName)
private:
	int agegrpID;
	QString agegrpName;
public:
	explicit AgeGroup(QObject *parent = nullptr);
	explicit AgeGroup(int rowCnt, QObject *parent = nullptr);
	explicit AgeGroup(const QJsonObject& json, QObject *parent = nullptr);
	AgeGroup(const AgeGroup& cpy);
	void operator=(const AgeGroup& cpy);
	int getAgeGroupID() const;
	void setAgeGroupID(int value);
	QString getAgeGroupName() const;
	void setAgeGroupName(const QString &value);

	void saveToJson(QJsonObject& json) const;
	QJsonObject saveToJson(void) const;
	void loadFromJson(const QJsonObject& json);
	void operator=(const QJsonObject& json);
};
typedef Resolver<AgeGroup> AgeGroupResolver;

#endif // AGEGROUP_HPP
