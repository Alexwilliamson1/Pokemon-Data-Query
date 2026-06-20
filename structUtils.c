#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "header.h"

//The following are functions that modify structure data:
//Prompting the user to type a query, then validating and saving the input:
void getType(arguments *args) {
	char type[80]; 
	printf("\nType a type of Pokemon.  Types include: Grass, Fire, Water, Bug, Normal, Poison, Electric, Ground, Fairy, Fighting, Psychic, Rock, Flying, Ice, Dark, Ghost, Steel, and Dragon.  Capitalize the first letter in your response.\n\n");
	int typeCheck = 0;
	while (typeCheck == 0) {
		printf("Type of Pokemon: ");
		fgets(type, sizeof(type), stdin);
		type[strcspn(type, "\n")] = '\0';
		if (strlen(type) > 0 && islower((unsigned char)type[0])) {
			type[0] = toupper((unsigned char)type[0]);
		}
		typeCheck = isType(type);
		if (typeCheck == 0) {
			printf("\nPlease type one of the types listed above.\n\n");
		} 
	}
	if (args -> numTypes >= args -> typeCapacity) {
		args -> typeCapacity += 50;
		char (*temp)[25];
		temp = realloc(args -> type1s, args -> typeCapacity * sizeof(*(args -> type1s)));
		if (temp == NULL) {
			printf("There was a problem re-allocating memory for \"data -> type1s.\"\n");
			return;
		}
		args -> type1s = temp;
	}
	strcpy(args -> type1s[args -> numTypes], type);
	args -> numTypes++;
}

//Prompting the user to type a file name, then validating and saving the input:
void getFileName(arguments *args, char (**fileNames)[30], int *numFiles, int *fileNamesLength) {
	char fileName[30];
	bool fileCond1 = false;
	bool fileCond2 = false;
	printf("\nType the name of the file, ending in \".txt\" and with a maximum of 20 characters, within which you would like all new query results saved.\n\n");
	while (!(fileCond1 && fileCond2)) {
		printf("File name: ");
		fgets(fileName, sizeof(fileName), stdin);
		fileName[strcspn(fileName, "\n")] = '\0';
		size_t length = strlen(fileName);
		if (length >= 4 && strcmp(fileName + length - 4, ".txt") == 0) {
			fileCond1 = true;			
		} else {
			printf("\nPlease type a file name that ends with \".txt.\"\n\n");
		}
		if (strlen(fileName) <= 20) {
			fileCond2 = true;
		} else {
			printf("\nPlease type a file name with a maximum length of 20 characters.\n\n");
		}
	}
	strcpy(args -> newFile, fileName);
	if (*numFiles >= *fileNamesLength) {
		*fileNamesLength += 20;
		char (*temp)[30];
		temp = realloc(*fileNames, *fileNamesLength * sizeof(**fileNames));
		if (temp == NULL) {
			printf("There was a problem re-allocating memory for \"fileNames.\"\n");
			return;
		}
		*fileNames = temp;
	} 
	strcpy((*fileNames)[*numFiles], fileName);
}

//Creating a dynamically allocated "arguments" object for saving program data:
arguments *initialization(array *arr) {
	arguments *args = malloc(sizeof(arguments));
	if (args == NULL) {
		fprintf(stderr, "There was a problem allocating memory for \"args.\"\n");
		return NULL;
	}
	args -> copiedPokemon = arr;
	args -> numTypes = 0;
	args -> typeCapacity = 50;
	args -> type1s = malloc(args -> typeCapacity * sizeof(*(args -> type1s)));
	if (args -> type1s == NULL) {
		fprintf(stderr, "There was a problem allocating memory for \"args -> type1s.\"\n");
		free(args);
	}
	return args;
}

//Creating a dynamically allocated "array" object for saving query data:
array *pokemonArray(int capacity) {
        array *arr = (array*)malloc(sizeof(array));
        if (arr == NULL) {
        	printf("There was a problem regarding the memory allocation of \"arr.\"\n");
        	return NULL;
        }
        arr -> elements = (pokemon**)malloc(capacity * sizeof(pokemon*));
        if (arr -> elements == NULL) {
        	printf("There was a problem regarding the memory allocation of the \"elements\" of \"arr.\"\n");
        	free(arr);
        	return NULL;
        }
        arr -> size = 0;
        arr -> capacity = capacity;
        return arr;
}

//Adding "pokemon" structures to a dynamic array in the "array" structure:
int addPokemon(array *arr, pokemon *new_pokemon) {
	int C_OK = 0;
	int C_NOK = -1;
	if (arr -> size >= arr -> capacity) {
		int newCapacity = arr -> capacity * 2;
		pokemon **temp = realloc(
			arr -> elements, 
			newCapacity * sizeof(pokemon *)
		);

		if (temp == NULL) {
			return C_NOK;
		}
		arr -> elements = temp;
		arr -> capacity = newCapacity;
	}
	arr -> elements[arr -> size] = new_pokemon;
	arr -> size++;
  	return C_OK;
}

//Checking if "pokemon.csv" is in the user's current working directory:
void csvFileCheck(arguments *args) {
	char fileName[30];
	char statement[80];
	bool nameSpelling = false;
	while (!nameSpelling) {
		printf("File name: ");
		fgets(fileName, sizeof(fileName), stdin);
		fileName[strcspn(fileName, "\n")] = '\0';
		if (strcmp(fileName, "pokemon.csv") != 0) {
			printf("\nPlease check your spelling and re-type the file name.\n\n");
		} else {
			nameSpelling = true;
		}
	}
	//Checking if "pokemon.csv" can be opened for reading:
	FILE* file = fopen(fileName, "r");
    	if (file == NULL) {
		strcpy(statement, "\nThere is no access to the file.");
	} else {
		strcpy(args -> csvFile, fileName);
		fclose(file);
		strcpy(statement, "\nThe file was found.");
	}
	printf("%s\n", statement);
}

//Freeing allocated memory for an array of "pokemon" structures and resetting the values of "array" structure members:
void reset(array *arr) {
  	for (int i = 0; i < arr -> size; ++i) {
  		free(arr -> elements[i]);
  	}
  	free(arr -> elements);
  	arr -> elements = NULL;
 	arr -> size = 0;
	arr -> capacity = 50;
}



