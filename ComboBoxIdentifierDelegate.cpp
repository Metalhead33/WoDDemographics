#include "ComboBoxIdentifierDelegate.hpp"
#include <QComboBox>
#include "PointerRole.hpp"

ComboBoxIdentifierDelegate::ComboBoxIdentifierDelegate(int column, QAbstractTableModel *model, QObject *parent) : QStyledItemDelegate(parent),
	  column(column), model(model)
{

}

QWidget *ComboBoxIdentifierDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	(void)option;
	(void)index;
	// Create the combobox and populate it
	QComboBox *cb = new QComboBox(parent);
	cb->setModel(model);
	cb->setModelColumn(column);
	return cb;
}

void ComboBoxIdentifierDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	Q_ASSERT(cb);
	// get the index of the text in the combobox that matches the current value of the item
	cb->setCurrentIndex(cb->findData(index.data(MH::PointerRole), MH::PointerRole));
	/*for(int I = 0; I < cb->count(); I++) {
		if(index.data(MH::PointerRole) == cb->itemData(I,MH::PointerRole)) {
			cb->setCurrentIndex(I);
		}
	}*/
}


void ComboBoxIdentifierDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	Q_ASSERT(cb);
	model->setData(index, cb->currentData(MH::PointerRole), Qt::EditRole);
}
