#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//A threaded function to read from a file and write copied data to another file:
void* optionA(void* args) {
//Declaring variables:
	Array pokemons;
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
	pokemons.elements = NULL;
	
//Creating a structure for the threaded arguments:
	struct threadArgs *threadArgs = (struct threadArgs *)args;
	char *fileName = threadArgs -> sFileName;
	char *input2 = threadArgs -> input2A;
	char *input3 = threadArgs -> input2B;
	int totalNumQueries = threadArgs -> totalNumQueries;
	char *type1s = threadArgs -> type1s;

	char line[200];
	char oneType1[20];
	int counter = 0;
	char a[10];
	char b[30];
	char c[20];
	
//Opening a file to be read:
	FILE* file = fopen(fileName, "r");
    	if (file == NULL) {
		printf("There was a problem opening the file \"pokemon.csv.\"\n");
		exit(1);
	}

	if (strlen(input3) > 3) {
//Creating a file to be written to:
		FILE* file2 = fopen(input3, "w");
		if (file2 == NULL) {
			printf("There was a problem creating a new file.  Please type the name of the file again.\n");
			exit(1);
		}
//Tokenizing an array of strings by means of a comma:
		char* token = strtok(type1s, ",");
		while (token != NULL) {
			strcpy(oneType1, token);
			strtrim(oneType1);
//Reading the file to be read from the beginning:
			fseek(file, 0, SEEK_SET);
//Iterating through each line of the file being read:
			while (fgets(line, sizeof(line), file) != NULL) {
				sscanf(line, "%[^,], %[^,], %[^,]", a, b, c);
				if (strcmp(oneType1, c) == 0) {
					if (strstr(line, ",,")) {
						removeConsecutiveCommas(line);
//Creating an array of the lines in the file that correspond to user input:
						createPokemon(number, name, type1, type2, total, HP, attack, defense, spatk, spdef, speed, generation, legendary, &newPokemon);
						sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
						rc = addPokemon(&pokemons, newPokemon, counter);
						counter++;
						if (rc < 0) {
							free(newPokemon);
						}
					}

					else {
						createPokemon(number, name, type1, type2, total, HP, attack, defense, spatk, spdef, speed, generation, legendary, &newPokemon);
						sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> type2, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
					rc = addPokemon(&pokemons, newPokemon, counter);
						counter++;
						if (rc < 0) {
							free(newPokemon);
						}
					}
				}
			}
//Writing the created array to the file opened for writing:
			for (int i = 0; i < pokemons.size; ++i) {
				printPokemon(pokemons.elements[i], file2);
			}
//De-allocating the memory used by the array:
			cleanup(&pokemons);
			token = strtok(NULL, ",");
			counter = 0;
		}
//Closing the file being written to:
		fclose(file2);
	}
//Closing the file that was opened to be read:
	fclose(file);
	return NULL;
}

