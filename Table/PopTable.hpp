#ifndef POPTABLE_HPP
#define POPTABLE_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QJsonArray>
#include <QSharedPointer>
#include "../Data/Pop.hpp"

class PopTable : public QAbstractTableModel, public PopResolver
{
	Q_OBJECT
private:
	QList<Pointer> entries;
	int lastId;
public:
	explicit PopTable(QObject *parent = nullptr);
	Pointer resolve(int id) const override;

	// Header:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	// Add data:
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
	bool insertPop(qint64 quantity, QSharedPointer<Area> area, QSharedPointer<Race> race, QSharedPointer<Religion> religion, QSharedPointer<Occupation> occupation, QSharedPointer<AgeGroup> agegroup, bool female);

	// Remove data:
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

	void clear();
	void loadFromJSON(const QJsonArray& json, const AreaResolver& areaResolv, const RaceResolver& raceResolv,
					  const ReligionResolver& religionResolv, const OccupationResolver& occupationResolv, const AgeGroupResolver& agegroupResolv);
	void saveToJSON(QJsonArray& json) const;
	QJsonArray saveToJSON(void) const;

	void consolidate();
public slots:
	void removeAllPops(void);
	void onAreaRemoved(QSharedPointer<Area> ptr);
	void onAgeGroupRemoved(QSharedPointer<AgeGroup> ptr);
	void onOccupationRemoved(QSharedPointer<Occupation> ptr);
	void onRaceRemoved(QSharedPointer<Race> ptr);
	void onReligionRemoved(QSharedPointer<Religion> ptr);
private:
};

#endif // POPTABLE_HPP
