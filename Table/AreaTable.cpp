#include "AreaTable.hpp"
#include "../PointerRole.hpp"

AreaTable::AreaTable(QObject *parent)
	: QAbstractTableModel(parent)
{
}

AreaTable::Pointer AreaTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getAreaID() == id) return it;
	} }
	return nullptr;
}

QVariant AreaTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getAreaID() : QVariant();
		case Qt::Orientation::Horizontal:
			switch (section) {
			case 0:
				return tr("Area");
			case 1:
				return tr("Rural");
			case 2:
				return tr("Region");
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
	// FIXME: Implement me!
}

int AreaTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int AreaTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 3;
	// FIXME: Implement me!
}

QVariant AreaTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) {
		switch (index.column()) {
		case 0:
			return QVariant::fromValue(entries[index.row()] );
		case 1:
			return QVariant::fromValue(entries[index.row()] );
		case 2:
			return QVariant::fromValue(entries[index.row()]->getRegion());
		default:
			return QVariant();
		}
	}
	if((role == Qt::DisplayRole || role == Qt::EditRole) && index.row() < entries.size())
	{
		switch (index.column()) {
		case 0:
			return entries[index.row()]->getAreaName();
		case 1:
			return entries[index.row()]->getRural();
		case 2:
			return (entries[index.row()]->getRegion()) ? entries[index.row()]->getRegion()->getRegionName() : QString();
		default:
			return QVariant();
		}
	}
	return QVariant();
}


bool AreaTable::setData(const QModelIndex &index, const QVariant &value, int role)
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
				entries[index.row()]->setAreaName(str);
				emit dataChanged(index, index, QVector<int>() << role);
			} else {
				beginInsertRows(QModelIndex(), index.row(), index.row());
				Pointer tmp(new Area(entries.size()+1));
				tmp->setAreaName(str);
				entries.push_back(tmp);
				endInsertRows();
			}
			return true;
		}
		case 1: {
			if(index.row() < entries.size()) {
				entries[index.row()]->setRural(value.toBool());
				return true;
			} else return false;
		}
		case 2: {
			if(index.row() < entries.size()) {
				entries[index.row()]->setRegion(value.value<QSharedPointer<Region>>());
				emit dataChanged(index, index, QVector<int>() << role);
				return true;
			} else return false;
		}

		}
	}
	return false;
}

Qt::ItemFlags AreaTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool AreaTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Area(nindex)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool AreaTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingArea(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void AreaTable::clear()
{
	if(!entries.empty()) {
	emit removingAllAreas();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void AreaTable::loadFromJSON(const QJsonArray &json, const RegionResolver &resolv)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Area(it.toObject(),resolv )) );
	}
	endInsertRows();
}

void AreaTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray AreaTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}

void AreaTable::onRegionRemoved(QSharedPointer<Region> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getRegion() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void AreaTable::removeAllAreas()
{
	clear();
}
