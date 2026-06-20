#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "header.h"

//Initializing global variables:
pthread_mutex_t thread_count_lock;
pthread_mutex_t data_lock;
int active_threads = 0;

int main() {
	//Initializing pointers and other variables:
	if (pthread_mutex_init(&thread_count_lock, NULL) != 0) {
		fprintf(stderr, "There was a problem initializing \"thread_count_lock.\"\n");
		return 1;
	}
	if (pthread_mutex_init(&data_lock, NULL) != 0) {
		fprintf(stderr, "There was a problem initializing \"data_lock.\"\n");
		return 1;
	}
	array *arr = pokemonArray(50); 
	if (arr == NULL) {
		fprintf(stderr, "There was a problem allocating memory for an \"array\" variable.\n");
		return 1;
	}
	arguments *vars = initialization(arr);
	int fileNamesLength = 20;
	char (*fileNames)[30] = malloc(fileNamesLength * sizeof(*(fileNames)));
	if (fileNames == NULL) {
		fprintf(stderr, "There was a problem allocating memory for \"fileNames.\"\n");
		return 1;
	}	
	int numFiles = 0;
	for (int i = 0; i < 20; i++) {
		fileNames[i][0] = '\0';
	}
	bool endLoop = false;

	//Outputting an introductory statement for the user:
	printf("Use this program to query a file of Pokemon data that includes attributes for over 700 Pokemon.  You can run any number of queries and save the results in plain text files.  After saving results, your previous results will be deleted and you can start a new set of queries.\n\nTo verify that you have access to the data file, type \"pokemon.csv.\"  Follow all responses by pressing the Return key.\n\n");
	
	//To check if "pokemon.csv" is in this program's current working directory:
	csvFileCheck(vars);
	
	//Using a loop to create a continuous command-line interface:	
	while (!endLoop) {
		//Prompting the user for input and performing queries:
		loop(vars, &endLoop, &fileNamesLength, fileNames, &numFiles);
	}
	//Waiting for all threads to finish running:
	while (1) {
		pthread_mutex_lock(&thread_count_lock);
    		int done = (active_threads == 0);
    		pthread_mutex_unlock(&thread_count_lock);
    		if (done) {
        		break;
		}
		usleep(10000);
	}
	//De-allocating memory and destroying the mutexes:
	free(arr);
	free(vars);
	free(fileNames);
	pthread_mutex_destroy(&thread_count_lock);
	pthread_mutex_destroy(&data_lock);
	return 0;	
}





