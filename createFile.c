//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

void* createFile(void* args) {
	if (pthread_mutex_lock(&lock) != 0) {
		printf("There was a problem locking the mutex in the \"createFile\" function.\n");
		exit(1);
	}
	Array *accData = (Array *)args;
	char *createdFile = accData -> createdFile;
	int size = accData -> size;	

	if (createdFile != NULL) {
		//Creating a file to be written to:
		FILE* file2 = fopen(createdFile, "w");
		if (file2 == NULL) {
			printf("There was a problem creating a new file.  Please type the name of the file again.\n");
			exit(1);
		}
		//Writing the created array to the file opened for writing:
		for (int i = 0; i < size; ++i) {
			printPokemon(accData -> elements[i], file2);
		}
		if (pthread_mutex_unlock(&lock) != 0) {
			printf("There was a problem unlocking the mutex in the \"createFile\" function.\n");
		}
		fclose(file2);
	}
	return NULL;
}

Array *pokemonsArray(int capacity) {
        Array *arr = (Array*)malloc(sizeof(Array));
        if (arr == NULL) {
        	printf("There was a problem regarding the memory allocation of \"arr.\"\n");
        	return NULL;
        }
        arr -> elements = (Pokemon**)malloc(capacity * sizeof(Pokemon*));
        if (arr -> elements == NULL) {
        	printf("There was a problem regarding the memory allocation of the \"elements\" of \"arr.\"\n");
        	free(arr);
        	return NULL;
        }
        arr -> size = 0;
        arr -> userType1[0] = '\0';
        arr -> pokeFile[0] = '\0';
        arr -> createdFile[0] = '\0';
        arr -> capacity = capacity;
        return arr;
}

