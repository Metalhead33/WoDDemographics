#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Table/AgeGroupTable.hpp"
#include "Table/AreaTable.hpp"
#include "Table/CountryTable.hpp"
#include "Table/PopTable.hpp"
#include "Table/RaceTable.hpp"
#include "Table/RegionTable.hpp"
#include "Table/ReligionTable.hpp"
#include "Table/OccupationTable.hpp"
#include "ComboBoxIdentifierDelegate.hpp"
#include "SpinboxDelegate.hpp"
#include "CheckboxDelegate.hpp"
#include <QSortFilterProxyModel>
#include <array>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_ageGroupsSave2JSON_clicked();

	void on_ageGroupsLoadFromJSON_clicked();

	void on_popsSave2JSON_clicked();

	void on_popsLoadFromJSON_clicked();

	void on_racesSave2JSON_clicked();

	void on_racesLoadFromJSON_clicked();

	void on_religionsSave2JSON_clicked();

	void on_reigionsLoadFromJSON_clicked();

	void on_occupationsSave2JSON_clicked();

	void on_occupationsLoadFromJSON_clicked();

	void on_countriesSave2JSON_clicked();

	void on_countriesLoadFromJSON_clicked();

	void on_regionsSave2JSON_clicked();

	void on_regionsLoadFromJSON_clicked();

	void on_areasSave2JSON_clicked();

	void on_areasLoadFromJSON_clicked();

	void on_loadAllBtn_clicked();

	void on_saveAllBtn_clicked();

	void on_purgePops_clicked();

	void on_purgeRaces_clicked();

	void on_purgeReligions_clicked();

	void on_purgeAgeGrps_clicked();

	void on_purgeOccupations_clicked();

	void on_purgeCountries_clicked();

	void on_purgeRegions_clicked();

	void on_purgeAreas_clicked();

	void on_popDistributionCreator_clicked();

private:
	Ui::MainWindow *ui;
	AgeGroupTable agegroupz;
	AreaTable areas;
	CountryTable countries;
	PopTable pops;
	RaceTable races;
	RegionTable regions;
	ReligionTable religions;
	OccupationTable occupations;
	std::array<QSortFilterProxyModel,8> proxies;

	ComboBoxIdentifierDelegate ageGroupsDelegate;
	ComboBoxIdentifierDelegate areasDelegate;
	ComboBoxIdentifierDelegate countriesDelegate;
	ComboBoxIdentifierDelegate racesDelegate;
	ComboBoxIdentifierDelegate religionsDelegate;
	ComboBoxIdentifierDelegate regionsDelegate;
	ComboBoxIdentifierDelegate occupationsDelegate;
	SpinboxDelegate spinboxDelegate;
	CheckboxDelegate checkboxDelegate;
};

#endif // MAINWINDOW_HPP
