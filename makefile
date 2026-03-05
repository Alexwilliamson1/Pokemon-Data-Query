OBJ = pokemondataquery.o optionA.o createPokemon.o addPokemon.o cleanup.o 

THR = -pthread

all: main Util1 Util2 Util3 Util4
	gcc -o pokemondataquery $(OBJ) $(THR)

main: pokemondataquery.c pokemondataquery.h
	gcc -c pokemondataquery.c $(THR)

Util1: optionA.c pokemondataquery.h 
	gcc -c optionA.c $(THR)

Util2: createPokemon.c pokemondataquery.h
	gcc -c createPokemon.c $(THR)

Util3: addPokemon.c pokemondataquery.h
	gcc -c addPokemon.c $(THR)

Util4: cleanup.c pokemondataquery.h
	gcc -c cleanup.c $(THR)

clean:
	rm -f $(OBJ) pokemondataquery
