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

	string name;
	name = outputName.substr(0, outputName.length() - 4) + ".cpp";
	outputFlow.open("outputFiles/" + name);
	hashTable = _hashTable;

	cout << "Creating " << name << " file" << endl;

	init();
}

void Printer::print(short typeOfSentence, string key) {

	VariableDetail variableDetail = hashTable->getValueByKey(key);

	switch (typeOfSentence) {

	case constants::PRINTMARKSENSOR:

		outputFlow << "marca_sensor(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;
		break;

	case constants::PRINTDISABLEACTUATOR:

		outputFlow << "desactivar_actuador(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;

		break;

	case constants::PRINTENABLEACTUATOR:

		outputFlow << "activar_actuador(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< ",\"" << key << "\");" << endl;

		break;

	case constants::PRINTVALUESENSOR:

		outputFlow << "valor_sensor(" << variableDetail.position1 << ","
				<< variableDetail.position2 << ","
				<< hashTable->sensorActuatorInfo(variableDetail.specificType)
				<< "," << variableDetail.value << ");" << endl;

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

Printer::~Printer() {

	outputFlow << endl << "fin()" << endl << "return 0;" << endl << "}" << endl;

	outputFlow.close();
}

