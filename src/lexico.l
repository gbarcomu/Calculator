%{
#include "expresiones.h"
#include <math.h>
int n_lineas;
%}

%option noyywrap

%x COM

%%

"#"						BEGIN(COM);
<COM>"\n"				BEGIN(0);

<COM>.					;

"<="					return LOWEROREQUAL;
">="					return GREATEROREQUAL;
"=="					return EQUALS;
"!="					return NOTEQUALS;

"%%"					return SEPARATOR;
"entero"				return DEFINITIONINTEGER;
"real"					return DEFINITIONREAL;
"posicion"				return DEFINITIONPOSITION;
"Sensor"				return DEFINITIONSENSOR;
"Actuador"				return DEFINITIONACTUATOR;
"temperatura"			return SENSORTEMPERATURE;
"luminosidad"			return SENSORBRIGHTNESS;
"humo"					return SENSORSMOKE;
"alarma"				return ACTUATORALARM;
"luz"					return ACTUATORLIGHT;
"si"					return IF;
"sino"					return ELSE;
"repite"				return WHILE;
"activar"				return ACTIVATE;
"desactivar"			return DESACTIVATE;
"pausa"					return PAUSE;
"escribir"				return WRITE;
"plano"					return PLANO;

["][^"]*["] 		yylval.cadena = new char; strcpy(yylval.cadena,yytext);return TEXT;
[A-Za-z_][A-Za-z1-9_]*	yylval.cadena = new char; strcpy(yylval.cadena,yytext);return VARIABLE;
[0-9]+[.][0-9]*			yylval.value = atof(yytext);return REAL;
[0-9]+					yylval.value = atof(yytext);return ENTERO;
\n					    n_lineas++;
[\t ]					;	
. 						return (yytext[0]);
%%
