#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"

//The following functions are run by threads:
//Copying and saving file data for one query:
void *copy(void *arg) {
	arguments *args = (arguments *)arg;
	array *results = args -> copiedPokemon;
	char *csvFile = args -> csvFile;
	char *type1 = args -> type1s[args -> numTypes - 1];
	char field1[10];
	char field2[30];
	char field3[20];
	int returnValue;
	char line[200];
	//Opening "pokemon.csv" to be read:
	FILE* file = fopen(csvFile, "r");
    	if (file == NULL) {
		printf("There was a problem opening the file \"pokemon.csv.\"\n");
		return NULL;
	}
	//Setting the starting position of the file read:
	fseek(file, 0, SEEK_SET);
	//Copying the fila data for a Pokemon if its Type 1 field matches the user's query:
	while (fgets(line, sizeof(line), file) != NULL) {
		if (sscanf(line, "%9[^,], %29[^,], %19[^,]", field1, field2, field3) != 3) {
			printf("There was a problem reading a \"Type 1\" in the file.\n");
			return NULL;
		}
		if (strcmp(type1, field3) == 0) {
			pokemon *newPokemon = malloc(sizeof(pokemon));
			if (!newPokemon) {
				printf("There was a problem allocating memory for \"newPokemon.\"\n.");
				return NULL;
			}
			if (strstr(line, ",,")) {
				removeConsecutiveCommas(line);
				int fields = sscanf(line, "%9[^,], %29[^,], %19[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %9[^,], %9[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
				//Checking that all the fields in "line" were successfully copied:
				if (fields != 12) {
					printf("There was a problem copying the file data.\n");
					return NULL;
				}
			}
			else {
				int fields = sscanf(line, "%9[^,], %29[^,], %19[^,], %9[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %9[^,], %9[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> type2, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
				//Checking that all the fields in "line" were successfully copied:
				if (fields != 13) {
					printf("There was a problem copying the file data.\n");
					return NULL;
				}
			}
			pthread_mutex_lock(&data_lock);
			//Adding a "pokemon" variable to the array of query results:
			returnValue = addPokemon(results, newPokemon);
			pthread_mutex_unlock(&data_lock);
			if (returnValue < 0) {
				free(newPokemon);
				return NULL;
			}	
		}
	}
	//Closing "pokemon.csv"::
	fclose(file);
	//Decrementing the active threads counter:
	pthread_mutex_lock(&thread_count_lock);
	active_threads--;
	pthread_mutex_unlock(&thread_count_lock);
	return NULL;
}

//To create a new .txt file and write the data saved in the "array" structure to the file:
void *createFile(void* arg) {
	arguments *args = (arguments *)arg;
	//Locking the mutex while the function accesses the "arguments" structure:
	pthread_mutex_lock(&data_lock);
	array *data = args -> copiedPokemon;
	char *newFile = args -> newFile;
	int size = data -> size;
	int numTypes = args -> numTypes;
	char types[300] = "";
	char lastType[20] = "";
	char firstLine[200];
	types[0] = '\0';
	strcpy(lastType, args -> type1s[numTypes - 1]);
	//Writing the first line in the file:
	if (numTypes == 1) {
		snprintf(firstLine, sizeof(firstLine), "Search results for %s Pokemon: %d found.\n", lastType, size);
	} else {
		for (int i = 0; i < numTypes - 1; i++) {
			strcat(types, args -> type1s[i]);
			if (numTypes == 2) {
				strcat(types, " ");
			}
			if (numTypes > 2) {
				strcat(types, ", ");
			}
		}
		snprintf(firstLine, sizeof(firstLine), "Search results for %sand %s Pokemon: %d found.\n", types, lastType, size);
	}
	
	if (strlen(newFile) > 0) {
		//Creating a file to be written to:
		FILE* file = fopen(newFile, "w");
		if (file == NULL) {
			printf("There was a problem creating a new file.  Please type the name of the file again.\n");
			return NULL;
		}
		fprintf(file, "%s\n", firstLine);
		//Writing the created array to the file opened for writing:
		for (int i = 0; i < size; ++i) {
			writePokemonData(data -> elements[i], file, i + 1);
		}
		fclose(file);
		//Resetting fields in the "arguments" structure:
		free(args -> type1s);
		args -> numTypes = 0;
		args -> typeCapacity = 50;
		//Unlocking the mutex for accessing structure data:
		pthread_mutex_unlock(&data_lock);
		//Decrementing the active threads counter:
		pthread_mutex_lock(&thread_count_lock);
		active_threads--;
		pthread_mutex_unlock(&thread_count_lock);
	}
	return NULL;
}

