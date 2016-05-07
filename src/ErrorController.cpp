/*
 * ErrorController.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#include "ErrorController.h"

ErrorController::ErrorController() {
	// TODO Auto-generated constructor stub

}

void ErrorController::errorCatcher(short errorCode, const char* parameter1,
		const char* parameter2, const char* parameter3) {

	cout << "Error semántico en la línea " << n_lineas << ", ";

	switch (errorCode) {

	case constants::ERRORMODULE:
		cout << "el operador % no se puede usar con datos reales"
				<< endl;
		break;

	case constants::ERRORNONDECLARED:
		cout << "la variable " << parameter1 << " no ha sido definida"
				<< endl;
		break;

	case constants::ERRORTYPESNOTMATCH:
		cout << "la variable " << parameter1 << " es de tipo " << parameter2
				<< " y no se le puede asignar un valor " << parameter3 << endl;
		break;

	case constants::ERRORLOGICALASSIGNMENT:
		cout << "no se pueden realizar operaciones aritméticas con variables de tipo lógico" << endl;
		break;
	}
}

ErrorController::~ErrorController() {
	// TODO Auto-generated destructor stub
}

