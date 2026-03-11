//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

char* fileCheck() {
	char filePath[100];
	char filePath2[100];
	static char fileName[100];
	static char fileName2[100];
	char q[] = "q";

//Creating input for a file name and check if the file exists:
	printf("\nUse this program to find and save data about Pokemon listed in \"pokemon.csv.\"  To verify that this file is in your current working directory, type \"pokemon.csv\" or the directory path to the file.  Follow all responses by pressing the Return key.\n\n");
	printf("File name or directory path: ");
	scanf("%99s", filePath);
	char *lastSeparator = strrchr(filePath, '\\');
	if (lastSeparator != NULL) {
		strcpy(fileName, lastSeparator + 1);
	} 
	else {
		strcpy(fileName, filePath);
	}
	
	FILE* fileCheckA = fopen(fileName, "r");
    	if (fileCheckA == NULL) {
		printf("\nThere is no file with that name in your working directory. Please re-type the file name or press \"q\" to stop running this program.\n\n");
		while (1) {
			scanf("%99s", filePath2);
			char *lastSeparator2 = strrchr(filePath2, '\\');
			if (lastSeparator2 != NULL) {
				strcpy(fileName2, lastSeparator2 + 1);
			} else {
				strcpy(fileName2, filePath2);
			}
			if (strcmp(fileName2, q) == 0) {
				exit(1);
			}
			FILE* fileCheckB = fopen(fileName2, "r");
			if (fileCheckB == NULL) {
				printf("\nThere is no file with that name.  Please type another file name or \"q\" to either continue running or to stop running this program.\n\n");			}
			else if (strcmp(fileName2, "pokemon.csv") == 0) {				
				fclose(fileCheckB);
				return fileName2;
				break;
			}
		}
	}
//If the file corresponding to the user's input exists:
	else { 
		fclose(fileCheckA);
		return fileName;
	}
}

