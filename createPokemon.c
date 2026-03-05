#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//Outputting statements:
void* displayOptions(void *arg) {
	printf("\nIf you would like to retrieve the information for all Pokemon of a specific \"type 1,\" type \"a.\"");
	printf("  If you would like to save all query results in a file, type \"b.\"");
	printf("  If you are finished creating files, type \"c.\"\n\n");
	return NULL;
}

//Assigning data read from a file to structure variables:
void createPokemon(char *number, char *name, char *type1, char *type2, char *total, char *HP, char *attack, char *defense, char *spatk, char *spdef, char *speed, char *generation, char *legendary, Pokemon **pokemons) {
	*pokemons = (Pokemon*) malloc(sizeof(Pokemon));
	if (*pokemons == NULL) {
		printf("Memory allocation error.\n");
		exit(0);
	}
	strcpy((*pokemons) -> number, number);
	strcpy((*pokemons) -> name, name);
	strcpy((*pokemons) -> type1, type1);	
	strcpy((*pokemons) -> type2, type2);	
	strcpy((*pokemons) -> total, total);
	strcpy((*pokemons) -> HP, HP);
	strcpy((*pokemons) -> attack, attack);
	strcpy((*pokemons) -> defense, defense);
	strcpy((*pokemons) -> spatk, spatk);
	strcpy((*pokemons) -> spdef, spdef);
	strcpy((*pokemons) -> speed, speed);
	strcpy((*pokemons) -> generation, generation);
	strcpy((*pokemons) -> legendary, legendary);
}

