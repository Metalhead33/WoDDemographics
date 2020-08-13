#ifndef CHECKBOXDELEGATE_HPP
#define CHECKBOXDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QAbstractTableModel>

class CheckboxDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit CheckboxDelegate(QObject *parent = nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:

};

#endif // CHECKBOXDELEGATE_HPP
