/*
 * Printer.cpp
 *
 *  Created on: May 12, 2016
 *      Author: guille
 */

#include "Printer.h"

Printer::Printer(HashTable *_hashTable) {

	hashTable = _hashTable;
}

void Printer::print(short typeOfSentence, string key){

	switch (typeOfSentence) {

	default:

		cout << "hola" << endl;
	}
}

void Printer::printPause(int seconds) {

	cout << "hola" << endl;
}

Printer::~Printer() {

}

