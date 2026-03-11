OBJ = main.o copyData.o createPokemon.o addPokemon.o cleanUp.o fileCheck.o createFile.o appendMain.o

THR = -pthread

all: Main Util1 Util2 Util3 Util4 Util5 Util6 Util7
	gcc -o main $(OBJ) $(THR)

Main: main.c pokemondataquery.h
	gcc -c main.c $(THR)

Util1: copyData.c pokemondataquery.h 
	gcc -c copyData.c $(THR)

Util2: createPokemon.c pokemondataquery.h
	gcc -c createPokemon.c $(THR)

Util3: addPokemon.c pokemondataquery.h
	gcc -c addPokemon.c $(THR)

Util4: cleanUp.c pokemondataquery.h
	gcc -c cleanUp.c $(THR)

Util5: fileCheck.c pokemondataquery.h
	gcc -c fileCheck.c $(THR)

Util6: createFile.c pokemondataquery.h
	gcc -c createFile.c $(THR)

Util7: appendMain.c pokemondataquery.h
	gcc -c appendMain.c $(THR)

clean:
	rm -f $(OBJ) main
