#include "Util.hpp"
#include <QMetaProperty>
#include <QFileDialog>
#include <QErrorMessage>
#include <QCborMap>
#include <QErrorMessage>

namespace Util
{


void loadFromJSON(QObject &obj, const QJsonObject& json){
	auto meta = obj.metaObject();
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
	{
		QString tname(meta->property(i).name());
		if(json.contains(tname)) meta->property(i).write(&obj,json[tname].toVariant());
	}
}
void saveToJSON(const QObject &obj, QJsonObject& json){
	auto meta = obj.metaObject();
	for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
	{
		QString tname(meta->property(i).name());
		json[tname] = meta->property(i).read(&obj).toJsonValue();
	}
}

void saveJson(const QJsonDocument &json)
{
	auto fileName = QFileDialog::getSaveFileName(nullptr,"Open JSON file",QString(),QStringLiteral("JSON files and CBOR binaries ( *.json *.cbor )"));
	if(fileName.isNull() || fileName.isEmpty()) return;
	bool isBinary;
	if(fileName.endsWith(".cbor")) isBinary = true;
	else if(fileName.endsWith(".json")) isBinary = false;
	else {
		QErrorMessage err(nullptr);
		err.showMessage(QStringLiteral("The file must be either CBOR-binary or human-readable JSON!"));
		return;
	}
	QFile saveFile(fileName);
	if (!saveFile.open(QIODevice::WriteOnly)) {
		QErrorMessage err(nullptr);
		err.showMessage(QStringLiteral("Couldn't open file for writing."));
		return;
	}
	saveFile.write(isBinary ? QCborValue::fromJsonValue(json.object()).toCbor() : json.toJson());
}

void loadJson(QJsonDocument &json)
{
	auto fileName = QFileDialog::getOpenFileName(nullptr,"Open JSON file",QString(),QStringLiteral("JSON files and CBOR binaries ( *.json *.cbor )"));
	if(fileName.isNull() || fileName.isEmpty()) return;
	bool isBinary;
	if(fileName.endsWith(".cbor")) isBinary = true;
	else if(fileName.endsWith(".json")) isBinary = false;
	else {
		QErrorMessage err(nullptr);
		err.showMessage(QStringLiteral("The file must be either CBOR-binary or human-readable JSON!"));
		return;
	}
	QFile loadFile(fileName);
	if (!loadFile.open(QIODevice::ReadOnly)) {
		QErrorMessage err(nullptr);
		err.showMessage(QStringLiteral("Couldn't open file for reading."));
		return;
	}
	QByteArray saveData = loadFile.readAll();
	json = (isBinary ? QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject()) : QJsonDocument::fromJson(saveData));
}

QJsonDocument loadJson()
{
	QJsonDocument tmp;
	loadJson(tmp);
	return tmp;
}

}
