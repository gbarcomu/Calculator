#fichero Makefile

OBJ = expresiones.o lexico.o HashTable.o ErrorController.o

all: SHoL

SHoL : $(OBJ)     
	g++ -oSHoL $(OBJ)



expresiones.o : expresiones.c
	g++ -c  -std=c++11 -oexpresiones.o  expresiones.c
	
HashTable.o: HashTable.h  HashTable.cpp
	g++ -c -std=c++11 -oHashTable.o HashTable.cpp
	
ErrorController.o: ErrorController.h  ErrorController.cpp
	g++ -c -std=c++11 -oErrorController.o ErrorController.cpp

	
lexico.o : lex.yy.c		
	g++ -c -olexico.o lex.yy.c 	

expresiones.c : expresiones.y     
	bison -d -oexpresiones.c expresiones.y

lex.yy.c: lexico.l
	flex lexico.l

clean : 
	rm  -f  *.c *.o 
