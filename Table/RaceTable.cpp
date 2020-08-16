#include "RaceTable.hpp"
#include "../PointerRole.hpp"

RaceTable::RaceTable(QObject *parent)
	: QAbstractTableModel(parent), lastId(0)
{
}

RaceTable::Pointer RaceTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getRaceID() == id) return it;
	} }
	qWarning("Could not resolve the race id [%d].",id);
	return nullptr;
}

QVariant RaceTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getRaceID() : QVariant();
		case Qt::Orientation::Horizontal:
			switch (section) {
			case 0:
				return tr("Race Name");
			case 1:
				return tr("Race Name in Hungarian");
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
	// FIXME: Implement me!
}

int RaceTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int RaceTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 2;
	// FIXME: Implement me!
}

QVariant RaceTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) return QVariant::fromValue(entries[index.row()] );
	if(role == Qt::DisplayRole && index.row() < entries.size())
	{
		switch (index.column()) {
		case 0:
			return entries[index.row()]->getRaceName();
		case 1:
			return entries[index.row()]->getRaceName_hun();
		default:
			return QVariant();

		}
	}
	return QVariant();
}
bool RaceTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	QString str = value.toString();
	if (role == Qt::EditRole && !index.column()) {
		if( (str.isNull() || str.isEmpty())) {
			if(index.row() < entries.size()) {
				removeRows(index.row(),1);
			}
		} else if(index.row() < entries.size()) {
			entries[index.row()]->setRaceName(str);
			emit dataChanged(index, index, QVector<int>() << role);
		} else {
			beginInsertRows(QModelIndex(), index.row(), index.row());
			Pointer tmp(new Race(++lastId));
			tmp->setRaceName(str);
			entries.push_back(tmp);
			endInsertRows();
		}
		return true;
	}
	return false;
}

Qt::ItemFlags RaceTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool RaceTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Race(++lastId)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool RaceTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingRace(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void RaceTable::clear()
{
	lastId = 0;
	if(!entries.empty() ) {
	emit removingAllRaces();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void RaceTable::loadFromJSON(const QJsonArray &json)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Race(it.toObject() )) );
		lastId = std::max(lastId,entries.back()->getRaceID());
	}
	endInsertRows();
}

void RaceTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray RaceTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}

