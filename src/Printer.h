/*
 * Printer.h
 *
 *  Created on: May 12, 2016
 *      Author: guille
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "Constants.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>

class Printer {

private:

	HashTable *hashTable;

public:
	Printer(HashTable *_hashTable);

	void print(short typeOfSentence, string key);
	void printPause(int seconds);

	~Printer();
};

#endif /* PRINTER_H_ */
