/*
 * HashTable.h
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "Constants.h"
using namespace std;

struct VariableDetail {

	short type;
	short specificType;
	float value;
	float position1;
	float position2;
};

class HashTable {

private:

unordered_map <string,VariableDetail> table;

bool printTable;

public:
	HashTable();
	void printHashTable();
	~HashTable();

	void dontPrintTable();

	string myToString (float value);
	void myToUpper (string &key);
	string sensorActuatorInfo(short specificType);

	void insertValue (string key, VariableDetail variableDetail);
	VariableDetail getValueByKey(string key);
	bool checkValueByKey(string key);
	string typeToString (short type);
};

#endif /* HASHTABLE_H_ */
