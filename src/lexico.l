%{
#include "expresiones.h"
#include <math.h>
int n_lineas;
%}

%option noyywrap

%%

[Ss][Aa][Ll][Ii][Rr]	return SALIR;

"<="					return LOWEROREQUAL;
">="					return GREATEROREQUAL;
"=="					return EQUALS;
"!="					return NOTEQUALS;

"&&"					return ANDAND;
"||"					return OROR;
"%%"					return SEPARATOR;
"entero"				return DEFINITIONINTEGER;
"real"					return DEFINITIONREAL;
"posicion"				return DEFINITIONPOSITION;
"Sensor"				return DEFINITIONSENSOR;
"Actuador"				return DEFINITIONACTUADOR;
"temperatura"			return SENSORTEMPERATURE;
"luminosidad"			return SENSORBRIGHTNESS;
"humo"					return SENSORSMOKE;
"alarma"				return ACTUADORALARM;
"luz"					return ACTUADORLIGHT;
"si"					return IF;
"sino"					return ELSE;
"repite"				return WHILE;
"activar"				return ACTIVATE;
"desactivar"			return DESACTIVATE;
"pausa"					return PAUSE;
"escribir"				return WRITE /*cadena caracteres comentarios*/;



[A-Za-z_][A-Za-z1-9_]*	yylval.cadena = new char; strcpy(yylval.cadena,yytext);return VARIABLE;
[0-9]+[.][0-9]*			yylval.value = atof(yytext);return REAL;
[0-9]+					yylval.value = atof(yytext);return ENTERO;
\n					    n_lineas++;
[\t ]					;	
. 						return (yytext[0]);
%%
