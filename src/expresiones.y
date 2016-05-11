
%{

#include <iostream>
#include <cmath>
#include <stack>
#include "HashTable.h"
#include "ErrorController.h"	
	
using namespace std;

//elementos externos al analizador sintácticos por haber sido declarados en el analizador léxico      			
extern int n_lineas;
extern int yylex();

bool isReal;
bool execute;
HashTable *hashTable;
ErrorController *errorController;

stack <string> variablesSeparatedComma;

////definición de procedimientos auxiliares
void yyerror(const char* s){         /*    llamada por cada error sintactico de yacc */

    cout << "Error sintáctico en la línea "<< n_lineas <<endl;	
} 

void prompt(){
  	cout << "$> ";
}

float getValue(string key) {
	
	float response;
	
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	
	if (variableDetail.type == constants::TYPESENSOR or variableDetail.type == constants::TYPEACTUADOR) {
		
		response = variableDetail.value3;
	}
	
	else {
		
		response = variableDetail.value;
	}
	
	return response;
}

VariableDetail getAll(string key) {
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	return variableDetail;
}

pair<float,float> getPair(string key) {
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	pair<float,float> _pair;
	_pair.first = variableDetail.value;
	_pair.second = variableDetail.value2;
	
	return _pair;
}

short getType(string key) {
	VariableDetail variableDetail = hashTable->getValueByKey(key);
	return variableDetail.type;
}

void setValue(string key, short type, float value, float value2 = 0) {
	
	VariableDetail variableDetail = getAll(key);
	variableDetail.value = value;
	variableDetail.value2 = value2;
	hashTable->insertValueStruct(key,variableDetail);
}

void setSensor(string key, float value3) {
	
	VariableDetail variableDetail = getAll(key);
	variableDetail.value3 = value3;
	hashTable->insertValueStruct(key,variableDetail);
}

void initializeValue(string key, short type) {
	
	hashTable->insertValue(key,type);
}

void initializeSensor(string key, short type, float value, short specificType, float value2) {
	
	hashTable->insertValue(key,type,value,specificType,value2);
}

void initializeSensorWithPair(string key, short type, string pairName, short specificType) {
	
	pair<float,float> _pair = getPair(pairName);
	
	hashTable->insertValue(key,type,_pair.first,specificType,_pair.second);
}

bool valueExists(string key) {
	
	return hashTable->checkValueByKey(key);
}

bool checkType(string key, short type) {
	
	bool correct = true;
	
	if (valueExists(key)) {
		
		if (getType(key) != type) {
			
			correct = false;
		}
	}
	
	else {
		
		correct = false;
	}
	
	return correct;
}

string parseTypeToString(short type) {
	
	return (type==constants::TYPEINTEGER)?"entero":(type==constants::TYPEREAL)?"real":"lógico";
}

/**************************************************************/

void printMarcaSensor(string key) {
	
	VariableDetail variableDetail = getAll(key);
	cout << "marca_sensor(" << variableDetail.value << "," 
			<< variableDetail.value2 << "," 
			<< hashTable->sensorActivatorInfo(variableDetail.specificType) << ",\"" 
			<< key << "\"); pausa (1)" << endl;
}

void printDesactivarActuador(string key) {
	
	VariableDetail variableDetail = getAll(key);
	cout << "desactivar_actuador(" << variableDetail.value << "," 
			<< variableDetail.value2 << "," 
			<< hashTable->sensorActivatorInfo(variableDetail.specificType) << ",\"" 
			<< key << "\"); pausa (1)" << endl;
}

void printActivarActuador(string key) {
	
	VariableDetail variableDetail = getAll(key);
	cout << "activar_actuador(" << variableDetail.value << "," 
			<< variableDetail.value2 << "," 
			<< hashTable->sensorActivatorInfo(variableDetail.specificType) << ",\"" 
			<< key << "\"); pausa (1)" << endl;
}


void printValorSensor(string key) {
	
	VariableDetail variableDetail = getAll(key);
	cout << "valor_sensor(" << variableDetail.value << "," 
			<< variableDetail.value2 << "," 
			<< hashTable->sensorActivatorInfo(variableDetail.specificType) << ",\"" 
			<< variableDetail.value3 << "\"); pausa (1)" << endl;
}

/**************************************************************/


void printMessagge(string id, float value, short type) {
	
	cout << "La instrucción " << n_lineas << " hace que la variable " << id;
	
	switch (type) {
		
	case constants::TYPEINTEGER:		
		cout << ", de tipo entero, tenga el valor " << value << endl;
		break;
		
	case constants::TYPEREAL:
		cout << ", de tipo real, tenga el valor " << value << endl;
		break;
	
	case constants::TYPEBOOLEAN:
		cout << ", de tipo lógico, tenga el valor " << ((value!=0)?"verdadero":"falso") << endl;
		break;
	}
}

%}

%union{

  short typeOfThing;
  float value;
  char* cadena;
  bool logico;
} 

%start SHoLProgram
%token SALIR 
%token EQUALS LOWEROREQUAL GREATEROREQUAL NOTEQUALS ANDAND OROR SEPARATOR
%token <cadena> VARIABLE
%token <value> ENTERO
%token <value> REAL
%token <value> IDENTIFICADOR
%type <value> expresionAritmetica
%type <logico> expresionLogica

%type <typeOfThing> sensorOrActivator

%token DEFINITIONSENSOR DEFINITIONACTUADOR SENSORTEMPERATURE SENSORBRIGHTNESS SENSORSMOKE ACTUADORALARM ACTUADORLIGHT
%token ACTIVATE DESACTIVATE PAUSE WRITE
%token DEFINITIONINTEGER DEFINITIONREAL DEFINITIONPOSITION
%token IF ELSE WHILE

%left '+' '-' 
%left '*' '/' '%' 
%right '^' 
%left '(' ')'
%left menosunario

%%

SHoLProgram: definitionZone SEPARATOR dataZone SEPARATOR behaviourZone
	;

definitionZone:
	| definitionZone definition 
	| definitionZone declaration 
	| definitionZone asignacion 
	;
	
definition: DEFINITIONSENSOR VARIABLE sensorOrActivator '<' ENTERO ',' ENTERO '>'';' {initializeSensor($2, constants::TYPESENSOR, $5, $3, $7); printMarcaSensor($2);}
	| DEFINITIONACTUADOR VARIABLE sensorOrActivator '<' ENTERO ',' ENTERO '>' ';' {initializeSensor($2, constants::TYPEACTUADOR, $5, $3, $7);printDesactivarActuador($2);}
	| DEFINITIONSENSOR VARIABLE sensorOrActivator VARIABLE ';' {initializeSensorWithPair($2, constants::TYPESENSOR, $4, $3); printMarcaSensor($2);}	
	| DEFINITIONACTUADOR VARIABLE sensorOrActivator VARIABLE ';' {initializeSensorWithPair($2, constants::TYPEACTUADOR, $4, $3);printDesactivarActuador($2);}
	;

sensorOrActivator: SENSORTEMPERATURE {$$ = constants::TYPETEMPERATURE;}
	| SENSORBRIGHTNESS				 {$$ = constants::TYPEBRIGHTNESS;}
	| SENSORSMOKE					 {$$ = constants::TYPESMOKE;}
	| ACTUADORALARM					 {$$ = constants::TYPEALARM;}
	| ACTUADORLIGHT					 {$$ = constants::TYPELIGHT;}
	;

dataZone:
	| dataZone data
	;	

data: VARIABLE REAL ';' {setSensor($1,$2);printValorSensor($1);}
	| VARIABLE ENTERO ';' {setSensor($1,$2);printValorSensor($1);}
	;
	
behaviourZone:
	| behaviourZone behaviour
	| behaviourZone asignacion
	| behaviourZone actions
	;
	
behaviour: IF condition '[' behaviourZone ']' ';' {execute = true;}
	| ELSE '[' behaviourZone ']' ';'
	| WHILE ENTERO '[' behaviourZone ']' ';'
	;

condition: expresionLogica {if(!$1) {execute = false;} cout << $1 << endl;}
	;

actions: action ';'
	| actions action ';'
	;

action: ACTIVATE VARIABLE ENTERO
	| DESACTIVATE VARIABLE ENTERO
	| ACTIVATE VARIABLE {if(execute){printActivarActuador($2);}}
	| DESACTIVATE VARIABLE
	| PAUSE ENTERO
	;

declaration: DEFINITIONINTEGER variables ';' {while(!variablesSeparatedComma.empty()){initializeValue(variablesSeparatedComma.top(), constants::TYPEINTEGER);variablesSeparatedComma.pop();}}
	| DEFINITIONREAL variables ';' 			 {while(!variablesSeparatedComma.empty()){initializeValue(variablesSeparatedComma.top(), constants::TYPEREAL);variablesSeparatedComma.pop();}}
	| DEFINITIONPOSITION variables ';'       {while(!variablesSeparatedComma.empty()){initializeValue(variablesSeparatedComma.top(), constants::TYPEPOSITION);variablesSeparatedComma.pop();}}
	;

variables: VARIABLE {variablesSeparatedComma.push($1);}
	| variables ',' VARIABLE {variablesSeparatedComma.push($3);}
	;

pair : '<' ENTERO ',' ENTERO '>'
	;	

asignacion: VARIABLE '=' expresionLogica ';' { 
//	if (checkType($1,constants::TYPEBOOLEAN)){
//		printMessagge($1,$3, constants::TYPEBOOLEAN);
//		setValue($1,constants::TYPEBOOLEAN,$3);
//	}
//	else {
//		errorController->errorCatcher(constants::ERRORTYPESNOTMATCH, $1, parseTypeToString(getType($1)).c_str(), "lógico");		
//	}
}
       | VARIABLE '=' expresionAritmetica ';' { setValue($1,constants::TYPEREAL,$3);
//    if (checkType($1,(isReal)?constants::TYPEREAL:constants::TYPEINTEGER)){	   
//    	printMessagge($1,$3, (isReal)?constants::TYPEREAL:constants::TYPEINTEGER);
//    	setValue($1,(isReal)?constants::TYPEREAL:constants::TYPEINTEGER,$3);
//    }
//    else {
//    	errorController->errorCatcher(constants::ERRORTYPESNOTMATCH, $1, parseTypeToString(getType($1)).c_str(), (isReal)?"real":"entero");	
//    }
}    
       | VARIABLE '=' '<' expresionAritmetica ',' expresionAritmetica '>' ';'{setValue($1,constants::TYPEPOSITION,$4,$6);}    	       	 
       ;    	   
    	   


expresionAritmetica:    ENTERO                                {$$=$1;}
	   |                REAL                                  {$$=$1; isReal = true;} 
       |                VARIABLE                         	  {
    	   if(!valueExists($1)){
    		   errorController->errorCatcher(constants::ERRORNONDECLARED, $1);
    		   YYERROR;
    	   }else {
    		   $$=getValue($1);
    		   if(checkType($1,constants::TYPEREAL)){
    			   isReal = true;
    		   }
    		   else if(checkType($1,constants::TYPEBOOLEAN)) {
    			   
    			   errorController->errorCatcher(constants::ERRORLOGICALASSIGNMENT);
    			   YYERROR;
    		   }
    	   }
       } 
       | '-' expresionAritmetica  %prec menosunario           {$$=-$2;}
       | '(' expresionAritmetica ')'                          {$$=$2;}                   
       | expresionAritmetica '+' expresionAritmetica 		  {$$=$1+$3;}              
       | expresionAritmetica '-' expresionAritmetica    	  {$$=$1-$3;}            
       | expresionAritmetica '*' expresionAritmetica          {$$=$1*$3;} 
       | expresionAritmetica '/' expresionAritmetica          {$$=$1/$3;} 
       | expresionAritmetica '%' expresionAritmetica          {if(isReal){errorController->errorCatcher(constants::ERRORMODULE);YYERROR;}else{$$=(int)$1%(int)$3;}} 
       | expresionAritmetica '^' expresionAritmetica          {$$=pow($1,$3);}
       ;

expresionLogica: expresionAritmetica EQUALS expresionAritmetica   {$$=($1==$3)?true:false;}
       | expresionAritmetica NOTEQUALS expresionAritmetica        {$$=($1!=$3)?true:false;}
       | expresionAritmetica GREATEROREQUAL expresionAritmetica   {$$=($1>=$3)?true:false;}
       | expresionAritmetica LOWEROREQUAL expresionAritmetica     {$$=($1<=$3)?true:false;}
       | expresionAritmetica '>' expresionAritmetica              {$$=($1>$3)?true:false; cout << $1 << " " << $3 << endl;}
       | expresionAritmetica '<' expresionAritmetica              {$$=($1<$3)?true:false;}

       | expresionLogica ANDAND expresionLogica                   {$$=($1&&$3)?true:false;}
       | expresionLogica OROR expresionLogica                     {$$=($1||$3)?true:false;}
       | '!' expresionLogica                                      {$$=(!$2)?true:false;}
       | '(' expresionLogica ')'                                  {$$=$2;};  

%%

int main(){
     
     n_lineas = 0;
     isReal = false;
     execute = true;
     
     hashTable = new HashTable();
     errorController = new ErrorController();
         
     yyparse();
     
     
     delete hashTable;
     delete errorController;
     
     return 0;
}







