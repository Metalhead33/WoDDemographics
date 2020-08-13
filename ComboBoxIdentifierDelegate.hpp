#ifndef COMBOBOXIDENTIFIERDELEGATE_HPP
#define COMBOBOXIDENTIFIERDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QAbstractTableModel>

class ComboBoxIdentifierDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
	QAbstractTableModel* model;
	int column;
public:
	explicit ComboBoxIdentifierDelegate(int column, QAbstractTableModel* model, QObject *parent = nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:

};

#endif // COMBOBOXIDENTIFIERDELEGATE_HPP
