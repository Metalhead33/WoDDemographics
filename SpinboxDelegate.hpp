#ifndef SPINBOXDELEGATE_HPP
#define SPINBOXDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QAbstractTableModel>
#include <limits>

class SpinboxDelegate : public QStyledItemDelegate
{
	Q_OBJECT
	int min,max;
public:
	explicit SpinboxDelegate(int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max(), QObject *parent = nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:

};

#endif // SPINBOXDELEGATE_HPP
