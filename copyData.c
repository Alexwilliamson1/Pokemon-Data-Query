//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

void* copyData(void* args) {
	if (pthread_mutex_lock(&lock) != 0) {
		printf("There was a problem locking the mutex inside the \"copyData\" function.\n");
		exit(1);
	}
	Array *accData = (Array*)args;
	char *userType1 = accData -> userType1;
	char *pokeFile = accData -> pokeFile;
	Pokemon *newPokemon;
	char number[10];
	char name[30];
	char type1[20];
	char type2[10];
	char total[5];
	char HP[5];
	char attack[5];
	char defense[5];
	char spatk[5];
	char spdef[5];
	char speed[5];
	char generation[10];
	char legendary[10];
	int rc;
	char oneType1[20];
	char a[10];
	char b[30];
	char c[20];
	char line[200];
	int counter = 0;
	
	//Opening a file to be read:
	FILE* file = fopen(pokeFile, "r");
    	if (file == NULL) {
		printf("There was a problem opening the file \"pokemon.csv.\"\n");
		exit(1);
	}
	
	//Reading the file to be read from the beginning:
	fseek(file, 0, SEEK_SET);
	
	//Iterating through each line of the file being read:
	while (fgets(line, sizeof(line), file) != NULL) {
		sscanf(line, "%[^,], %[^,], %[^,]", a, b, c);
		if (strcmp(userType1, c) == 0) {
			accData -> elements[accData -> size] = (Pokemon*)malloc(sizeof(Pokemon));
			if (strstr(line, ",,")) {
				removeConsecutiveCommas(line);
				//Creating an array of the lines in the file that correspond to user input:
				createPokemon(number, name, type1, type2, total, HP, attack, defense, spatk, spdef, speed, generation, legendary, &newPokemon);
				sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
				rc = addPokemon(accData, newPokemon, accData -> size);
				if (rc < 0) {
					free(newPokemon);
				}
			}
			else {
				createPokemon(number, name, type1, type2, total, HP, attack, defense, spatk, spdef, speed, generation, legendary, &newPokemon);
				sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> type2, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
				rc = addPokemon(accData, newPokemon, accData -> size);
				if (rc < 0) {
					free(newPokemon);
				}
			}
		}
	}
	if (pthread_mutex_unlock(&lock) != 0) {
		printf("There was a problem unlocking the mutex in the \"copyData\" function.\n");
	}
	//Closing the file that was opened to be read:
	fclose(file);
	return NULL;
}

