/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_EXPRESIONES_H_INCLUDED
# define YY_YY_EXPRESIONES_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SALIR = 258,
    EQUALS = 259,
    LOWEROREQUAL = 260,
    GREATEROREQUAL = 261,
    NOTEQUALS = 262,
    ANDAND = 263,
    OROR = 264,
    SEPARATOR = 265,
    VARIABLE = 266,
    ENTERO = 267,
    REAL = 268,
    IDENTIFICADOR = 269,
    DEFINITIONSENSOR = 270,
    DEFINITIONACTUADOR = 271,
    SENSORTEMPERATURE = 272,
    SENSORBRIGHTNESS = 273,
    SENSORSMOKE = 274,
    ACTUADORALARM = 275,
    ACTUADORLIGHT = 276,
    ACTIVATE = 277,
    DESACTIVATE = 278,
    PAUSE = 279,
    WRITE = 280,
    DEFINITIONINTEGER = 281,
    DEFINITIONREAL = 282,
    DEFINITIONPOSITION = 283,
    IF = 284,
    ELSE = 285,
    WHILE = 286,
    menosunario = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 203 "expresiones.y" /* yacc.c:1909  */


  short typeOfThing;
  float value;
  char* cadena;
  bool logico;

#line 95 "expresiones.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXPRESIONES_H_INCLUDED  */
