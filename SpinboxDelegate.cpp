#include "SpinboxDelegate.hpp"
#include <QSpinBox>

SpinboxDelegate::SpinboxDelegate(int min, int max, QObject *parent) : QStyledItemDelegate(parent), min(min), max(max)
{

}

QWidget *SpinboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	(void)option;
	(void)index;
	QSpinBox *sb = new QSpinBox(parent);
	sb->setRange(min,max);
	return sb;
}

void SpinboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QSpinBox *cb = qobject_cast<QSpinBox *>(editor);
	Q_ASSERT(cb);
	// get the index of the text in the combobox that matches the current value of the item
	const int num = index.data(Qt::EditRole).toInt();
	// if it is valid, adjust the combobox
	cb->setValue(num);
}

void SpinboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QSpinBox *cb = qobject_cast<QSpinBox *>(editor);
	Q_ASSERT(cb);
	model->setData(index, cb->value(), Qt::EditRole);
}
