/*
 * HashTable.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#include "HashTable.h"


HashTable::HashTable() {
}

/**************PARSING METHODS********************************************/

string HashTable::typeToString (short type) {

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

	case constants::TYPEACTUATOR:
		response = "actuador";
	break;
	}

	return response;
}

string HashTable::sensorActuatorInfo(short specificType) {

	stringstream response;

	switch (specificType) {

	case constants::TYPETEMPERATURE:
		response << "Temperatura";
		break;
	case constants::TYPEBRIGHTNESS:
		response << "Brillo";
		break;
	case constants::TYPESMOKE:
		response << "Humo";
		break;
	case constants::TYPEALARM:
		response << "Alarma";
		break;
	case constants::TYPELIGHT:
		response << "Luz";
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
	case constants::TYPEACTUATOR:

		ss << "<" << variableDetail.position1 << ", " << variableDetail.position2 << ">";

		break;

	default :
		ss << variableDetail.value;
	}
	return ss.str();
}

/***********************************Helpers**********************************************/

/* Where the magic happens :)*/
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

/****************************************************CRUD*****************************************/

VariableDetail HashTable::getValueByKey(string key) {

	myToUpper(key);
	return table[key];
}

void HashTable::insertValue(string key, VariableDetail variableDetail) {

	myToUpper(key);
	table[key] = variableDetail;
}

bool HashTable::checkValueByKey(string key) {

	myToUpper(key);

	return table.find(key) != table.end();
}

/****************************************************************************************************/

HashTable::~HashTable() {

	/* Printing symbol table */

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
		<< setw(1) << "|" << setw(20) << left << sensorActuatorInfo(it.second.specificType)
		<< setw(1) << "|" << endl;
	}

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << setw(20) << "-" << setw(1) << "+" << endl;
}
