#include "ComboBoxItemDelegate.hpp"
#include <QComboBox>

ComboBoxItemDelegate::ComboBoxItemDelegate(int column, QAbstractTableModel *model, QObject *parent)
	: QStyledItemDelegate(parent), model(model), column(column)
{
}

QWidget *ComboBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	(void)option;
	(void)index;
	// Create the combobox and populate it
	QComboBox *cb = new QComboBox(parent);
	cb->setModel(model);
	cb->setModelColumn(column);
	return cb;
}


void ComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	Q_ASSERT(cb);
	// get the index of the text in the combobox that matches the current value of the item
	const int cbIndex = index.data(Qt::EditRole).toInt();
	// if it is valid, adjust the combobox
	if (cbIndex >= 0 && cbIndex < cb->count() )
		cb->setCurrentIndex(cbIndex);
}


void ComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *cb = qobject_cast<QComboBox *>(editor);
	Q_ASSERT(cb);
	model->setData(index, cb->currentIndex(), Qt::EditRole);
}
