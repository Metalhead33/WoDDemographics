#include "RegionTable.hpp"
#include "../PointerRole.hpp"

RegionTable::RegionTable(QObject *parent)
	: QAbstractTableModel(parent), lastId(0)
{
}

RegionTable::Pointer RegionTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getRegionID() == id) return it;
	} }
	qWarning("Could not resolve the region id [%d].",id);
	return nullptr;
}

QVariant RegionTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getRegionID() : QVariant();
		case Qt::Orientation::Horizontal:
			switch (section) {
			case 0:
				return tr("Region");
			case 1:
				return tr("Country");
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
	// FIXME: Implement me!
}

int RegionTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int RegionTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return 2;
	// FIXME: Implement me!
}

QVariant RegionTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) {
		switch (index.column()) {
		case 0:
			return QVariant::fromValue(entries[index.row()] );
		case 1:
			return QVariant::fromValue(entries[index.row()]->getCountry());
		default:
			return QVariant();
		}
	}
	if(role == Qt::DisplayRole && index.row() < entries.size())
	{
		switch (index.column()) {
		case 0:
			return entries[index.row()]->getRegionName();
		case 1:
			return (entries[index.row()]->getCountry()) ? entries[index.row()]->getCountry()->getCountryName() : QString();
		default:
			return QVariant();
		}
	}
	return QVariant();
}

bool RegionTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::EditRole) {
		switch (index.column()) {
		case 0: {
			const QString str = value.toString();
			if( (str.isNull() || str.isEmpty())) {
				if(index.row() < entries.size()) {
					removeRows(index.row(),1);
				}
			} else if(index.row() < entries.size()) {
				entries[index.row()]->setRegionName(str);
				emit dataChanged(index, index, QVector<int>() << role);
			} else {
				beginInsertRows(QModelIndex(), index.row(), index.row());
				Pointer tmp(new Region(++lastId));
				tmp->setRegionName(str);
				entries.push_back(tmp);
				endInsertRows();
			}
			return true;
		}
		case 1: {
			if(index.row() < entries.size()) {
				entries[index.row()]->setCountry(value.value<QSharedPointer<Country>>());
				emit dataChanged(index, index, QVector<int>() << role);
				return true;
			} else return false;
		}

		}
	}
	return false;
}

Qt::ItemFlags RegionTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool RegionTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Region(++lastId)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool RegionTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingRegion(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void RegionTable::clear()
{
	lastId = 0;
	if(!entries.empty() ) {
	emit removingAllRegions();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void RegionTable::loadFromJSON(const QJsonArray &json, const CountryResolver &resolv)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Region(it.toObject(),resolv)) );
		lastId = std::max(lastId,entries.back()->getRegionID());
	}
	endInsertRows();
}

void RegionTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray RegionTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}

void RegionTable::onCountryRemoved(QSharedPointer<Country> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getCountry() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void RegionTable::removeAllRegions()
{
	clear();
}
