#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Util.hpp"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include "PopGeneratorDialog.hpp"

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
	if(ui->consolidateBox->isChecked()) agegroupz.consolidate();
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
	if(ui->consolidateBox->isChecked()) pops.consolidate();
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
	if(ui->consolidateBox->isChecked()) races.consolidate();
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
	if(ui->consolidateBox->isChecked()) religions.consolidate();
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
	if(ui->consolidateBox->isChecked()) occupations.consolidate();
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
	if(ui->consolidateBox->isChecked()) countries.consolidate();
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
	if(ui->consolidateBox->isChecked()) regions.consolidate();
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
	if(ui->consolidateBox->isChecked()) areas.consolidate();
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

void MainWindow::on_loadAllBtn_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this,tr("Select directory to import demographics data from!"),QString());
	if(path.isEmpty()) return;
	QDir direct(path);
	QString fPath = direct.absoluteFilePath(QStringLiteral("occupations.json"));
	QFile occupationsFile(fPath);
	if(occupationsFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(occupationsFile.readAll()).object();
		if(doc.contains("occupations")) {
			occupations.loadFromJSON(doc["occupations"].toArray());
		}
		occupationsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("agegroups.json"));
	QFile agegroupsFile(fPath);
	if(agegroupsFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(agegroupsFile.readAll()).object();
		if(doc.contains("agegroups")) {
			agegroupz.loadFromJSON(doc["agegroups"].toArray());
		}
		agegroupsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("religions.json"));
	QFile religionsFile(fPath);
	if(religionsFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(religionsFile.readAll()).object();
		if(doc.contains("religions")) {
			religions.loadFromJSON(doc["religions"].toArray());
		}
		religionsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("races.json"));
	QFile racesFile(fPath);
	if(racesFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(racesFile.readAll()).object();
		if(doc.contains("races")) {
			races.loadFromJSON(doc["races"].toArray());
		}
		racesFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("countries.json"));
	QFile countriesFile(fPath);
	if(countriesFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(countriesFile.readAll()).object();
		if(doc.contains("countries")) {
			countries.loadFromJSON(doc["countries"].toArray());
		}
		countriesFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("regions.json"));
	QFile regionsFile(fPath);
	if(regionsFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(regionsFile.readAll()).object();
		if(doc.contains("regions")) {
			regions.loadFromJSON(doc["regions"].toArray(),countries);
		}
		regionsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("areas.json"));
	QFile areasFile(fPath);
	if(areasFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(areasFile.readAll()).object();
		if(doc.contains("areas")) {
			areas.loadFromJSON(doc["areas"].toArray(),regions);
		}
		areasFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("pops.json"));
	QFile popsFile(fPath);
	if(popsFile.open(QFile::ReadOnly)) {
		auto doc = QJsonDocument::fromJson(popsFile.readAll()).object();
		if(doc.contains("pops")) {
			pops.loadFromJSON(doc["pops"].toArray(),areas,races,religions,occupations,agegroupz);
		}
		popsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\". Does it even exist?").arg(fPath));
		return;
	}
	QMessageBox::information(this,tr("Success!"),tr("Successfully loaded all the files!"));
	/*QDirIterator iter(path);
	while(iter.hasNext()) {
		QString path = iter.next();
	}*/
}

void MainWindow::on_saveAllBtn_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this,tr("Select directory to export demographics data to!"),QString());
	if(path.isEmpty()) return;
	if(ui->consolidateBox->isChecked()) {
		agegroupz.consolidate();
		races.consolidate();
		religions.consolidate();
		occupations.consolidate();
		countries.consolidate();
		regions.consolidate();
		areas.consolidate();
		pops.consolidate();
	}
	QDir direct(path);
	QString fPath = direct.absoluteFilePath(QStringLiteral("occupations.json"));
	QFile occupationsFile(fPath);
	if(occupationsFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["occupations"] = occupations.saveToJSON();
		occupationsFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		occupationsFile.flush();
		occupationsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("agegroups.json"));
	QFile agegroupsFile(fPath);
	if(agegroupsFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["agegroups"] = agegroupz.saveToJSON();
		agegroupsFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		agegroupsFile.flush();
		agegroupsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("religions.json"));
	QFile religionsFile(fPath);
	if(religionsFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["religions"] = religions.saveToJSON();
		religionsFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		religionsFile.flush();
		religionsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("races.json"));
	QFile racesFile(fPath);
	if(racesFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["races"] = races.saveToJSON();
		racesFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		racesFile.flush();
		racesFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("countries.json"));
	QFile countriesFile(fPath);
	if(countriesFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["countries"] = countries.saveToJSON();
		countriesFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		countriesFile.flush();
		countriesFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("regions.json"));
	QFile regionsFile(fPath);
	if(regionsFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["regions"] = regions.saveToJSON();
		regionsFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		regionsFile.flush();
		regionsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("areas.json"));
	QFile areasFile(fPath);
	if(areasFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["areas"] = areas.saveToJSON();
		areasFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		areasFile.flush();
		areasFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	fPath = direct.absoluteFilePath(QStringLiteral("pops.json"));
	QFile popsFile(fPath);
	if(popsFile.open(QFile::WriteOnly)) {
		QJsonObject doc;
		doc["pops"] = pops.saveToJSON();
		popsFile.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
		popsFile.flush();
		popsFile.close();
	} else {
		QMessageBox::critical(this,tr("Error!"),tr("Could not open the file \"%1\" for writing.").arg(fPath));
		return;
	}
	QMessageBox::information(this,tr("Success!"),tr("Successfully saved all the files!"));
}

void MainWindow::on_purgePops_clicked()
{
	pops.clear();
}

void MainWindow::on_purgeRaces_clicked()
{
	races.clear();
}

void MainWindow::on_purgeReligions_clicked()
{
	religions.clear();
}

void MainWindow::on_purgeAgeGrps_clicked()
{
	agegroupz.clear();
}

void MainWindow::on_purgeOccupations_clicked()
{
	occupations.clear();
}

void MainWindow::on_purgeCountries_clicked()
{
	countries.clear();
}

void MainWindow::on_purgeRegions_clicked()
{
	regions.clear();
}

void MainWindow::on_purgeAreas_clicked()
{
	areas.clear();
}

void MainWindow::on_popDistributionCreator_clicked()
{
	PopGeneratorDialog* dial = new PopGeneratorDialog(pops,areas,races,religions,agegroupz,this);
	dial->show();
}
