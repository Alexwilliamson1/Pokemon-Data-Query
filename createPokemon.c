#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//Outputting statements:
void displayOptions() {
	printf("\nYou have the following options: to retrieve the information for all Pokemon of a specific Type 1, type \"a\";");
	printf("  to save all query results in a file, type \"b\";");
	printf("  and if you are finished creating files, type \"c.\"\n\n");
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

