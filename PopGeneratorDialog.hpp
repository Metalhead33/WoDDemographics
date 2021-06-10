#ifndef POPGENERATORDIALOG_HPP
#define POPGENERATORDIALOG_HPP

#include <QDialog>
#include "Table/AgeGroupTable.hpp"
#include "Table/AreaTable.hpp"
#include "Table/RaceTable.hpp"
#include "Table/ReligionTable.hpp"
#include "Table/PopDistributionTable.hpp"
#include "Table/PopTable.hpp"

namespace Ui {
class PopGeneratorDialog;
}

class PopGeneratorDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PopGeneratorDialog(PopTable& popTable, AreaTable& areaTable, RaceTable& raceTable, ReligionTable& religionTable,
								const AgeGroupTable &groups, QWidget *parent = nullptr);
	~PopGeneratorDialog() override;

private slots:
	void on_addPops_clicked();

private:
	Ui::PopGeneratorDialog *ui;
	PopDistributionTable distributionTable;
	PopTable& popTable;
};

#endif // POPGENERATORDIALOG_HPP
