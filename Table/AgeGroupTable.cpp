#include "AgeGroupTable.hpp"
#include "../PointerRole.hpp"

AgeGroupTable::AgeGroupTable(QObject *parent)
	: QAbstractTableModel(parent)
{
}

AgeGroupTable::Pointer AgeGroupTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getAgeGroupID() == id) return it;
	}
	}
	return nullptr;
}

QVariant AgeGroupTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
	switch (orientation) {
	case Qt::Orientation::Vertical:
		return (section < entries.size()) ? entries[section]->getAgeGroupID() : QVariant();
	case Qt::Orientation::Horizontal:
		return (!section) ? tr("Age Group") : QVariant();
	}
	}
	return QVariant();
	// FIXME: Implement me!
}

int AgeGroupTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int AgeGroupTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 1;
	// FIXME: Implement me!
}

QVariant AgeGroupTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) return QVariant::fromValue(entries[index.row()] );
	if(role == Qt::DisplayRole && index.row() < entries.size() && !index.column())
		return entries[index.row()]->getAgeGroupName();
	// FIXME: Implement me!
	return QVariant();
}

bool AgeGroupTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	QString str = value.toString();
	if (role == Qt::EditRole && !index.column()) {
		if( (str.isNull() || str.isEmpty())) {
			if(index.row() < entries.size()) {
			beginRemoveRows(QModelIndex(), index.row(), index.row());
			entries.removeAt(index.row());
			endRemoveRows();
			}
		} else if(index.row() < entries.size()) {
			entries[index.row()]->setAgeGroupName(str);
			emit dataChanged(index, index, QVector<int>() << role);
		} else {
			beginInsertRows(QModelIndex(), index.row(), index.row());
			Pointer tmp(new AgeGroup(entries.size()+1));
			tmp->setAgeGroupName(str);
			entries.push_back(tmp);
			endInsertRows();
		}
		return true;
	}
	return false;
}

Qt::ItemFlags AgeGroupTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool AgeGroupTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new AgeGroup(nindex)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool AgeGroupTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void AgeGroupTable::clear()
{
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
}

void AgeGroupTable::loadFromJSON(const QJsonArray &json)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new AgeGroup(it.toObject() )) );
	}
	endInsertRows();
}

void AgeGroupTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray AgeGroupTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}
