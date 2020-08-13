#include "CheckboxDelegate.hpp"
#include <QCheckBox>

CheckboxDelegate::CheckboxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *CheckboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	(void)option;
	(void)index;
	QCheckBox *cb = new QCheckBox(parent);
	return cb;
}

void CheckboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QCheckBox *cb = qobject_cast<QCheckBox *>(editor);
	Q_ASSERT(cb);
	// get the index of the text in the combobox that matches the current value of the item
	const bool isSet = index.data(Qt::EditRole).toBool();
	// if it is valid, adjust the combobox
	cb->setChecked(isSet);
	/*if(isSet) cb->setText(tr("True"));
	else cb->setText(tr("False"));*/
}

void CheckboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QCheckBox *cb = qobject_cast<QCheckBox *>(editor);
	Q_ASSERT(cb);
	model->setData(index, cb->isChecked(), Qt::EditRole);
}
