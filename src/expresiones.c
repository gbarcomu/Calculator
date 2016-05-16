/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "expresiones.y" /* yacc.c:339  */


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
// Previous position to define lines in plano
pair<float,float> previousPosition;
// First position to define lines in plano
pair<float,float> firstPosition;


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

void updatePreviousPositionWithPosition(string key) {
	
	previousPosition = getPosition(key);
}

void updatePreviousPositionWithPair(float position1, float position2) {
	
	previousPosition.first = position1;
	previousPosition.second = position2;
}

void createFirstPositionWithPosition(string key) {
	
	updatePreviousPositionWithPosition(key);
	
	firstPosition = getPosition(key);
}

void createFirstPositionWithPair(float position1, float position2) {
	
	updatePreviousPositionWithPair(position1, position2);
	
	firstPosition.first = position1;
	firstPosition.second = position2;
}


#line 252 "expresiones.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "expresiones.h".  */
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
    EQUALS = 258,
    LOWEROREQUAL = 259,
    GREATEROREQUAL = 260,
    NOTEQUALS = 261,
    SEPARATOR = 262,
    VARIABLE = 263,
    TEXT = 264,
    ENTERO = 265,
    REAL = 266,
    IDENTIFICADOR = 267,
    PLANO = 268,
    DEFINITIONSENSOR = 269,
    DEFINITIONACTUATOR = 270,
    SENSORTEMPERATURE = 271,
    SENSORBRIGHTNESS = 272,
    SENSORSMOKE = 273,
    ACTUATORALARM = 274,
    ACTUATORLIGHT = 275,
    ACTIVATE = 276,
    DESACTIVATE = 277,
    PAUSE = 278,
    WRITE = 279,
    DEFINITIONINTEGER = 280,
    DEFINITIONREAL = 281,
    DEFINITIONPOSITION = 282,
    IF = 283,
    ELSE = 284,
    WHILE = 285,
    menosunario = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 188 "expresiones.y" /* yacc.c:355  */


  short typeOfVariable;
  float value;
  char* cadena;
  bool logico;

#line 332 "expresiones.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXPRESIONES_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 347 "expresiones.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   253

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    38,     2,     2,
      47,    48,    36,    34,    42,    35,     2,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      32,    31,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   240,   240,   243,   244,   245,   246,   247,   251,   253,
     254,   256,   257,   259,   260,   263,   264,   265,   266,   270,
     271,   272,   273,   274,   278,   281,   282,   286,   299,   315,
     316,   317,   318,   322,   323,   324,   341,   344,   348,   352,
     355,   358,   386,   406,   426,   440,   452,   464,   486,   487,
     496,   508,   515,   522,   536,   537,   545,   566,   586,   587,
     588,   612,   613,   614,   615,   616,   617,   618,   619,   625,
     626,   627,   628,   629,   630
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQUALS", "LOWEROREQUAL",
  "GREATEROREQUAL", "NOTEQUALS", "SEPARATOR", "VARIABLE", "TEXT", "ENTERO",
  "REAL", "IDENTIFICADOR", "PLANO", "DEFINITIONSENSOR",
  "DEFINITIONACTUATOR", "SENSORTEMPERATURE", "SENSORBRIGHTNESS",
  "SENSORSMOKE", "ACTUATORALARM", "ACTUATORLIGHT", "ACTIVATE",
  "DESACTIVATE", "PAUSE", "WRITE", "DEFINITIONINTEGER", "DEFINITIONREAL",
  "DEFINITIONPOSITION", "IF", "ELSE", "WHILE", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "menosunario", "'^'", "'{'", "','", "'}'",
  "';'", "'['", "']'", "'('", "')'", "$accept", "SHoLProgram",
  "definitionZone", "plano", "planoPoints", "planoPoint",
  "planoFirstPoint", "definition", "sensorOrActuator", "dataZone",
  "dataSet", "data", "behaviourZone", "behaviour", "_else", "_while",
  "condition", "repeat", "actions", "action", "text", "declaration",
  "variables", "assignment", "arithmeticExpression", "logicExpression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    61,    60,    62,    43,    45,    42,    47,    37,   286,
      94,   123,    44,   125,    59,    91,    93,    40,    41
};
# endif

#define YYPACT_NINF -118

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-118)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -118,    13,   154,  -118,  -118,    -9,    -3,    25,    35,    39,
      39,    39,  -118,  -118,  -118,  -118,    51,    43,    -1,    19,
     232,   232,  -118,    12,    38,    68,  -118,    59,  -118,  -118,
    -118,  -118,    15,    15,    15,    41,     0,  -118,  -118,  -118,
    -118,  -118,    16,    21,    55,  -118,  -118,  -118,   113,    40,
      58,   136,    31,   111,    15,    15,    15,    15,    15,    15,
    -118,  -118,    15,    85,    84,    93,    87,   119,  -118,   124,
     125,   129,    -5,    15,  -118,  -118,   130,  -118,    98,  -118,
    -118,  -118,    15,  -118,    61,    61,    31,    31,    31,    31,
     148,    27,  -118,   102,  -118,   108,   153,  -118,  -118,    10,
    -118,    15,  -118,   120,  -118,   121,   120,  -118,  -118,   132,
    -118,   176,    15,  -118,    15,    49,  -118,   155,   165,  -118,
    -118,   157,    15,    15,    15,    15,    15,    15,  -118,  -118,
     143,   184,   166,    27,   145,   131,   163,    15,   207,   207,
     207,   207,   207,   207,    44,    65,  -118,  -118,    15,  -118,
    -118,   161,   171,   192,   -27,   179,   200,  -118,  -118,    10,
    -118,  -118,   162,  -118,  -118,  -118,  -118,    92,   187,  -118
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,    25,     0,     0,     0,     0,     0,
       0,     0,     7,     4,     5,     6,     0,    24,     0,     0,
       0,     0,    54,     0,     0,     0,    29,     0,    26,    60,
      58,    59,     0,     0,     0,     0,     0,    19,    20,    21,
      22,    23,     0,     0,     0,    51,    52,    53,     2,     0,
       0,     0,    61,     0,     0,     0,     0,     0,     0,     0,
      56,    13,     0,     0,     0,     0,     0,     0,    55,     0,
       0,     0,     0,     0,    37,    30,     0,    32,     0,    31,
      28,    27,     0,    62,    63,    64,    65,    66,    67,    68,
       0,     0,    17,     0,    18,     0,    42,    43,    44,    60,
      48,     0,    45,    49,    50,     0,     0,    38,    39,     0,
      40,     0,     0,    11,     0,     0,     9,     0,     0,    41,
      47,     0,     0,     0,     0,     0,     0,     0,    29,    29,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    72,
      71,    70,    74,    73,     0,     0,    57,    14,     0,    10,
       8,     0,     0,     0,     0,     0,     0,    15,    16,     0,
      36,    33,     0,    35,    12,    46,    29,     0,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,  -118,  -118,  -118,   106,  -118,  -118,   177,  -118,
    -118,  -118,  -117,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
     -98,  -118,   107,   244,   -18,   180
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    12,   115,   116,    63,    13,    42,    16,
      17,    28,    48,    75,   162,    76,   105,   109,    77,    78,
     102,    14,    23,    79,   103,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      35,   120,   160,    99,   100,    30,    31,    29,    61,    30,
      31,   144,   145,     3,    51,    52,    53,   161,    29,   100,
      30,    31,    18,    29,    64,    30,    31,   101,    19,    66,
      33,    32,    62,    20,    33,   113,    84,    85,    86,    87,
      88,    89,    34,    21,    90,    33,    34,    22,    65,   167,
      33,    27,     5,    67,    44,   106,    45,    34,    26,   114,
      36,   165,    34,    68,   111,    69,    70,    71,    72,    49,
      50,    59,    73,     5,    74,    54,    55,    56,    57,    58,
      44,    59,    46,   121,    80,    60,    69,    70,    71,    72,
     154,   133,   134,    73,   131,    74,   132,    56,    57,    58,
       5,    59,    81,    93,   138,   139,   140,   141,   142,   143,
      44,   155,    47,    69,    70,    71,    72,    24,    25,   153,
      73,     5,    74,   122,   123,   124,   125,    91,    92,    95,
     156,    94,    96,    97,    69,    70,    71,    72,   168,    98,
     108,    73,   110,    74,   117,    54,    55,    56,    57,    58,
     118,    59,   126,   127,    54,    55,    56,    57,    58,    83,
      59,     4,     5,   119,   151,   135,   128,     6,     7,     8,
      54,    55,    56,    57,    58,   136,    59,   129,    82,     9,
      10,    11,    54,    55,    56,    57,    58,   146,    59,   150,
     112,    54,    55,    56,    57,    58,   152,    59,    43,   137,
      54,    55,    56,    57,    58,   157,    59,   166,   148,   130,
      54,    55,    56,    57,    58,   158,    59,   147,    54,    55,
      56,    57,    58,   163,    59,   159,    54,    55,    56,    57,
      58,   169,    59,   164,    54,    55,    56,    57,    58,   149,
      59,    54,    55,    56,    57,    58,    15,    59,    37,    38,
      39,    40,    41,   107
};

static const yytype_uint8 yycheck[] =
{
      18,    99,    29,     8,     9,    10,    11,     8,     8,    10,
      11,   128,   129,     0,    32,    33,    34,    44,     8,     9,
      10,    11,    31,     8,     8,    10,    11,    32,    31,     8,
      35,    32,    32,     8,    35,     8,    54,    55,    56,    57,
      58,    59,    47,     8,    62,    35,    47,     8,    32,   166,
      35,     8,     8,    32,    42,    73,    44,    47,     7,    32,
      41,   159,    47,     8,    82,    21,    22,    23,    24,    10,
      11,    40,    28,     8,    30,    34,    35,    36,    37,    38,
      42,    40,    44,   101,    44,    44,    21,    22,    23,    24,
      46,    42,    43,    28,   112,    30,   114,    36,    37,    38,
       8,    40,    44,    10,   122,   123,   124,   125,   126,   127,
      42,    46,    44,    21,    22,    23,    24,    10,    11,   137,
      28,     8,    30,     3,     4,     5,     6,    42,    44,    10,
     148,    44,     8,     8,    21,    22,    23,    24,    46,    10,
      10,    28,    44,    30,    42,    34,    35,    36,    37,    38,
      42,    40,    32,    33,    34,    35,    36,    37,    38,    48,
      40,     7,     8,    10,    33,    10,    45,    13,    14,    15,
      34,    35,    36,    37,    38,    10,    40,    45,    42,    25,
      26,    27,    34,    35,    36,    37,    38,    44,    40,    44,
      42,    34,    35,    36,    37,    38,    33,    40,    21,    42,
      34,    35,    36,    37,    38,    44,    40,    45,    42,    33,
      34,    35,    36,    37,    38,    44,    40,    33,    34,    35,
      36,    37,    38,    44,    40,    33,    34,    35,    36,    37,
      38,    44,    40,    33,    34,    35,    36,    37,    38,   133,
      40,    34,    35,    36,    37,    38,     2,    40,    16,    17,
      18,    19,    20,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,     0,     7,     8,    13,    14,    15,    25,
      26,    27,    52,    56,    70,    72,    58,    59,    31,    31,
       8,     8,     8,    71,    71,    71,     7,     8,    60,     8,
      10,    11,    32,    35,    47,    73,    41,    16,    17,    18,
      19,    20,    57,    57,    42,    44,    44,    44,    61,    10,
      11,    73,    73,    73,    34,    35,    36,    37,    38,    40,
      44,     8,    32,    55,     8,    32,     8,    32,     8,    21,
      22,    23,    24,    28,    30,    62,    64,    67,    68,    72,
      44,    44,    42,    48,    73,    73,    73,    73,    73,    73,
      73,    42,    44,    10,    44,    10,     8,     8,    10,     8,
       9,    32,    69,    73,    74,    65,    73,    74,    10,    66,
      44,    73,    42,     8,    32,    53,    54,    42,    42,    10,
      69,    73,     3,     4,     5,     6,    32,    33,    45,    45,
      33,    73,    73,    42,    43,    10,    10,    42,    73,    73,
      73,    73,    73,    73,    61,    61,    44,    33,    42,    54,
      44,    33,    33,    73,    46,    46,    73,    44,    44,    33,
      29,    44,    63,    44,    33,    69,    45,    61,    46,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    56,    56,    57,
      57,    57,    57,    57,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    63,    64,    65,    66,
      67,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      69,    70,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    74,
      74,    74,    74,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     2,     8,     1,
       3,     1,     5,     1,     5,     9,     9,     5,     5,     1,
       1,     1,     1,     1,     1,     0,     2,     3,     3,     0,
       2,     2,     2,     6,    10,     6,     1,     1,     1,     1,
       2,     3,     2,     2,     2,     2,     7,     3,     1,     1,
       1,     3,     3,     3,     1,     3,     4,     8,     1,     1,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 251 "expresiones.y" /* yacc.c:1646  */
    {printer->printPlanoLinePair(previousPosition,firstPosition);}
#line 1554 "expresiones.c" /* yacc.c:1646  */
    break;

  case 11:
#line 256 "expresiones.y" /* yacc.c:1646  */
    {printer->printPlanoLinePosition(previousPosition,(yyvsp[0].cadena)); updatePreviousPositionWithPosition((yyvsp[0].cadena));}
#line 1560 "expresiones.c" /* yacc.c:1646  */
    break;

  case 12:
#line 257 "expresiones.y" /* yacc.c:1646  */
    {printer->printPlanoLinePair(previousPosition,make_pair((yyvsp[-3].value),(yyvsp[-1].value))); updatePreviousPositionWithPair((yyvsp[-3].value),(yyvsp[-1].value));}
#line 1566 "expresiones.c" /* yacc.c:1646  */
    break;

  case 13:
#line 259 "expresiones.y" /* yacc.c:1646  */
    {createFirstPositionWithPosition((yyvsp[0].cadena));}
#line 1572 "expresiones.c" /* yacc.c:1646  */
    break;

  case 14:
#line 260 "expresiones.y" /* yacc.c:1646  */
    {createFirstPositionWithPair((yyvsp[-3].value),(yyvsp[-1].value));}
#line 1578 "expresiones.c" /* yacc.c:1646  */
    break;

  case 15:
#line 263 "expresiones.y" /* yacc.c:1646  */
    {initializeSensor((yyvsp[-7].cadena), constants::TYPESENSOR, (yyvsp[-4].value), (yyvsp[-2].value), (yyvsp[-6].typeOfVariable)); printer->print(constants::PRINTMARKSENSOR,(yyvsp[-7].cadena)); {printer->printPause(constants::PAUSETIME);}}
#line 1584 "expresiones.c" /* yacc.c:1646  */
    break;

  case 16:
#line 264 "expresiones.y" /* yacc.c:1646  */
    {initializeSensor((yyvsp[-7].cadena), constants::TYPEACTUATOR, (yyvsp[-4].value), (yyvsp[-2].value), (yyvsp[-6].typeOfVariable));printer->print(constants::PRINTDISABLEACTUATOR,(yyvsp[-7].cadena)); {printer->printPause(constants::PAUSETIME);}}
#line 1590 "expresiones.c" /* yacc.c:1646  */
    break;

  case 17:
#line 265 "expresiones.y" /* yacc.c:1646  */
    {initializeSensorWithPosition((yyvsp[-3].cadena), constants::TYPESENSOR, (yyvsp[-1].cadena), (yyvsp[-2].typeOfVariable)); printer->print(constants::PRINTMARKSENSOR,(yyvsp[-3].cadena)); {printer->printPause(constants::PAUSETIME);}}
#line 1596 "expresiones.c" /* yacc.c:1646  */
    break;

  case 18:
#line 266 "expresiones.y" /* yacc.c:1646  */
    {initializeSensorWithPosition((yyvsp[-3].cadena), constants::TYPEACTUATOR, (yyvsp[-1].cadena), (yyvsp[-2].typeOfVariable));printer->print(constants::PRINTDISABLEACTUATOR,(yyvsp[-3].cadena)); {printer->printPause(constants::PAUSETIME);}}
#line 1602 "expresiones.c" /* yacc.c:1646  */
    break;

  case 19:
#line 270 "expresiones.y" /* yacc.c:1646  */
    {(yyval.typeOfVariable) = constants::TYPETEMPERATURE;}
#line 1608 "expresiones.c" /* yacc.c:1646  */
    break;

  case 20:
#line 271 "expresiones.y" /* yacc.c:1646  */
    {(yyval.typeOfVariable) = constants::TYPEBRIGHTNESS;}
#line 1614 "expresiones.c" /* yacc.c:1646  */
    break;

  case 21:
#line 272 "expresiones.y" /* yacc.c:1646  */
    {(yyval.typeOfVariable) = constants::TYPESMOKE;}
#line 1620 "expresiones.c" /* yacc.c:1646  */
    break;

  case 22:
#line 273 "expresiones.y" /* yacc.c:1646  */
    {(yyval.typeOfVariable) = constants::TYPEALARM;}
#line 1626 "expresiones.c" /* yacc.c:1646  */
    break;

  case 23:
#line 274 "expresiones.y" /* yacc.c:1646  */
    {(yyval.typeOfVariable) = constants::TYPELIGHT;}
#line 1632 "expresiones.c" /* yacc.c:1646  */
    break;

  case 24:
#line 278 "expresiones.y" /* yacc.c:1646  */
    {printer->printPause(constants::PAUSETIME);}
#line 1638 "expresiones.c" /* yacc.c:1646  */
    break;

  case 27:
#line 287 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-2].cadena))){
			   
			setValue((yyvsp[-2].cadena),(yyvsp[-1].value));
			printer->print(constants::PRINTVALUESENSOR,(yyvsp[-2].cadena));   		   
		}
		else {
			   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-2].cadena));
			YYERROR;
		}	
	}
#line 1655 "expresiones.c" /* yacc.c:1646  */
    break;

  case 28:
#line 300 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-2].cadena))){
			   
			setValue((yyvsp[-2].cadena),(yyvsp[-1].value));
			printer->print(constants::PRINTVALUESENSOR,(yyvsp[-2].cadena));   		   
		}
		else {
			   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-2].cadena));
			YYERROR;
		}	
	}
#line 1672 "expresiones.c" /* yacc.c:1646  */
    break;

  case 33:
#line 322 "expresiones.y" /* yacc.c:1646  */
    {execute = true;}
#line 1678 "expresiones.c" /* yacc.c:1646  */
    break;

  case 34:
#line 323 "expresiones.y" /* yacc.c:1646  */
    {execute = true;}
#line 1684 "expresiones.c" /* yacc.c:1646  */
    break;

  case 35:
#line 325 "expresiones.y" /* yacc.c:1646  */
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
#line 1702 "expresiones.c" /* yacc.c:1646  */
    break;

  case 36:
#line 341 "expresiones.y" /* yacc.c:1646  */
    {execute = !execute;}
#line 1708 "expresiones.c" /* yacc.c:1646  */
    break;

  case 37:
#line 344 "expresiones.y" /* yacc.c:1646  */
    {inWhile = true;}
#line 1714 "expresiones.c" /* yacc.c:1646  */
    break;

  case 38:
#line 348 "expresiones.y" /* yacc.c:1646  */
    {if(!(yyvsp[0].logico)) {execute = false;}}
#line 1720 "expresiones.c" /* yacc.c:1646  */
    break;

  case 39:
#line 352 "expresiones.y" /* yacc.c:1646  */
    {whileTimes = (yyvsp[0].value);}
#line 1726 "expresiones.c" /* yacc.c:1646  */
    break;

  case 41:
#line 359 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-1].cadena))){
				   
			if(execute) { /*If there is an if acting, do or not do the action*/
				if(!inWhile){ /*If there is a while acting repeats the instruction*/
					printer->print(constants::PRINTENABLEACTUATOR,(yyvsp[-1].cadena));printer->printPause((yyvsp[0].value));printer->print(constants::PRINTDISABLEACTUATOR,(yyvsp[-1].cadena));
				}
				else {
					
					whileInstructions.push_back(make_pair(constants::PRINTENABLEACTUATOR,(yyvsp[-1].cadena)));
					
					/*Using printer class in an incorrect way, second value is the number of seconds
					 * of the pause parsed as a string
					 */
					ostringstream oss;
					oss << (yyvsp[0].value);
					whileInstructions.push_back(make_pair(constants::PRINTPAUSE,oss.str()));
					whileInstructions.push_back(make_pair(constants::PRINTDISABLEACTUATOR,(yyvsp[-1].cadena)));
				}
			}    		   
				}
		else {
				   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-1].cadena));
			YYERROR;
		}		
	}
#line 1758 "expresiones.c" /* yacc.c:1646  */
    break;

  case 42:
#line 387 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[0].cadena))){
		   
			if(execute) { /*If there is an if acting, do or not do the action*/
				if(!inWhile){ /*If there is a while acting repeats the instruction*/
					printer->print(constants::PRINTENABLEACTUATOR,(yyvsp[0].cadena));
				}
				else {
					
					whileInstructions.push_back(make_pair(constants::PRINTENABLEACTUATOR,(yyvsp[0].cadena)));
				}
			}    		   
		}
		else {
		   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[0].cadena));
			YYERROR;
		}
	}
#line 1782 "expresiones.c" /* yacc.c:1646  */
    break;

  case 43:
#line 407 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[0].cadena))){
				   
			if(execute) { /*If there is an if acting, do or not do the action*/
				if(!inWhile){ /*If there is a while acting repeats the instruction*/
					printer->print(constants::PRINTDISABLEACTUATOR,(yyvsp[0].cadena));
				}
				else {

					whileInstructions.push_back(make_pair(constants::PRINTDISABLEACTUATOR,(yyvsp[0].cadena)));
				}
			}    		   
				}
		else {
				   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[0].cadena));
			YYERROR;
		}		
	}
#line 1806 "expresiones.c" /* yacc.c:1646  */
    break;

  case 44:
#line 427 "expresiones.y" /* yacc.c:1646  */
    {
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->printPause((yyvsp[0].value));
			}
			else {
				
				ostringstream oss;
				oss << (yyvsp[0].value);
				whileInstructions.push_back(make_pair(constants::PRINTPAUSE,oss.str()));
			}
		}
	}
#line 1824 "expresiones.c" /* yacc.c:1646  */
    break;

  case 45:
#line 441 "expresiones.y" /* yacc.c:1646  */
    {
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTMESSAGE,createMessageWithPair((yyvsp[0].cadena),0,0));
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPair((yyvsp[0].cadena),0,0)));
			}
		}
	}
#line 1840 "expresiones.c" /* yacc.c:1646  */
    break;

  case 46:
#line 453 "expresiones.y" /* yacc.c:1646  */
    {
		if(execute) { /*If there is an if acting, do or not do the action*/
			if(!inWhile){ /*If there is a while acting repeats the instruction*/
				printer->print(constants::PRINTMESSAGE,createMessageWithPair((yyvsp[0].cadena),(yyvsp[-4].value),(yyvsp[-2].value)));
			}
			else {

				whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPair((yyvsp[0].cadena),(yyvsp[-4].value),(yyvsp[-2].value))));
			}
		}
	}
#line 1856 "expresiones.c" /* yacc.c:1646  */
    break;

  case 47:
#line 465 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-1].cadena))){
				   
			if(execute) { /*If there is an if acting, do or not do the action*/
				if(!inWhile){ /*If there is a while acting repeats the instruction*/
					printer->print(constants::PRINTMESSAGE,createMessageWithPosition((yyvsp[0].cadena),(yyvsp[-1].cadena)));
				}
				else {

					whileInstructions.push_back(make_pair(constants::PRINTMESSAGE,createMessageWithPosition((yyvsp[0].cadena),(yyvsp[-1].cadena))));
				}
			}   		   
		}
		else {
				   
				errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-1].cadena));
				YYERROR;
		}		
	}
#line 1880 "expresiones.c" /* yacc.c:1646  */
    break;

  case 48:
#line 486 "expresiones.y" /* yacc.c:1646  */
    {(yyval.cadena) = (yyvsp[0].cadena);}
#line 1886 "expresiones.c" /* yacc.c:1646  */
    break;

  case 49:
#line 488 "expresiones.y" /* yacc.c:1646  */
    {
		ostringstream oss;
		oss << "\"" << (yyvsp[0].value) << "\"";
		string var = oss.str();
		char* c;
		strcpy(c, var.c_str());
		(yyval.cadena) = c;
	}
#line 1899 "expresiones.c" /* yacc.c:1646  */
    break;

  case 50:
#line 497 "expresiones.y" /* yacc.c:1646  */
    {
		ostringstream oss;
		oss << "\"" << (yyvsp[0].logico) << "\"";
		string var = oss.str();
		char* c;
		strcpy(c, var.c_str());
		(yyval.cadena) = c;
	}
#line 1912 "expresiones.c" /* yacc.c:1646  */
    break;

  case 51:
#line 509 "expresiones.y" /* yacc.c:1646  */
    {
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEINTEGER);
			variablesSeparatedComma.pop();
		}
    }
#line 1923 "expresiones.c" /* yacc.c:1646  */
    break;

  case 52:
#line 516 "expresiones.y" /* yacc.c:1646  */
    {
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEREAL);
			variablesSeparatedComma.pop();
		}
	}
#line 1934 "expresiones.c" /* yacc.c:1646  */
    break;

  case 53:
#line 523 "expresiones.y" /* yacc.c:1646  */
    {
		while(!variablesSeparatedComma.empty()) {
			initializeValue(variablesSeparatedComma.top(), constants::TYPEPOSITION);
			variablesSeparatedComma.pop();
		}
	}
#line 1945 "expresiones.c" /* yacc.c:1646  */
    break;

  case 54:
#line 536 "expresiones.y" /* yacc.c:1646  */
    {variablesSeparatedComma.push((yyvsp[0].cadena));}
#line 1951 "expresiones.c" /* yacc.c:1646  */
    break;

  case 55:
#line 537 "expresiones.y" /* yacc.c:1646  */
    {variablesSeparatedComma.push((yyvsp[0].cadena));}
#line 1957 "expresiones.c" /* yacc.c:1646  */
    break;

  case 56:
#line 546 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-3].cadena))){
			
			if(getType((yyvsp[-3].cadena)) == constants::TYPEPOSITION) {
				
				errorController->errorCatcher(constants::ERRORREDEFINED, (yyvsp[-3].cadena));
			}
			
			else {
				
				setValue((yyvsp[-3].cadena), (yyvsp[-1].value)); 
			}				   
		}
		else {
		   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-3].cadena));
			YYERROR;
		}
		isReal = false;
	}
#line 1982 "expresiones.c" /* yacc.c:1646  */
    break;

  case 57:
#line 567 "expresiones.y" /* yacc.c:1646  */
    {
		if(hashTable->checkValueByKey((yyvsp[-7].cadena))){
		   
			setPosition((yyvsp[-7].cadena),(yyvsp[-4].value),(yyvsp[-2].value));  		   
		}
		else {
		   
			errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[-7].cadena));
			YYERROR;
		}
		isReal = false;
	}
#line 1999 "expresiones.c" /* yacc.c:1646  */
    break;

  case 58:
#line 586 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[0].value);}
#line 2005 "expresiones.c" /* yacc.c:1646  */
    break;

  case 59:
#line 587 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[0].value); isReal = true;}
#line 2011 "expresiones.c" /* yacc.c:1646  */
    break;

  case 60:
#line 589 "expresiones.y" /* yacc.c:1646  */
    {
    	   if(hashTable->checkValueByKey((yyvsp[0].cadena))){
    		   
    		   if (getType((yyvsp[0].cadena)) == constants::TYPEPOSITION) {
    			   
        		   errorController->errorCatcher(constants::ERRORPOSITIONINARITHMETIC, (yyvsp[0].cadena));
        		   YYERROR; 
    		   }
    		   
    		   else {
    			   
        		   (yyval.value)=getValue((yyvsp[0].cadena));
        		   if(getType((yyvsp[0].cadena))==constants::TYPEREAL){
        			   isReal = true;
        		   } 
    		   }   		   
    	   }
    	   else {
    		   
    		   errorController->errorCatcher(constants::ERRORNONDECLARED, (yyvsp[0].cadena));
    		   YYERROR;
    	   }
       }
#line 2039 "expresiones.c" /* yacc.c:1646  */
    break;

  case 61:
#line 612 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=-(yyvsp[0].value);}
#line 2045 "expresiones.c" /* yacc.c:1646  */
    break;

  case 62:
#line 613 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[-1].value);}
#line 2051 "expresiones.c" /* yacc.c:1646  */
    break;

  case 63:
#line 614 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[-2].value)+(yyvsp[0].value);}
#line 2057 "expresiones.c" /* yacc.c:1646  */
    break;

  case 64:
#line 615 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[-2].value)-(yyvsp[0].value);}
#line 2063 "expresiones.c" /* yacc.c:1646  */
    break;

  case 65:
#line 616 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[-2].value)*(yyvsp[0].value);}
#line 2069 "expresiones.c" /* yacc.c:1646  */
    break;

  case 66:
#line 617 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(yyvsp[-2].value)/(yyvsp[0].value);}
#line 2075 "expresiones.c" /* yacc.c:1646  */
    break;

  case 67:
#line 618 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=(int)(yyvsp[-2].value)%(int)(yyvsp[0].value);}
#line 2081 "expresiones.c" /* yacc.c:1646  */
    break;

  case 68:
#line 619 "expresiones.y" /* yacc.c:1646  */
    {(yyval.value)=pow((yyvsp[-2].value),(yyvsp[0].value));}
#line 2087 "expresiones.c" /* yacc.c:1646  */
    break;

  case 69:
#line 625 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)==(yyvsp[0].value))?true:false;}
#line 2093 "expresiones.c" /* yacc.c:1646  */
    break;

  case 70:
#line 626 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)!=(yyvsp[0].value))?true:false;}
#line 2099 "expresiones.c" /* yacc.c:1646  */
    break;

  case 71:
#line 627 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)>=(yyvsp[0].value))?true:false;}
#line 2105 "expresiones.c" /* yacc.c:1646  */
    break;

  case 72:
#line 628 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)<=(yyvsp[0].value))?true:false;}
#line 2111 "expresiones.c" /* yacc.c:1646  */
    break;

  case 73:
#line 629 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)>(yyvsp[0].value))?true:false;}
#line 2117 "expresiones.c" /* yacc.c:1646  */
    break;

  case 74:
#line 630 "expresiones.y" /* yacc.c:1646  */
    {(yyval.logico)=((yyvsp[-2].value)<(yyvsp[0].value))?true:false;}
#line 2123 "expresiones.c" /* yacc.c:1646  */
    break;


#line 2127 "expresiones.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 632 "expresiones.y" /* yacc.c:1906  */


int main(int argc,char *argv[]){
     
     n_lineas = 0;
     isReal = false;
     execute = true;
     whileTimes = 1;
     inWhile = false;
     
     hashTable = new HashTable();
     printer = new Printer(hashTable, argv[1]);
     errorController = new ErrorController(printer);
     
     FILE *inputFile = fopen(argv[1], "r");
     yyin = inputFile;
     yyparse();
     
     
     delete hashTable;
     delete errorController;
     delete printer;
     
     return 0;
}
