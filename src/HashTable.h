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

class HashTable {

private:

unordered_map <string,pair<short,float>> table;

public:
	HashTable();
	~HashTable();

	string myToString (float value);
	void myToUpper (string &key);
	void insertValue(string key, short type, float value);
	pair<short,float> getValueByKey(string key);
	bool checkValueByKey(string key);
};

#endif /* HASHTABLE_H_ */
