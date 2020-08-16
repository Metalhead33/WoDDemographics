#include "OccupationTable.hpp"
#include "../PointerRole.hpp"

OccupationTable::OccupationTable(QObject *parent)
	: QAbstractTableModel(parent), lastId(0)
{
}

OccupationTable::Pointer OccupationTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getOccupationID() == id) return it;
	} }
	qWarning("Could not resolve the occupation id [%d].",id);
	return nullptr;
}


QVariant OccupationTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getOccupationID() : QVariant();
		case Qt::Orientation::Horizontal:
			return (!section) ? tr("Occupation") : QVariant();
		}
	}
	return QVariant();
	// FIXME: Implement me!
}


int OccupationTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int OccupationTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 1;
	// FIXME: Implement me!
}

QVariant OccupationTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) return QVariant::fromValue(entries[index.row()] );
	if(role == Qt::DisplayRole && index.row() < entries.size() && !index.column())
		return entries[index.row()]->getOccupationName();
	// FIXME: Implement me!
	return QVariant();
}

bool OccupationTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	QString str = value.toString();
	if (role == Qt::EditRole && !index.column()) {
		if( (str.isNull() || str.isEmpty())) {
			if(index.row() < entries.size()) {
				removeRows(index.row(),1);
			}
		} else if(index.row() < entries.size()) {
			entries[index.row()]->setOccupationName(str);
			emit dataChanged(index, index, QVector<int>() << role);
		} else {
			beginInsertRows(QModelIndex(), index.row(), index.row());
			Pointer tmp(new Occupation(++lastId));
			tmp->setOccupationName(str);
			entries.push_back(tmp);
			endInsertRows();
		}
		return true;
	}
	return false;
}

Qt::ItemFlags OccupationTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool OccupationTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Occupation(++lastId)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool OccupationTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingOccupation(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void OccupationTable::clear()
{
	lastId = 0;
	if(!entries.empty() ) {
	emit removingAllOccupations();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void OccupationTable::loadFromJSON(const QJsonArray &json)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Occupation(it.toObject() )) );
		lastId = std::max(lastId,entries.back()->getOccupationID());
	}
	endInsertRows();
}

void OccupationTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray OccupationTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}
