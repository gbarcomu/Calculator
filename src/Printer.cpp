/*
 * Printer.cpp
 *
 *  Created on: May 12, 2016
 *      Author: guille
 */

#include "Printer.h"

void Printer::init() {

	outputFlow << "#include \"entorno_shol.h\"" << endl << endl << "int main(){"
			<< endl << "inicio();" << endl << endl;
}

Printer::Printer(HashTable *_hashTable, string outputName) {

	nameFile = outputName.substr(0, outputName.length() - 4) + ".cpp";

	outputFlow.open(nameFile);
	hashTable = _hashTable;
	printFile = true;

	cout << "Creating " << nameFile << " file" << endl;

	init();
}

void Printer::print(short typeOfSentence, string key) {

	VariableDetail variableDetail;

	switch (typeOfSentence) {

	case constants::PRINTMARKSENSOR:

		variableDetail = hashTable->getValueByKey(key);
		outputFlow << "marca_sensor(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;
		break;

	case constants::PRINTDISABLEACTUATOR:

		variableDetail = hashTable->getValueByKey(key);
		outputFlow << "desactivar_actuador(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;

		break;

	case constants::PRINTENABLEACTUATOR:

		variableDetail = hashTable->getValueByKey(key);
		outputFlow << "activar_actuador(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;

		break;

	case constants::PRINTVALUESENSOR:

		variableDetail = hashTable->getValueByKey(key);
		outputFlow << "valor_sensor(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< "," << variableDetail.value << ");" << endl;

		break;

	case constants::PRINTPAUSE:

		outputFlow << "pausa (" << key << ");" << endl;

		break;

	case constants::PRINTMESSAGE:

		outputFlow << "MostrarMensaje (" << key << ");" << endl;

		break;

	default:

		cout << typeOfSentence << endl;
	}
}

void Printer::printPause(int seconds) {

	outputFlow << "pausa (" << seconds << ");" << endl;
}

void Printer::printEndLine() {

	outputFlow << endl;
}

void Printer::printPlanoLinePair(pair<float,float> first, pair<float,float> second) {

	outputFlow << "linea(" << first.first << "," << first.second << "," << second.first << "," << second.second << ");" << endl;
}

void Printer::printPlanoLinePosition(pair<float,float> first, string key) {

	VariableDetail variableDetail = hashTable->getValueByKey(key);
	outputFlow << "linea(" << first.first << "," << first.second << "," << variableDetail.position1 << "," << variableDetail.position2 << ");" << endl;
}

void Printer::dontGenerateFile() {

	printFile = false;
	hashTable->dontPrintTable();
}

Printer::~Printer() {

	outputFlow << endl << "fin()" << endl << "return 0;" << endl << "}" << endl;
	outputFlow.close();
	if (!printFile) {

		  if( remove(nameFile.c_str()) != 0 ) {

			  cout << "Error deleting file" << endl;
		  }
		  else {

			  cout << "File deleted" << endl;
		  }
	}
}
