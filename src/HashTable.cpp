/*
 * HashTable.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#include "HashTable.h"


HashTable::HashTable() {
}

HashTable::~HashTable() {

	cout << "Symbol table" << endl;

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << endl;

	cout << setfill(' ') << setw(1) << "|" << setw(15) << left << "Name"
	<< setw(1) << "|" << setw(15) << left << "Type" << setw(1) << "|"
	<< setw(15) << left << "Value" << setw(1) << "|" << endl;

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << endl;

	for (auto it : table) {

		cout << setfill(' ') << setw(1) << "|" << setw(15) << left << it.first
		<< setw(1) << "|" << setw(15) << left << it.second.first
		<< setw(1) << "|" << setw(15) << left << (it.second.first!=constants::TYPEBOOLEAN?myToString(it.second.second):(it.second.second==0)?"falso":"verdadero")
		<< setw(1) << "|" << endl;
	}

	cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+"
	<< setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1)
	<< "+" << endl;
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

void HashTable::insertValue(string key, short type, float value) {

	myToUpper(key);

	pair<short, float> _pair;
	_pair.first = type;
	_pair.second = value;

	myToUpper(key);

	table[key] = _pair;
}

pair<short, float> HashTable::getValueByKey(string key) {

	myToUpper(key);

	return table[key];
}

bool HashTable::checkValueByKey(string key) {

	myToUpper(key);

	return table.find(key) != table.end();
}
