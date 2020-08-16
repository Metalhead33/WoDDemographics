#include "ReligionTable.hpp"
#include "../PointerRole.hpp"

ReligionTable::ReligionTable(QObject *parent)
	: QAbstractTableModel(parent)
{
}

ReligionTable::Pointer ReligionTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getReligionID() == id) return it;
	} }
	qWarning("Could not resolve the religion id [%d].",id);
	return nullptr;
}

QVariant ReligionTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getReligionID() : QVariant();
		case Qt::Orientation::Horizontal:
			return (!section) ? tr("Religion") : QVariant();
		}
	}
	return QVariant();
	// FIXME: Implement me!
}

int ReligionTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int ReligionTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 1;
	// FIXME: Implement me!
}

QVariant ReligionTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) return QVariant::fromValue(entries[index.row()] );
	if(role == Qt::DisplayRole && index.row() < entries.size() && !index.column())
		return entries[index.row()]->getReligionName();
	// FIXME: Implement me!
	return QVariant();
}
bool ReligionTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	QString str = value.toString();
	if (role == Qt::EditRole && !index.column()) {
		if( (str.isNull() || str.isEmpty())) {
			if(index.row() < entries.size()) {
				removeRows(index.row(),1);
			}
		} else if(index.row() < entries.size()) {
			entries[index.row()]->setReligionName(str);
			emit dataChanged(index, index, QVector<int>() << role);
		} else {
			beginInsertRows(QModelIndex(), index.row(), index.row());
			Pointer tmp(new Religion(entries.size()+1));
			tmp->setReligionName(str);
			entries.push_back(tmp);
			endInsertRows();
		}
		return true;
	}
	return false;
}

Qt::ItemFlags ReligionTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool ReligionTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Religion(nindex)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool ReligionTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingReligion(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void ReligionTable::clear()
{
	if(!entries.empty() ) {
	emit removingAllReligions();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void ReligionTable::loadFromJSON(const QJsonArray &json)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Religion(it.toObject() )) );
	}
	endInsertRows();
}

void ReligionTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray ReligionTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}


