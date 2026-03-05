#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//Creating an array using the "Pokemon" and "Array" structures:
int addPokemon(Array *arr, Pokemon *pokemon, int pos) {
	Pokemon **newArr;
	int index;
	int C_OK = 0;
	int C_NOK = -1;

	if (pos < 0 || pos > arr->size) {
  		return C_NOK;
	}
  
	newArr = calloc(arr -> size + 1, sizeof(Pokemon*));

	for (index = 0; index < pos; ++index) {
  		newArr[index] = arr->elements[index];
  	}

  	newArr[index] = pokemon;

  	for (; index < arr -> size; ++index) {
  		newArr[index + 1] = arr -> elements[index];
  	}

  	free(arr -> elements);
  	arr -> elements = newArr;
  	arr -> size++;

  	return C_OK;
}

//Writing formatted text to a file for one "Pokemon" structure:
void printPokemon(Pokemon *tPtr, FILE *file2) {
	fprintf(file2, "Number: %s\n", tPtr -> number);
	fprintf(file2, "Name: %s\n", tPtr -> name);
	fprintf(file2, "Type 1: %s\n", tPtr -> type1);
	fprintf(file2, "Type 2: %s\n", tPtr -> type2);
	fprintf(file2, "Total: %s\n", tPtr -> total);
 	fprintf(file2, "HP: %s\n", tPtr -> HP);
	fprintf(file2, "Attack: %s\n", tPtr -> attack);
	fprintf(file2, "Defense: %s\n", tPtr -> defense);
	fprintf(file2, "Sp. Atk: %s\n", tPtr -> spatk);
	fprintf(file2, "Sp. Def: %s\n", tPtr -> spdef);
	fprintf(file2, "Speed: %s\n", tPtr -> speed);
	fprintf(file2, "Generation: %s\n", tPtr -> generation);
	fprintf(file2, "Legendary: %s\n", tPtr -> legendary);
	fprintf(file2, "\n");
}


