#include "PopTable.hpp"
#include "../PointerRole.hpp"

PopTable::PopTable(QObject *parent)
	: QAbstractTableModel(parent)
{
}

PopTable::Pointer PopTable::resolve(int id) const
{
	if(id) {
	for(const auto& it : entries) {
		if(it->getPopId() == id) return it;
	} }
	return nullptr;
}

QVariant PopTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole) {
		switch (orientation) {
		case Qt::Orientation::Vertical:
			return (section < entries.size()) ? entries[section]->getPopId() : QVariant();
		case Qt::Orientation::Horizontal:
			switch (section) {
			case 0:
				return tr("Quantity");
			case 1:
				return tr("Area");
			case 2:
				return tr("Race");
			case 3:
				return tr("Religion");
			case 4:
				return tr("Occupation");
			case 5:
				return tr("Age Group");
			case 6:
				return tr("Is Female");
			default:
				return QVariant();
			}
		}
	}
	return QVariant();
}


int PopTable::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return entries.size()+1;
	// FIXME: Implement me!
}

int PopTable::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return 7;
	// FIXME: Implement me!
}

/*
	Q_PROPERTY(int popId READ getPopId WRITE setPopId)
	Q_PROPERTY(int quantity READ getQuantity WRITE setQuantity)
	Q_PROPERTY(QSharedPointer<Area> area READ getArea WRITE setArea)
	Q_PROPERTY(QSharedPointer<Race> race READ getRace WRITE setRace)
	Q_PROPERTY(QSharedPointer<Religion> religion READ getReligion WRITE setReligion)
	Q_PROPERTY(QSharedPointer<Occupation> occupation READ getOccupation WRITE setOccupation)
	Q_PROPERTY(QSharedPointer<AgeGroup> agegroup READ getAgegroup WRITE setAgegroup)
	Q_PROPERTY(bool female READ getFemale WRITE setFemale)
*/

QVariant PopTable::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(role == MH::PointerRole && index.row() < entries.size()) {
		switch (index.column()) {
		case 0:
			return QVariant::fromValue(entries[index.row()] );
		case 1:
			return QVariant::fromValue(entries[index.row()]->getArea());
		case 2:
			return QVariant::fromValue(entries[index.row()]->getRace());
		case 3:
			return QVariant::fromValue(entries[index.row()]->getReligion());
		case 4:
			return QVariant::fromValue(entries[index.row()]->getOccupation());
		case 5:
			return QVariant::fromValue(entries[index.row()]->getAgegroup());
		case 6:
			return QVariant::fromValue(entries[index.row()] );
		default:
			return QVariant();
		}
	}
	if(role == Qt::DisplayRole && index.row() < entries.size())
	{
		switch (index.column()) {
		case 0:
			return QVariant::fromValue(entries[index.row()]->getQuantity());
		case 1:
			return QVariant::fromValue(
				(entries[index.row()]->getArea()) ? entries[index.row()]->getArea()->getAreaName() : QVariant()
				);
		case 2:
			return QVariant::fromValue(
				(entries[index.row()]->getRace()) ? entries[index.row()]->getRace()->getRaceName() : QString()
				);
		case 3:
			return QVariant::fromValue(
				(entries[index.row()]->getReligion()) ? entries[index.row()]->getReligion()->getReligionName() : QString()
				);
			//return QVariant::fromValue(entries[index.row()]->getReligion()->getReligionName());
		case 4:
			return QVariant::fromValue(
				(entries[index.row()]->getOccupation()) ? entries[index.row()]->getOccupation()->getOccupationName() : QString()
				);
			//return QVariant::fromValue(entries[index.row()]->getOccupation()->getOccupationName());
		case 5:
			return QVariant::fromValue(
				(entries[index.row()]->getAgegroup()) ? entries[index.row()]->getAgegroup()->getAgeGroupName() : QString()
				);
			//return QVariant::fromValue(entries[index.row()]->getAgegroup()->getAgeGroupName());
		case 6:
			//return QVariant::fromValue(entries[index.row()]->getFemale());
		default:
			return QVariant();
		}
	}
	return QVariant();
}

bool PopTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(role == Qt::EditRole) {
		if(index.row() < entries.size()) {
			switch (index.column()) {
			case 0: {
				int dat = value.toInt();
				if(dat) {
					entries[index.row()]->setQuantity(dat);
				} else {
					removeRows(index.row(),1);
				}
				return true;
			}
			case 1: {
				entries[index.row()]->setArea(value.value<QSharedPointer<Area>>());
				return true;
			}
			case 2: {
				entries[index.row()]->setRace(value.value<QSharedPointer<Race>>());
				return true;
			}
			case 3: {
				entries[index.row()]->setReligion(value.value<QSharedPointer<Religion>>());
				return true;
			}
			case 4: {
				entries[index.row()]->setOccupation(value.value<QSharedPointer<Occupation>>());
				return true;
			}
			case 5: {
				entries[index.row()]->setAgegroup(value.value<QSharedPointer<AgeGroup>>());
				return true;
			}
			case 6: {
				entries[index.row()]->setFemale(value.toBool());
				return true;
			}
			default:
				return false;
			}
		} else {
			if(!index.column() && value.toInt()) {
				beginInsertRows(QModelIndex(), index.row(), index.row());
				Pointer tmp(new Pop(entries.size()+1));
				tmp->setQuantity(value.toInt());
				entries.push_back(tmp);
				endInsertRows();
				return true;
			} else return false;
		}
	}
	return false;
	/*if (data(index, role) != value) {
		// FIXME: Implement me!
		emit dataChanged(index, index, QVector<int>() << role);
		return true;
	}
	return false;*/
}

Qt::ItemFlags PopTable::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	if(index.row() == entries.size())
	{
		return (index.column()) ? Qt::NoItemFlags : Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	}
	return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool PopTable::insertRows(int row, int count, const QModelIndex &parent)
{
	int nindex = row;
	beginInsertRows(parent, row, row + count - 1);
	for(int i = 0; i < count;++i) {
		entries.insert(nindex,Pointer(new Pop(nindex)) );
		++nindex;
	}
	endInsertRows();
	return true;
}

bool PopTable::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i) {
		entries.removeAt(row);
	}
	endRemoveRows();
	return true;
}

void PopTable::clear()
{
	if(!entries.empty() ) {
	beginRemoveRows(QModelIndex(), 0, entries.size()-1);
	entries.clear();
	endRemoveRows();
	}
}

void PopTable::loadFromJSON(const QJsonArray &json, const AreaResolver& areaResolv, const RaceResolver& raceResolv,
							const ReligionResolver& religionResolv, const OccupationResolver& occupationResolv, const AgeGroupResolver& agegroupResolv)
{
	clear();
	beginInsertRows(QModelIndex(),0,json.size()-1);
	for(const auto& it : json) {
		entries.push_back(Pointer( new Pop(it.toObject(),areaResolv,raceResolv,religionResolv,occupationResolv,agegroupResolv)) );
	}
	endInsertRows();
}

void PopTable::saveToJSON(QJsonArray &json) const
{
	for(const auto& it : entries) {
		json.push_back(it->saveToJson());
	}
}

QJsonArray PopTable::saveToJSON() const
{
	QJsonArray tmp;
	saveToJSON(tmp);
	return tmp;
}

void PopTable::removeAllPops()
{
	clear();
}

void PopTable::onAreaRemoved(QSharedPointer<Area> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getArea() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void PopTable::onAgeGroupRemoved(QSharedPointer<AgeGroup> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getAgegroup() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void PopTable::onOccupationRemoved(QSharedPointer<Occupation> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getOccupation() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void PopTable::onRaceRemoved(QSharedPointer<Race> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getRace() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

void PopTable::onReligionRemoved(QSharedPointer<Religion> ptr)
{
	int i = 0;
	int count = entries.size();
	for(;i < count;) {
		if(entries[i]->getReligion() == ptr)
		{
			removeRows(i,1);
			--count;
		}
		else ++i;
	}
}

