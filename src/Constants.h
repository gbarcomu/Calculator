/*
 * Constants.h
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace constants {

const short TYPEINTEGER = 0;
const short TYPEREAL = 1;
const short TYPEBOOLEAN = 2;
const short TYPEPOSITION = 8;
const short TYPESENSOR = 9;
const short TYPEACTUATOR = 10;

const short ERRORMODULE = 3;
const short ERRORNONDECLARED = 4;
const short ERRORTYPESNOTMATCH = 5;
const short ERRORLOGICALASSIGNMENT = 6;

const short TYPETEMPERATURE = 11;
const short TYPEBRIGHTNESS = 12;
const short TYPESMOKE = 13;
const short TYPEALARM = 14;
const short TYPELIGHT = 15;

const short OK = 7;

const short PRINTMARKSENSOR = 20;
const short PRINTDISABLEACTUATOR = 21;
const short PRINTENABLEACTUATOR = 22;
const short PRINTVALUESENSOR = 23;
const short PRINTPAUSE = 24;
const short PRINTMESSAGE = 25;


}

#endif /* CONSTANTS_H_ */
