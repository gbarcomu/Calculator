
%{

#include <iostream>
#include <cmath>
#include <stack>
#include <list>
#include "HashTable.h"
#include "ErrorController.h"
#include "Printer.h"
	
using namespace std;
     			
extern int n_lineas;
extern int yylex();
extern FILE *yyin;

// Determines if a parameter is real or integer
bool isReal;
// Determines if a line should be executed depending on an if clause
bool execute;
// Determines how many times you have to execute an instruction depending on a while clause
int whileTimes;
// Determines if we are inside a while loop
bool inWhile;

// Store variables with its values and all the necesary information
HashTable *hashTable;
// Manages semantic errors
ErrorController *errorController;
// Create cpp code
Printer *printer;

// Stack used to keep variables before defining them
stack <string> variablesSeparatedComma;
// List used to keep instructions that are inside a while and repeat them later
list <pair<short,string>> whileInstructions;


void yyerror(const char* s){

    cout << "Error sintáctico en la línea "<< n_lineas <<endl;	
} 

/***********************************Symbol Table Methods**********************************************/

/*
 * Return values, not positions
 */
float getValue(string key) {
	
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	return variableDetail.value;
}

/*
 * Get a position as a pair from a variable type position
 */
pair<float,float> getPosition(string key) {
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	pair<float,float> _pair;
	_pair.first = variableDetail.position1;
	_pair.second = variableDetail.position2;
	
	return _pair;
}

/*
 * Get the type of a variable
 */
short getType(string key) {
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	return variableDetail.type;
}

/*
 * Set the value of a sensor or simple types, neither positions nor actuators!
 */
void setValue(string key, float value) {
	
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	variableDetail.value = value;
	hashTable->insertValue(key,variableDetail);
}

/*
 * Set the position of a sensor, activator or a position!
 */
void setPosition(string key, float position1, float position2) {
	
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	variableDetail.position1 = position1;
	variableDetail.position2 = position2;
	hashTable->insertValue(key,variableDetail);
}

/*
 * Use this to create a simple variable with its type and no value
 */
void initializeValue(string key, short type) {
	
	VariableDetail variableDetail;
	variableDetail.type = type;
	hashTable->insertValue(key,variableDetail);
}

/*
 * Create variable type Sensor or Actuator giving two parameters for positions
 */
void initializeSensor(string key, short type, float position1, float position2, short specificType) {
	
	VariableDetail variableDetail;
	variableDetail.type = type;
	variableDetail.position1 = position1;
	variableDetail.position2 = position2;
	variableDetail.specificType = specificType;
	
	hashTable->insertValue(key,variableDetail);
}

/*
 * Create variable type Sensor or Actuator using a position variable
 */
void initializeSensorWithPosition(string key, short type, string positionName, short specificType) {
	
	pair<float,float> _pair = getPosition(positionName);
	VariableDetail variableDetail;
	variableDetail.type = type;
	variableDetail.position1 = _pair.first;
	variableDetail.position2 = _pair.second;
	variableDetail.specificType = specificType;
	
	hashTable->insertValue(key,variableDetail);
}

/*
 * Create message with information and position
 */
string createMessageWithPair(string text, float position1, float position2) {
	
	ostringstream oss;
	oss << text << ", " << position1 << "," << position2;
	return oss.str();
}

string createMessageWithPosition(string text, string key) {
	
	pair<float,float> _pair = getPosition(key);
	ostringstream oss;
	oss << text << ", " << _pair.first << "," << _pair.second;
	return oss.str();
}

%}

%union{

  short typeOfVariable;
  float value;
  char* cadena;
  bool logico;
} 

%start SHoLProgram /* Starting symbol */


/* Tokens */
%token EQUALS LOWEROREQUAL GREATEROREQUAL NOTEQUALS
%token SEPARATOR /* %% */
%token <cadena> VARIABLE
%token <cadena> TEXT
%token <value> ENTERO
%token <value> REAL
%token <value> IDENTIFICADOR
/* Kind of sensors and activadores */
%token DEFINITIONSENSOR DEFINITIONACTUATOR
%token SENSORTEMPERATURE SENSORBRIGHTNESS SENSORSMOKE ACTUATORALARM ACTUATORLIGHT
/* Actions */
%token ACTIVATE DESACTIVATE PAUSE WRITE
%token DEFINITIONINTEGER DEFINITIONREAL DEFINITIONPOSITION
/* Control structures */
%token IF ELSE WHILE

/* Types */
%type <value> arithmeticExpression
%type <logico> logicExpression
%type <typeOfVariable> sensorOrActuator
%type <cadena> text

/* Priority table */
%left '+' '-' 
%left '*' '/' '%' 
%right '^' 
%left '(' ')'
%left menosunario

%%

/* SHoL program consists on three zones separated by %%
 * First- Definitions: Initialize variables, set variables values and declare sensors and actuators
 * Second- Data: In this part sensors receives data
 * Third- Behaviour: In this part are allowed actions with actuadores depending on sensors values
 * control instructions (if,else,while) and also set variables, print messages and pauses
 */
SHoLProgram: definitionZone SEPARATOR dataZone SEPARATOR behaviourZone
	;

definitionZone:
	| definitionZone definition 
	| definitionZone declaration 
	| definitionZone assignment 
	;

/* Here are recognised sensor and actuators definition with either a couple of values or a position variable */	
definition: DEFINITIONSENSOR VARIABLE sensorOrActuator '<' ENTERO ',' ENTERO '>'';' {initializeSensor($2, constants::TYPESENSOR, $5, $7, $3); printer->print(constants::PRINTMARKSENSOR,$2);}
	| DEFINITIONACTUATOR VARIABLE sensorOrActuator '<' ENTERO ',' ENTERO '>' ';' {initializeSensor($2, constants::TYPEACTUATOR, $5, $7, $3);printer->print(constants::PRINTDISABLEACTUATOR,$2);}
	| DEFINITIONSENSOR VARIABLE sensorOrActuator VARIABLE ';' {initializeSensorWithPosition($2, constants::TYPESENSOR, $4, $3); printer->print(constants::PRINTMARKSENSOR,$2);}	
	| DEFINITIONACTUATOR VARIABLE sensorOrActuator VARIABLE ';' {initializeSensorWithPosition($2, constants::TYPEACTUATOR, $4, $3);printer->print(constants::PRINTDISABLEACTUATOR,$2);}
	;

/* Determines which kind of sensor or actuator is*/
sensorOrActuator: SENSORTEMPERATURE {$$ = constants::TYPETEMPERATURE;}
	| SENSORBRIGHTNESS				 {$$ = constants::TYPEBRIGHTNESS;}
	| SENSORSMOKE					 {$$ = constants::TYPESMOKE;}
	| ACTUATORALARM					 {$$ = constants::TYPEALARM;}
	| ACTUATORLIGHT					 {$$ = constants::TYPELIGHT;}
	;

/* This zone is defined recursively as a set of data instructions */
dataZone:
	| dataZone data
	;	

/* Here is where sensors take data that could be either integer or real */
data: VARIABLE REAL ';' {setValue($1,$2);printer->print(constants::PRINTVALUESENSOR,$1);}
	| VARIABLE ENTERO ';' {setValue($1,$2);printer->print(constants::PRINTVALUESENSOR,$1);}
	;

/* In this part we could have actions, control sentences or variable assignments*/
behaviourZone:
	| behaviourZone behaviour
	| behaviourZone assignment
	| behaviourZone actions
	;

/* Three control productions */
behaviour: IF condition '[' behaviourZone ']' ';' 						   {execute = true;}
	| IF condition '[' behaviourZone ']' _else '[' behaviourZone ']' ';'   {execute = true;}
	| _while repeat '[' behaviourZone ']' ';'	  						   
	{
		/*Repeat the instructions inside the list*/
		for (int i = 0; i < whileTimes; i++) { 
			
			for (std::list <pair<short,string>>::iterator it=whileInstructions.begin(); it != whileInstructions.end(); ++it) {
				
				pair<short,string> _pair = (pair<short,string>)*it; 
				printer->print(_pair.first, _pair.second);
			}	
		}
		whileInstructions.clear(); /* Empties the list */
		inWhile = false;
	}
	;

/* Foo production that allow to switch boolean condition*/
_else: ELSE 			  												   {execute = !execute;}
	;
/* Foo production that allow to set true boolean condition*/
_while: WHILE  															   {inWhile = true;}
	;

/* Foo production that allow to change execute variable depending on the if clause */
condition: logicExpression {if(!$1) {execute = false;}}
	;

/* Foo production that set the times that a production should be repeated*/
repeat: ENTERO {whileTimes = $1;}

/* Activate desactivate pause write, defined recursively*/
actions: action ';'
	| actions action ';'
	;

action: ACTIVATE VARIABLE ENTERO /* activate a actuator, pause of n seconds and desactivates the actuator*/ 
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTENABLEACTUATOR,$2);printer->printPause($3);printer->print(constants::PRINTDISABLEACTUATOR,$2);;
			}
			else {
				
				whileInstructions.push_back(make_pair(constants::PRINTENABLEACTUATOR,$2));
				
				/*Using printer class in an incorrect way, second value is the number of seconds
				 * of the pause parsed as a string
				 */
				ostringstream oss;
				oss << $3;
				whileInstructions.push_back(make_pair(constants::PRINTPAUSE,oss.str()));
				whileInstructions.push_back(make_pair(constants::PRINTDISABLEACTUATOR,$2));
			}
		}
	}
	| ACTIVATE VARIABLE 
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTENABLEACTUATOR,$2);
			}
			else {
				
				whileInstructions.push_back(make_pair(constants::PRINTENABLEACTUATOR,$2));
			}
		}
	}
	| DESACTIVATE VARIABLE
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTDISABLEACTUATOR,$2);
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTDISABLEACTUATOR,$2));
			}
		}
	}
	| PAUSE ENTERO
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->printPause($2);
			}
			else {
				
				ostringstream oss;
				oss << $2;
				whileInstructions.push_back(make_pair(constants::PRINTPAUSE,oss.str()));
			}
		}
	}
	| WRITE text /*Type a message, position given by a pair or a position is optional*/
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTMESSAGE,createMessageWithPair($2,0,0));
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPair($2,0,0)));
			}
		}
	}
	| WRITE '<' arithmeticExpression ',' arithmeticExpression '>' text
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTMESSAGE,createMessageWithPair($7,$3,$5));
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPair($7,$3,$5)));
			}
		}
	}
	| WRITE VARIABLE text 
	{
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTMESSAGE,createMessageWithPosition($3,$2));
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPosition($3,$2)));
			}
		}
	}
	;

text: TEXT {$$ = $1;} 
	| arithmeticExpression  /* Method to convert the arithmetic expression to " value " as a char* */
	{
		ostringstream oss;
		oss << "\"" << $1 << "\"";
		string var = oss.str();
		char* c;
		strcpy(c, var.c_str());
		$$ = c;
	}
	| logicExpression
	{
		ostringstream oss;
		oss << "\"" << $1 << "\"";
		string var = oss.str();
		char* c;
		strcpy(c, var.c_str());
		$$ = c;
	}
	;
	
/* Empties the stack and declares the variables */
declaration: DEFINITIONINTEGER variables ';' 
    {
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEINTEGER);
			variablesSeparatedComma.pop();
		}
    }
	| DEFINITIONREAL variables ';' 			 
	{
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEREAL);
			variablesSeparatedComma.pop();
		}
	}
	| DEFINITIONPOSITION variables ';'       
	{
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEPOSITION);
			variablesSeparatedComma.pop();
		}
	}
	;

/*
 * Keep in a stack all the variables defined as:
 * type a,b,c,d;
 * In declaration insert the values in the symbol table with the specified type
 */
variables: VARIABLE {variablesSeparatedComma.push($1);}
	| variables ',' VARIABLE {variablesSeparatedComma.push($3);}
	;

/* 
 * Recognises an assignment like any other programming lenguage like
 * a = 5 * b;
 * Just works with real and integers
 */	
assignment: VARIABLE '=' arithmeticExpression ';' 
	{ 
	setValue($1, $3);
	isReal = false;
	}    
    | VARIABLE '=' '<' arithmeticExpression ',' arithmeticExpression '>' ';'{setPosition($1,$4,$6);}    	       	 
    ;    	   
    	   
/*
 * This part detects an arithmetic expression that could have variables, for example
 *  a + 5
 *  6.7 / 5.0
 */
arithmeticExpression:    ENTERO                                {$$=$1;}
	   |                REAL                                  {$$=$1; isReal = true;} 
       |                VARIABLE                         	  {$$=getValue($1);if(getType($1)==constants::TYPEREAL){isReal = true;}}
       | '-' arithmeticExpression  %prec menosunario           {$$=-$2;}
       | '(' arithmeticExpression ')'                          {$$=$2;}                   
       | arithmeticExpression '+' arithmeticExpression 		  {$$=$1+$3;}              
       | arithmeticExpression '-' arithmeticExpression    	  {$$=$1-$3;}            
       | arithmeticExpression '*' arithmeticExpression          {$$=$1*$3;} 
       | arithmeticExpression '/' arithmeticExpression          {$$=$1/$3;} 
       | arithmeticExpression '%' arithmeticExpression          {$$=(int)$1%(int)$3;} 
       | arithmeticExpression '^' arithmeticExpression          {$$=pow($1,$3);}
       ;

/*
 * This part evaluates two arithmetic expressions and returns true or false
 */
logicExpression: arithmeticExpression EQUALS arithmeticExpression   {$$=($1==$3)?true:false;}
       | arithmeticExpression NOTEQUALS arithmeticExpression        {$$=($1!=$3)?true:false;}
       | arithmeticExpression GREATEROREQUAL arithmeticExpression   {$$=($1>=$3)?true:false;}
       | arithmeticExpression LOWEROREQUAL arithmeticExpression     {$$=($1<=$3)?true:false;}
       | arithmeticExpression '>' arithmeticExpression              {$$=($1>$3)?true:false;}
       | arithmeticExpression '<' arithmeticExpression              {$$=($1<$3)?true:false;}

%%

int main(int argc,char *argv[]){
     
     n_lineas = 0;
     isReal = false;
     execute = true;
     whileTimes = 1;
     inWhile = false;
     
     hashTable = new HashTable();
     errorController = new ErrorController();
     printer = new Printer(hashTable, argv[1]);
     
     FILE *inputFile = fopen(argv[1], "r");
     yyin = inputFile;
     yyparse();
     
     
     delete hashTable;
     delete errorController;
     delete printer;
     
     return 0;
}