#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Checking if a given string is a Pokemon type in "pokemon.csv":
int isType(char *type) {
	char types[] = "Grass, Fire, Water, Bug, Normal, Poison, Electric, Ground, Fairy, Fighting, Psychic, Rock, Flying, Ice, Dark, Ghost, Steel, Dragon";
	char temp[200];
	strcpy(temp, types);
	char *token = strtok(temp, ",");
	int found = 0;
	while (token != NULL) {
		while (*token == ' ') {
			token++;
		}
		if (strcmp(token, type) == 0) {
			found = 1;
			break;
		}
		token = strtok(NULL, ",");
	}
	if (found) {
		return 1;
	} else {
		return 0;
	}
}

//To prompt a user to type an option, a, b, or c, and validate the input:
void getOption(char option[]) {
	printf("\nYou have the following options: to query the data file by Pokemon type, type \"a\";");
	printf("  to save query results in a file, type \"b\";");
	printf("  and if you are finished making queries, type \"c.\" \n\n");
	bool isOption = false;
	while (!isOption) {
		printf("Option: ");
		fgets(option, 49, stdin);
		option[strcspn(option, "\n")] = '\0';
		if ((strcmp(option, "a") == 0) || (strcmp(option, "b") == 0) || (strcmp(option, "c") == 0)) {
		       isOption = true;
		} else {
			printf("\nPlease type \"a,\" \"b,\" or \"c.\"\n\n");
		}
	}
}

//Writing one "pokemon" structure to a file:
void writePokemonData(pokemon *field, FILE *file, int num) {
	fprintf(file, "%d.  ", num);
	fprintf(file, "Number: %s, ", field -> number);
	fprintf(file, "Name: %s, ", field -> name);
	fprintf(file, "Type 1: %s, ", field -> type1);
	fprintf(file, "Type 2: %s, ", field -> type2);
	fprintf(file, "Total: %s, ", field -> total);
 	fprintf(file, "HP: %s, ", field -> HP);
	fprintf(file, "Attack: %s, ", field -> attack);
	fprintf(file, "Defense: %s, ", field -> defense);
	fprintf(file, "Sp. Atk: %s, ", field -> spatk);
	fprintf(file, "Sp. Def: %s, ", field -> spdef);
	fprintf(file, "Speed: %s, ", field -> speed);
	fprintf(file, "Generation: %s, ", field -> generation);
	fprintf(file, "Legendary: %s", field -> legendary);
	fprintf(file, "\n\n");
}

//Outputting the names of files added to the user's current working directory:
void closingMessage(int *numFiles, char (*fileNames)[30]) {
	int length = *numFiles * 25;
	char fileNameList[length];
	fileNameList[0] = '\0';
	char lastFileName[25];
	if (*numFiles == 0) {
		printf("\n0 files have been added to your working directory.  Thank you for using Pokemon Data Query.");
	} if (*numFiles == 1) {
		printf("\nThe file \"%s\" has been added to your working directory.  Thank you for using Pokemon Data Query.", fileNames[0]);

	} else if (*numFiles == 2) {
		printf("\nThe files \"%s\" and \"%s\" have been added to your working directory.  Thank you for using Pokemon Data Query.", fileNames[0], fileNames[1]);
	} else if (*numFiles > 2) {
		strcpy(lastFileName, fileNames[*numFiles - 1]);
		for (int i = 0; i < *numFiles - 1; i++) {
			strcat(fileNameList, "\"");
			strcat(fileNameList, fileNames[i]);
			strcat(fileNameList, ",\" ");
		}
		printf("\nThe files %sand \"%s\" have been added to your working directory.  Thank you for using Pokemon Data Query.", fileNameList, lastFileName);
	}
}

//Removing duplicate commas from a line of text:
void removeConsecutiveCommas(char *str) {
    int len = strlen(str);
    int i, j;

    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != ',' || (str[i] == ',' && str[i + 1] != ',')) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}




