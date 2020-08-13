#ifndef COMBOBOXITEMDELEGATE_H
#define COMBOBOXITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QAbstractTableModel>

class ComboBoxItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

private:
	QAbstractTableModel* model;
	int column;
public:
	ComboBoxItemDelegate(int column, QAbstractTableModel* model, QObject *parent = nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // COMBOBOXITEMDELEGATE_H
