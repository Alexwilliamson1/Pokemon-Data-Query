//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//The "main" function:
int main() {
	char input1;
	char input2[20];
	char input3[20];
	char fileName[20];
	char fileName2[20];
	int totalNumQueries = 0;
	int numFiles = 0;
	char *fileNames;
	char *type1s;
	char stopChar[3];
	char q[] = "q";

//Declaring an array and two threads:
	Array pokemons;
	pthread_t t1, t2;
	
//Allocating memory for a structure and two arrays:
	struct threadArgs *args = malloc(sizeof(struct threadArgs));
	fileNames = (char *) malloc(20);
	type1s = (char *) malloc(20);

	int fileNamesLength = 0;

//Creating input for a file name and check if the file exists:
	printf("\nUse this program to find and save data about Pokemon listed in \"pokemon.csv.\"  To verify that this file is in your current working directory, type \"pokemon.csv.\"  Follow all responses by pressing the Return key.\n\n");
	scanf("%s", fileName);
	FILE* fileCheck = fopen(fileName, "r");
    	if (fileCheck == NULL) {
		printf("\nThere is no file with that name in your working directory. Please re-type the file name or press \"q\" to stop running this program.\n\n");
		while (1) {
			scanf("%s", fileName2);
			if (strcmp(fileName2, q) == 0) {
				exit(1);
			}
			FILE* fileCheck2 = fopen(fileName2, "r");
			if (fileCheck2 == NULL) {
				printf("\nThere is no file with that name.  Please type another file name or \"q\" to either continue running or to stop running this program.\n\n");
			}
			else if (strcmp(fileName2, "pokemon.csv") == 0) {
				strcpy((args) -> sFileName, fileName2);
				fclose(fileCheck2);
				break;
			}
		}
	}
//If the file corresponding to the user's input exists:
	else { 
		strcpy((args) -> sFileName, fileName);
		fclose(fileCheck);
	}

	while (1) {
//Running the first thread:
		pthread_create(&t1, NULL, displayOptions, NULL);
		scanf(" %c", &input1);
//Appending the user input to a list:
   		if (input1 == 'a') {
        		printf("\nType the \"type 1\" of Pokemon for which you would like to retrieve data.  Type 1's include: grass, fire, water, bug, normal, poison, electric, ground, fairy, fighting, psychic, rock, flying, ice, dark, ghost, steel, and dragon.\n\n");
			scanf(" %s", input2);
			strcpy(args -> input2A, input2);
			strcat(type1s, input2);
			strcat(type1s, ", ");
			type1s = (char *) realloc(type1s, 20);
			totalNumQueries += 1;
		}
		if (input1 == 'b') {
			printf("\nType the name of the file, ending in \".txt\" and with a maximum of 20 characters, within which you would like all query results saved.\n\n");
			scanf(" %s", input3);
			strcpy(args -> input2B, input3);
			args -> type1s = type1s;
			args -> totalNumQueries = totalNumQueries;		
			strcat(fileNames, input3);
			strcat(fileNames, ", ");
			fileNames = (char *) realloc(fileNames, 20);
			fileNamesLength = strlen(fileNames);
//Running the second thread:
			pthread_create(&t2, NULL, optionA, (void *)args);
			type1s = "";
			type1s = (char *) malloc(20);
			numFiles += 1;
		}
		if (input1 == 'c') {
//'Waiting' for the threads to finish running:
			pthread_join(t1, NULL);
			pthread_join(t2, NULL);
			if (totalNumQueries == 1) {
				printf("\nThe data for %d type of Pokemon has been saved in ", totalNumQueries);
			}
			else {
			printf("\nThe data for %d types of Pokemon has been saved in ", totalNumQueries);
			}
			if (numFiles == 1) {
				printf("%.*s.", fileNamesLength - 2, fileNames);
			}
			else if (numFiles > 1) {
				char *lastComma = strrchr(fileNames, ',');
				if (lastComma != NULL) {
					int index = lastComma - fileNames;
					fileNames[index] = '\0';
					printf("%s.", fileNames);
				}
			}
			return 1;
		}	
	}
//De-allocating the memory for a structure and two arrays:
	free(args);
	free(fileNames);
	free(type1s);
	return 0;
}




