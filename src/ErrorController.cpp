/*
 * ErrorController.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#include "ErrorController.h"

ErrorController::ErrorController(Printer *_printer) {

	printer = _printer;
}

void ErrorController::errorCatcher(short errorCode, const char* parameter1,
		const char* parameter2, const char* parameter3) {

	printer->dontGenerateFile();

	cout << "Error semántico en la línea " << n_lineas << ", ";


	switch (errorCode) {

	case constants::ERRORPOSITIONINARITHMETIC:
		cout << "se ha utilizado la variable " << parameter1 << " de tipo posición en una operación aritmética"
				<< endl;
		break;

	case constants::ERRORNONDECLARED:
		cout << "la variable " << parameter1 << " no ha sido definida"
				<< endl;
		break;

	case constants::ERRORREDEFINED:
		cout << "se ha cambiado el tipo de la variable " << parameter1 << " de tipo posición"
				<< endl;
		break;
	}
}

ErrorController::~ErrorController() {
	// TODO Auto-generated destructor stub
}

