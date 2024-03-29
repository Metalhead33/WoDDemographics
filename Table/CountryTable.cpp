#include "CountryTable.hpp"
#include "../PointerRole.hpp"

CountryTable::CountryTable(QObject *parent)
	: QAbstractTableModel(parent), lastId(0)
{
}

CountryTable::Pointer CountryTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getCountryID() == id) return it;
	} }
	qWarning("Could not resolve the country id [%d].",id);
	return nullptr;
}


QVariant CountryTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getCountryID() : QVariant();
		case Qt::Orientation::Horizontal:
			return (!section) ? tr("Country") : QVariant();
		}
	}
	return QVariant();
	// FIXME: Implement me!
}


int CountryTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return entries.size()+1;
}

int CountryTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return 1;
}

QVariant CountryTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) return QVariant::fromValue(entries[index.row()] );
	if(role == Qt::DisplayRole && index.row() < entries.size() && !index.column())
		return entries[index.row()]->getCountryName();
	// FIXME: Implement me!
	return QVariant();
}

bool CountryTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	QString str = value.toString();
	if (role == Qt::EditRole && !index.column()) {
		if( (str.isNull() || str.isEmpty())) {
			if(index.row() < entries.size()) {
				removeRows(index.row(),1);
			}
		} else if(index.row() < entries.size()) {
			entries[index.row()]->setCountryName(str);
			emit dataChanged(index, index, QVector<int>() << role);
		} else {
			beginInsertRows(QModelIndex(), index.row(), index.row());
			Pointer tmp(new Country(++lastId));
			tmp->setCountryName(str);
			entries.push_back(tmp);
			endInsertRows();
		}
		return true;
	}
	return false;
}

Qt::ItemFlags CountryTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool CountryTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Country(++lastId)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool CountryTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		emit removingCountry(entries[row]);
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void CountryTable::clear()
{
	lastId = 0;
	if(!entries.empty() ) {
	emit removingAllCountries();
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void CountryTable::loadFromJSON(const QJsonArray &json)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Country(it.toObject() )) );
		lastId = std::max(lastId,entries.back()->getCountryID());
	}
	endInsertRows();
}

void CountryTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray CountryTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}

void CountryTable::consolidate()
{
	int row = 1;
	for(auto& it : entries) {
		it->setCountryID(row);
		++row;
	}
}
