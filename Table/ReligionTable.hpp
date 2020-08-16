#ifndef RELIGIONTABLE_HPP
#define RELIGIONTABLE_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QJsonArray>
#include <QSharedPointer>
#include "../Data/Religion.hpp"

class ReligionTable : public QAbstractTableModel, public ReligionResolver
{
	Q_OBJECT
private:
	QList<Pointer> entries;
	int lastIndex;
public:
	explicit ReligionTable(QObject *parent = nullptr);
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
	void loadFromJSON(const QJsonArray& json);
	void saveToJSON(QJsonArray& json) const;
	QJsonArray saveToJSON(void) const;

signals:
	void removingReligion(Pointer ptr);
	void removingAllReligions(void);
};

#endif // RELIGIONTABLE_HPP
