#ifndef REGIONTABLE_HPP
#define REGIONTABLE_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QJsonArray>
#include <QSharedPointer>
#include "../Data/Region.hpp"

class RegionTable : public QAbstractTableModel, public RegionResolver
{
	Q_OBJECT
private:
	QList<Pointer> entries;
public:
	explicit RegionTable(QObject *parent = nullptr);
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

	// Remove data:
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

	void clear();
	void loadFromJSON(const QJsonArray& json, const CountryResolver& resolv);
	void saveToJSON(QJsonArray& json) const;
	QJsonArray saveToJSON(void) const;
public slots:
	void onCountryRemoved(QSharedPointer<Country> ptr);
	void removeAllRegions(void);
signals:
	void removingRegion(Pointer ptr);
	void removingAllRegions(void);
};

#endif // REGIONTABLE_HPP
