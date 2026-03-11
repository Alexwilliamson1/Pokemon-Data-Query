//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

void appendMain() {
	Array* accData = pokemonsArray(50); 
	char* pokeFile = fileCheck();
	char* fileNames = (char *) malloc(20);
	strcpy(accData -> pokeFile, pokeFile);	
	char optChoice;
	char userType1[20];
	char fileName[100];
	int totalNumQueries = 0;
	int numFiles = 0;
	char stopChar[3];
	int fileNamesLength = 0;
	
	//Declaring two threads:
	pthread_t t1, t2;
	
	while (1) {
		displayOptions();
		printf("Option: ");
		scanf(" %c", &optChoice);
		if (optChoice == 'a') {
        		printf("\nType the Type 1 of Pokemon for which you would like to retrieve data.  Type 1's include: grass, fire, water, bug, normal, poison, electric, ground, fairy, fighting, psychic, rock, flying, ice, dark, ghost, steel, and dragon.\n\n");
			printf("Type 1 of Pokemon: ");
			scanf("%19s", userType1);
			strcpy(accData -> userType1, userType1);
			totalNumQueries += 1;
			if (totalNumQueries >= 50) {
				accData -> capacity += 1;
			}
			//Running the first thread:
			pthread_create(&t1, NULL, copyData, (void *)accData);
			pthread_join(t1, NULL);
			accData -> userType1[0] = '\0';
		}
		if (optChoice == 'b') {
			printf("\nType the name of the file, ending in \".txt\" and with a maximum of 20 characters, within which you would like all query results saved.\n\n");
			printf("File name: ");
			scanf(" %s", fileName);
			strcpy(accData -> createdFile, fileName);		
			strcat(fileNames, fileName);
			strcat(fileNames, ", ");
			fileNames = (char *)realloc(fileNames, (strlen(fileNames) + 2) * sizeof(char));
			fileNamesLength = strlen(fileNames);
			//Running the second thread:
			pthread_create(&t2, NULL, createFile, (void *)accData);
			pthread_join(t2, NULL);
			numFiles += 1;
			accData -> size = 0;
			accData -> capacity = 50;
			free(accData -> elements);
		}
		if (optChoice == 'c') {
			//pthread_join(t1, NULL);
			//pthread_join(t2, NULL);
			//pthread_exit(NULL);
			//pthread_exit(NULL);
			if (totalNumQueries == 1) {
				printf("\nThe data for %d type of Pokemon has been saved in ", totalNumQueries);
			}
			else {
				printf("\nThe data for %d types of Pokemon has been saved in ", totalNumQueries);		}
			if (numFiles == 1) {
				printf("\"%.*s.\"\n", fileNamesLength - 2, fileNames);
			}
			else if (numFiles > 1) {
				char *lastComma = strrchr(fileNames, ',');
				if (lastComma != NULL) {
					int index = lastComma - fileNames;
					fileNames[index] = '\0';
					printf("\"%s.\"\n", fileNames);
				}
			}
			break;
		}
	}
	//De-allocating the memory for two arrays:
	free(accData);
	free(fileNames);
}
