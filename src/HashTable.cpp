/*
 * HashTable.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#include "HashTable.h"


HashTable::HashTable() {
}

string typeToString (short type) {

	string response = "";

	switch (type) {

	case constants::TYPEINTEGER:
		response = "entero";
	break;

	case constants::TYPEREAL:
		response = "real";
	break;

	case constants::TYPEBOOLEAN:
		response = "logico";
	break;

	case constants::TYPEPOSITION:
		response = "posicion";
	break;

	case constants::TYPESENSOR:
		response = "sensor";
	break;

	case constants::TYPEACTUADOR:
		response = "actuador";
	break;
	}

	return response;
}

string sensorExtraInfo(VariableDetail variableDetail) {

	stringstream response;

	switch (variableDetail.type) {

	case constants::TYPESENSOR:
	case constants::TYPEACTUADOR:

		switch (variableDetail.specificType) {

		case constants::TYPETEMPERATURE:
			response << "temperatura";
			break;
		case constants::TYPEBRIGHTNESS:
			response << "brillo";
			break;
		case constants::TYPESMOKE:
			response << "humo";
			break;
		case constants::TYPEALARM:
			response << "alarma";
			break;
		case constants::TYPELIGHT:
			response << "luz";
			break;
		}

		if (variableDetail.type == constants::TYPESENSOR) {
			response << ", " << variableDetail.value3;
		}

		break;

		default :
			response << " ";
	}
	return response.str();
}

string simpleOrPosition (VariableDetail variableDetail){

	stringstream ss;

	switch (variableDetail.type) {

	case constants::TYPEPOSITION:
	case constants::TYPESENSOR:
	case constants::TYPEACTUADOR:

		ss << "<" << variableDetail.value << ", " << variableDetail.value2 << ">";

		break;

	default :
		ss << variableDetail.value;
	}
	return ss.str();
}

HashTable::~HashTable() {

	cout << "Symbol table" << endl;

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << setw(20) << "-" << setw(1) << "+"<< endl;

	cout << setfill(' ') << setw(1) << "|" << setw(15) << left << "Name"
	<< setw(1) << "|" << setw(15) << left << "Type" << setw(1) << "|"
	<< setw(15) << left << "Value" << setw(1) << "|"
	<< setw(20) << left << "Mas" << setw(1) << "|"
	<< endl;

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << setw(20) << "-" << setw(1) << "+"<< endl;

	for (auto it : table) {

		cout << setfill(' ') << setw(1) << "|" << setw(15) << left << it.first
		<< setw(1) << "|" << setw(15) << left << typeToString(it.second.type)
		<< setw(1) << "|" << setw(15) << left << simpleOrPosition(it.second)
		<< setw(1) << "|" << setw(20) << left << sensorExtraInfo(it.second)
		<< setw(1) << "|" << endl;
	}

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << setw(20) << "-" << setw(1) << "+" << endl;
}

void fooler(){}
void foo(int l, string &key) {
	'a'<=key[l]&&key[l]<='z'?key[l]+=-'a'+'A':key[l]+=0;
	l!=0?foo(l-1,key):fooler();
}
void HashTable::myToUpper (string &key) {
	foo(key.length()-1,key);
}

string HashTable::myToString (float value) {

	stringstream ss;
	ss << value;
	return ss.str();
}

void HashTable::insertValue(string key, short type, float value, short specificType, float value2, float value3, bool initialized) {

	myToUpper(key);

	VariableDetail variableDetail;

	variableDetail.specificType = specificType;
	variableDetail.type = type;
	variableDetail.value = value;
	variableDetail.value2 = value2;
	variableDetail.value3 = value3;
	variableDetail.initialized = initialized;

	myToUpper(key);

	table[key] = variableDetail;
}

VariableDetail HashTable::getValueByKey(string key) {

	myToUpper(key);
	return table[key];
}

void HashTable::insertValueStruct(string key, VariableDetail variableDetail) {

	myToUpper(key);
	table[key] = variableDetail;
}

bool HashTable::checkValueByKey(string key) {

	myToUpper(key);

	return table.find(key) != table.end();
}
