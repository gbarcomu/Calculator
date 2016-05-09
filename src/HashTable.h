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
	float value2;
	float value3;
	bool initialized;
};

class HashTable {

private:

unordered_map <string,VariableDetail> table;

public:
	HashTable();
	~HashTable();

	string myToString (float value);
	void myToUpper (string &key);
	void insertValue(string key, short type, float value = 0, short specificType = 0, float value2 = 0, float value3 = 0, bool initialized = false);

	void insertValueStruct (string key, VariableDetail variableDetail);

	VariableDetail getValueByKey(string key);
	bool checkValueByKey(string key);
};

#endif /* HASHTABLE_H_ */
