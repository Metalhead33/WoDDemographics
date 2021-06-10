#include "PopGeneratorDialog.hpp"
#include "ui_PopGeneratorDialog.h"
#include "PointerRole.hpp"

PopGeneratorDialog::PopGeneratorDialog(PopTable &popTable, AreaTable &areaTable, RaceTable &raceTable, ReligionTable &religionTable, const AgeGroupTable &groups, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PopGeneratorDialog), popTable(popTable), distributionTable(groups,parent)
{
	QWidget::setAttribute(Qt::WA_DeleteOnClose,true);
	ui->setupUi(this);
	ui->tableView->setModel(&distributionTable);
	ui->areaIn->setModel(&areaTable);
	ui->areaIn->setModelColumn(0);
	ui->raceIn->setModel(&raceTable);
	ui->raceIn->setModelColumn(0);
	ui->religionIn->setModel(&religionTable);
	ui->religionIn->setModelColumn(0);
}

PopGeneratorDialog::~PopGeneratorDialog()
{
	delete ui;
}

void PopGeneratorDialog::on_addPops_clicked()
{
	const QSharedPointer<Area> area = ui->areaIn->model()->data(ui->areaIn->model()->index(ui->areaIn->currentIndex(),0),MH::PointerRole).value<QSharedPointer<Area>>();
	const QSharedPointer<Religion> religion = ui->religionIn->model()->data(ui->religionIn->model()->index(ui->religionIn->currentIndex(),0),MH::PointerRole).value<QSharedPointer<Religion>>();
	const QSharedPointer<Race> race = ui->raceIn->model()->data(ui->raceIn->model()->index(ui->raceIn->currentIndex(),0),MH::PointerRole).value<QSharedPointer<Race>>();
	const int quantity = ui->quantityIn->value();
	const auto distributions = distributionTable.toDistributions(quantity);
	if(quantity && area && religion && race) {
		for(const auto& it : distributions) {
			popTable.insertPop(it.second.first,area,race,religion,nullptr,it.first,false);
			popTable.insertPop(it.second.second,area,race,religion,nullptr,it.first,true);
		}
	}
}
