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

	proxies[0].setSourceModel(&agegroupz);
	proxies[1].setSourceModel(&areas);
	proxies[2].setSourceModel(&countries);
	proxies[3].setSourceModel(&pops);
	proxies[4].setSourceModel(&races);
	proxies[5].setSourceModel(&religions);
	proxies[6].setSourceModel(&regions);
	proxies[7].setSourceModel(&occupations);


	ui->agegroupsTable->setModel(&proxies[0]);
	ui->areasTable->setModel(&proxies[1]);
	ui->countriesTable->setModel(&proxies[2]);
	ui->popsTable->setModel(&proxies[3]);
	ui->racesTable->setModel(&proxies[4]);
	ui->religionsTable->setModel(&proxies[5]);
	ui->regionsTable->setModel(&proxies[6]);
	ui->occupationsTable->setModel(&proxies[7]);

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
	QJsonObject doc;
	doc["agegroups"] = agegroupz.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_ageGroupsLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("agegroups")) {
	agegroupz.loadFromJSON(doc["agegroups"].toArray());
	}
}

void MainWindow::on_popsSave2JSON_clicked()
{
	QJsonObject doc;
	doc["pops"] = pops.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_popsLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("pops")) {
		pops.loadFromJSON(doc["pops"].toArray(),areas,races,religions,occupations,agegroupz);
	}
}

void MainWindow::on_racesSave2JSON_clicked()
{
	QJsonObject doc;
	doc["races"] = races.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_racesLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("races")) {
		races.loadFromJSON(doc["races"].toArray());
	}
}

void MainWindow::on_religionsSave2JSON_clicked()
{
	QJsonObject doc;
	doc["religions"] = religions.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_reigionsLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("religions")) {
		religions.loadFromJSON(doc["religions"].toArray());
	}
}

void MainWindow::on_occupationsSave2JSON_clicked()
{
	QJsonObject doc;
	doc["occupations"] = occupations.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_occupationsLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("occupations")) {
		occupations.loadFromJSON(doc["occupations"].toArray());
	}
}

void MainWindow::on_countriesSave2JSON_clicked()
{
	QJsonObject doc;
	doc["countries"] = countries.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_countriesLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("countries")) {
		countries.loadFromJSON(doc["countries"].toArray());
	}
}

void MainWindow::on_regionsSave2JSON_clicked()
{
	QJsonObject doc;
	doc["regions"] = regions.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_regionsLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("regions")) {
		regions.loadFromJSON(doc["regions"].toArray(),countries);
	}
}

void MainWindow::on_areasSave2JSON_clicked()
{
	QJsonObject doc;
	doc["areas"] = areas.saveToJSON();
	Util::saveJson(QJsonDocument(doc));
}

void MainWindow::on_areasLoadFromJSON_clicked()
{
	auto doc = Util::loadJson().object();
	if(doc.contains("areas")) {
		areas.loadFromJSON(doc["areas"].toArray(),regions);
	}
}
