#ifndef POPDISTRIBUTIONTABLE_HPP
#define POPDISTRIBUTIONTABLE_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QPair>
#include "AgeGroupTable.hpp"

class PopDistributionTable : public QAbstractTableModel
{
	Q_OBJECT

public:
	typedef QPair<double,double> GenderPercentage;
	typedef QPair<qint64,qint64> GenderDistribution;
	typedef QPair<QSharedPointer<AgeGroup>,GenderPercentage> AgenGenderPercentage;
	typedef QPair<QSharedPointer<AgeGroup>,GenderDistribution> AgenGenderDistribution;
	typedef QList<AgenGenderPercentage> PercentageList;
	typedef QList<AgenGenderDistribution> DistributionList;

private:
	PercentageList percentages;
public:
	explicit PopDistributionTable(const AgeGroupTable& groups, QObject *parent = nullptr);

	// Header:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	void toDistributions(DistributionList& distributions, qint64 totalNumber) const;
	DistributionList toDistributions(int totalNumber) const;

private:
};

#endif // POPDISTRIBUTIONTABLE_HPP
