#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "header.h"

//The following function performs queries and saves the results in files according to user input.  Threads are created for running functions that copy and write file data and a mutex is used for accessing and modifying shared structure variables.
void loop(arguments *args, bool *endLoop, int *fileNamesLength, char (*fileNames)[30], int *numFiles) {
	pthread_t t1, t2;
	array *data = args -> copiedPokemon;
	char userOption[50];
	//Prompting the user for an option, a, b, or c:
	getOption(userOption);
	//Handling user input:
	if (strcmp(userOption, "a") == 0) {
		//If a file was created, re-allocate freed memory for queries:
		if (args -> fileCreated == true) {
			pthread_mutex_lock(&data_lock);
			args -> type1s = malloc(args -> typeCapacity * sizeof(*(args -> type1s)));
			if (args -> type1s == NULL) {
				pthread_mutex_unlock(&data_lock);
				printf("There was a problem allocating memory for \"args -> type1s.\"\n");
				return;
			}
			//Freeing and re-allocating memory for query results:
			reset(data);
			data -> elements = malloc(data -> capacity * sizeof(pokemon*));
			if (data -> elements == NULL) {
				pthread_mutex_unlock(&data_lock);
				printf("There was a problem allocating memory for \"data -> elements.\"\n");
				return;
			}
			pthread_mutex_unlock(&data_lock);
			args -> fileCreated = false;
		}
		//Prompting the user to type a query:               	    	
		getType(args);
		//Copying data from "pokemon.csv" that matches the user's query and saving it in a structure variable:
		if (pthread_create(&t1, NULL, copy, (void *)args) != 0) {
			printf("There was a problem running thread \"t1.\"\n");
			return;
		} else {
			//To count the number of running threads:
			pthread_mutex_lock(&thread_count_lock);
			active_threads++;
			pthread_mutex_unlock(&thread_count_lock);
			pthread_detach(t1);
		}
	} else if (strcmp(userOption, "b") == 0) {
		//To handle cases when a user inputs "b" before "a":
		if (args -> numTypes == 0) {
			printf("\nPlease use option (a) to query the file before saving results.\n");
			return;
		}
		//Creating a file containing all new query results:
		getFileName(args, &fileNames, numFiles, fileNamesLength);
		if (pthread_create(&t2, NULL, createFile, (void *)args) != 0) {
			printf("There was a problem running thread \"t2.\"\n");
			return;
		} else {
			//To count the number of running threads:
			pthread_mutex_lock(&thread_count_lock);
			active_threads++;
			pthread_mutex_unlock(&thread_count_lock);
			pthread_detach(t2);
		}		
		(*numFiles)++;
		args -> fileCreated = true;	
	} else if (strcmp(userOption, "c") == 0) {
		//If user queries were processed, but no file was created, free allocated memory:
		if (args -> fileCreated == false) {
			pthread_mutex_lock(&data_lock);
			free(args -> type1s);
			reset(data);
			pthread_mutex_unlock(&data_lock);
		}
		//Outputting the names of files created by the program:
		closingMessage(numFiles, fileNames);
		*endLoop = true;
	}
}

