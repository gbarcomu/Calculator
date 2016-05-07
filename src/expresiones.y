
%{

#include <iostream>
#include <cmath>
#include "HashTable.h"
#include "ErrorController.h"	
	
using namespace std;

//elementos externos al analizador sintácticos por haber sido declarados en el analizador léxico      			
extern int n_lineas;
extern int yylex();

bool isReal;
HashTable *hashTable;
ErrorController *errorController;

////definición de procedimientos auxiliares
void yyerror(const char* s){         /*    llamada por cada error sintactico de yacc */

    cout << "Error sintáctico en la línea "<< n_lineas <<endl;	
} 

void prompt(){
  	cout << "$> ";
}

float getValue(string key) {
	pair<short,float> _pair = hashTable->getValueByKey(key);
	return _pair.second;
}

short getType(string key) {
	pair<short,float> _pair = hashTable->getValueByKey(key);
	return _pair.first;
}

void setValue(string key, short type, float value) {
	
	hashTable->insertValue(key,type,value);
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
	
	return correct;
}

string parseTypeToString(short type) {
	
	return (type==constants::TYPEINTEGER)?"entero":(type==constants::TYPEREAL)?"real":"lógico";
}

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

SHoLProgram: definitionZone SEPARATOR dataZone SEPARATOR behaviourZone {cout << "programa" << endl;}
	;

definitionZone:
	| definitionZone definition {cout << "definicion" << endl;}
	| definitionZone declaration {cout << "declaracion" << endl;}
	| definitionZone asignacion {cout << "asignacion" << endl;}
	;
	
definition: DEFINITIONSENSOR VARIABLE sensorOrActivator pair';'
	| DEFINITIONACTUADOR VARIABLE sensorOrActivator pair ';'
	;

sensorOrActivator: SENSORTEMPERATURE
	| SENSORBRIGHTNESS
	| SENSORSMOKE
	| ACTUADORALARM
	| ACTUADORLIGHT
	;

variables: VARIABLE
	| variables ',' VARIABLE
	;


dataZone:
	| dataZone data
	;	

data: VARIABLE REAL ';'
	| VARIABLE ENTERO ';'		
	
behaviourZone:
	| behaviourZone behaviour
	| behaviourZone asignacion
	| behaviourZone action
	;
	
behaviour: IF '(' expresionLogica ')' '[' behaviourZone ']' ';'
	| ELSE '[' behaviourZone ']' ';'
	| WHILE ENTERO '[' behaviourZone ']' ';'
	;

actions: action ';'
	| actions action

action: ACTIVATE VARIABLE ENTERO
	| DESACTIVATE VARIABLE ENTERO
	| ACTIVATE VARIABLE
	| DESACTIVATE VARIABLE
	| PAUSE ENTERO

declaration: DEFINITIONINTEGER variables ';'
	| DEFINITIONREAL variables ';'
	| DEFINITIONPOSITION variables ';'
	;

pair : '<' ENTERO ',' ENTERO '>'
	;	

asignacion: VARIABLE '=' expresionLogica ';' { 
	if (checkType($1,constants::TYPEBOOLEAN)){
		printMessagge($1,$3, constants::TYPEBOOLEAN);
		setValue($1,2,$3);
	}
	else {
		errorController->errorCatcher(constants::ERRORTYPESNOTMATCH, $1, parseTypeToString(getType($1)).c_str(), "lógico");		
	}
}
       | VARIABLE '=' expresionAritmetica ';' { 
    if (checkType($1,(isReal)?constants::TYPEREAL:constants::TYPEINTEGER)){	   
    	printMessagge($1,$3, (isReal)?constants::TYPEREAL:constants::TYPEINTEGER);
    	setValue($1,(isReal)?1:0,$3);
    }
    else {
    	errorController->errorCatcher(constants::ERRORTYPESNOTMATCH, $1, parseTypeToString(getType($1)).c_str(), (isReal)?"real":"entero");	
    }
};    	   
    	   


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
       | expresionAritmetica '>' expresionAritmetica              {$$=($1>$3)?true:false;}
       | expresionAritmetica '<' expresionAritmetica              {$$=($1<$3)?true:false;}

       | expresionLogica ANDAND expresionLogica                   {$$=($1&&$3)?true:false;}
       | expresionLogica OROR expresionLogica                     {$$=($1||$3)?true:false;}
       | '!' expresionLogica                                      {$$=(!$2)?true:false;}
       | '(' expresionLogica ')'                                  {$$=$2;};  

%%

int main(){
     
     n_lineas = 0;
     isReal = false;
     
     hashTable = new HashTable();
     errorController = new ErrorController();
         
     yyparse();
     
     
     delete hashTable;
     delete errorController;
     
     return 0;
}







