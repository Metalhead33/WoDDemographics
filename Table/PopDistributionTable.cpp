#include "PopDistributionTable.hpp"

PopDistributionTable::PopDistributionTable(const AgeGroupTable &groups, QObject *parent)
	: QAbstractTableModel(parent)
{
	for(const auto& it : groups.entries) {
		percentages.push_back(AgenGenderPercentage(it,GenderPercentage(0.0,0.0)));
	}
}

QVariant PopDistributionTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
	switch (orientation) {
	case Qt::Orientation::Vertical:
		return (section < percentages.size()) ? percentages[section].first->getAgeGroupName() : QVariant();
	case Qt::Orientation::Horizontal:
		{
			switch(section) {
			case 0:
				return tr("Male");
			case 1:
				return tr("Female");
			default:
				return QVariant();
			}
		}
	}
	}
	return QVariant();

	// FIXME: Implement me!
}

/*bool PopDistributionTable::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
	if (value != headerData(section, orientation, role)) {
		// FIXME: Implement me!
		emit headerDataChanged(orientation, section, section);
		return true;
	}
	return false;
}*/


int PopDistributionTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return percentages.size();
}

int PopDistributionTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return 2;
}

QVariant PopDistributionTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if( ((role == Qt::DisplayRole) || (role == Qt::EditRole)) && index.row() < percentages.size() && index.column() < 2)
	{
		return (index.column()) ? percentages[index.row()].second.second : percentages[index.row()].second.first;
	}
	// FIXME: Implement me!
	return QVariant();
}

bool PopDistributionTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (data(index, role) != value) {
		// FIXME: Implement me!
		if(index.column()) percentages[index.row()].second.second = value.toDouble();
			else percentages[index.row()].second.first = value.toDouble();
		emit dataChanged(index, index, QVector<int>() << role);
		return true;
	}
	return false;
}

Qt::ItemFlags PopDistributionTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

void PopDistributionTable::toDistributions(PopDistributionTable::DistributionList &distributions, int totalNumber) const
{
	for(const auto& it : percentages) {
		const double multipliedM = 0.01 * it.second.first * double(totalNumber);
		const double multipliedF = 0.01 * it.second.second * double(totalNumber);
		AgenGenderDistribution tmp(it.first,GenderDistribution(int(multipliedM),int(multipliedF)));
		distributions.push_back(tmp);
	}
}

PopDistributionTable::DistributionList PopDistributionTable::toDistributions(int totalNumber) const
{
	DistributionList tmp;
	toDistributions(tmp,totalNumber);
	return tmp;
}
