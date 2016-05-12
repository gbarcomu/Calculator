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
	ofstream outputFlow;

	void init();

public:
	Printer(HashTable *_hashTable, string outputName);

	void print(short typeOfSentence, string key);

	void printPause(int seconds);
	void printEndLine();

	~Printer();
};

#endif /* PRINTER_H_ */
