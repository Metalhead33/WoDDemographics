#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Util.hpp"

/*
ComboBoxIdentifierDelegate ageGroupsDelegate;
ComboBoxIdentifierDelegate areasDelegate;
ComboBoxIdentifierDelegate countriesDelegate;
ComboBoxIdentifierDelegate racesDelegate;
ComboBoxIdentifierDelegate religionsDelegate;
ComboBoxIdentifierDelegate regionsDelegate;
ComboBoxIdentifierDelegate occupationsDelegate;
*/

MainWindow::MainWindow(QWidget *parent) :
	  QMainWindow(parent),
	  ui(new Ui::MainWindow), ageGroupsDelegate(0,&agegroupz), areasDelegate(0,&areas), countriesDelegate(0,&countries),
	  racesDelegate(0, &races), religionsDelegate(0, &religions), regionsDelegate(0,&regions), occupationsDelegate(0,&occupations)
{
	ui->setupUi(this);
	ui->agegroupsTable->setModel(&agegroupz);
	ui->areasTable->setModel(&areas);
	ui->countriesTable->setModel(&countries);
	ui->popsTable->setModel(&pops);
	ui->racesTable->setModel(&races);
	ui->religionsTable->setModel(&religions);
	ui->regionsTable->setModel(&regions);
	ui->occupationsTable->setModel(&occupations);

	ui->regionsTable->setItemDelegateForColumn(1,&countriesDelegate); // Regions -> Countries foreign key
	ui->areasTable->setItemDelegateForColumn(1,&checkboxDelegate); // Checkbox for rural
	ui->areasTable->setItemDelegateForColumn(2,&regionsDelegate); // Areas -> Regions foreign key
	ui->popsTable->setItemDelegateForColumn(0,&spinboxDelegate); // Spinbox for quantity
	ui->popsTable->setItemDelegateForColumn(1,&areasDelegate); // Pops -> Areas foreign key
	ui->popsTable->setItemDelegateForColumn(2,&racesDelegate); // Pops -> Races foreign key
	ui->popsTable->setItemDelegateForColumn(3,&religionsDelegate); // Pops -> Religions foreign key
	ui->popsTable->setItemDelegateForColumn(4,&occupationsDelegate); // Pops -> Occupations foreign key
	ui->popsTable->setItemDelegateForColumn(5,&ageGroupsDelegate); // Pops -> AgeGroups foreign key
	ui->popsTable->setItemDelegateForColumn(6,&checkboxDelegate); // Checkbox for female
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_ageGroupsSave2JSON_clicked()
{
	QJsonDocument doc(agegroupz.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_ageGroupsLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	agegroupz.loadFromJSON(doc.array());
}
