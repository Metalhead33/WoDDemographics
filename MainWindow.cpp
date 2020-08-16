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
	QObject::connect(&agegroupz,&AgeGroupTable::removingAgeGroup,&pops,&PopTable::onAgeGroupRemoved);
	QObject::connect(&agegroupz,&AgeGroupTable::removingAllAgeGroups,&pops,&PopTable::removeAllPops);
	QObject::connect(&areas,&AreaTable::removingArea,&pops,&PopTable::onAreaRemoved);
	QObject::connect(&areas,&AreaTable::removingAllAreas,&pops,&PopTable::removeAllPops);
	QObject::connect(&races,&RaceTable::removingRace,&pops,&PopTable::onRaceRemoved);
	QObject::connect(&races,&RaceTable::removingAllRaces,&pops,&PopTable::removeAllPops);
	QObject::connect(&religions,&ReligionTable::removingReligion,&pops,&PopTable::onReligionRemoved);
	QObject::connect(&religions,&ReligionTable::removingAllReligions,&pops,&PopTable::removeAllPops);
	QObject::connect(&occupations,&OccupationTable::removingOccupation,&pops,&PopTable::onOccupationRemoved);
	QObject::connect(&occupations,&OccupationTable::removingAllOccupations,&pops,&PopTable::removeAllPops);
	QObject::connect(&regions,&RegionTable::removingRegion,&areas,&AreaTable::onRegionRemoved);
	QObject::connect(&regions,&RegionTable::removingAllRegions,&areas,&AreaTable::removeAllAreas);
	QObject::connect(&countries,&CountryTable::removingCountry,&regions,&RegionTable::onCountryRemoved);
	QObject::connect(&countries,&CountryTable::removingAllCountries,&regions,&RegionTable::removeAllRegions);
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

void MainWindow::on_popsSave2JSON_clicked()
{
	QJsonDocument doc(pops.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_popsLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	pops.loadFromJSON(doc.array(),areas,races,religions,occupations,agegroupz);
}

void MainWindow::on_racesSave2JSON_clicked()
{
	QJsonDocument doc(races.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_racesLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	races.loadFromJSON(doc.array());
}

void MainWindow::on_religionsSave2JSON_clicked()
{
	QJsonDocument doc(religions.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_reigionsLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	religions.loadFromJSON(doc.array());
}

void MainWindow::on_occupationsSave2JSON_clicked()
{
	QJsonDocument doc(occupations.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_occupationsLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	occupations.loadFromJSON(doc.array());
}

void MainWindow::on_countriesSave2JSON_clicked()
{
	QJsonDocument doc(countries.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_countriesLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	countries.loadFromJSON(doc.array());
}

void MainWindow::on_regionsSave2JSON_clicked()
{
	QJsonDocument doc(regions.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_regionsLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	regions.loadFromJSON(doc.array(),countries);
}

void MainWindow::on_areasSave2JSON_clicked()
{
	QJsonDocument doc(areas.saveToJSON());
	Util::saveJson(doc);
}

void MainWindow::on_areasLoadFromJSON_clicked()
{
	QJsonDocument doc = Util::loadJson();
	areas.loadFromJSON(doc.array(),regions);
}
