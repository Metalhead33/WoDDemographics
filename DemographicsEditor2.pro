QT += gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CheckboxDelegate.cpp \
        ComboBoxIdentifierDelegate.cpp \
        ComboBoxItemDelegate.cpp \
        Data/AgeGroup.cpp \
        Data/Area.cpp \
        Data/Business.cpp \
        Data/Country.cpp \
        Data/JobDemand.cpp \
        Data/Occupation.cpp \
        Data/Pop.cpp \
        Data/Race.cpp \
        Data/Region.cpp \
        Data/Religion.cpp \
        MainWindow.cpp \
        PopGeneratorDialog.cpp \
        SpinboxDelegate.cpp \
        Table/AgeGroupTable.cpp \
        Table/AreaTable.cpp \
        Table/CountryTable.cpp \
        Table/OccupationTable.cpp \
        Table/PopDistributionTable.cpp \
        Table/PopTable.cpp \
        Table/RaceTable.cpp \
        Table/RegionTable.cpp \
        Table/ReligionTable.cpp \
        Util.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	CheckboxDelegate.hpp \
	ComboBoxIdentifierDelegate.hpp \
	ComboBoxItemDelegate.hpp \
	Data/AgeGroup.hpp \
	Data/Area.hpp \
	Data/Business.hpp \
	Data/Country.hpp \
	Data/JobDemand.hpp \
	Data/Occupation.hpp \
	Data/Pop.hpp \
	Data/Race.hpp \
	Data/Region.hpp \
	Data/Religion.hpp \
	MainWindow.hpp \
	PointerRole.hpp \
	PopGeneratorDialog.hpp \
	Resolver/Resolver.hpp \
	SpinboxDelegate.hpp \
	Table/AgeGroupTable.hpp \
	Table/AreaTable.hpp \
	Table/CountryTable.hpp \
	Table/OccupationTable.hpp \
	Table/PopDistributionTable.hpp \
	Table/PopTable.hpp \
	Table/RaceTable.hpp \
	Table/RegionTable.hpp \
	Table/ReligionTable.hpp \
	Util.hpp

FORMS += \
	MainWindow.ui \
	PopGeneratorDialog.ui

DISTFILES += \
	README.md
