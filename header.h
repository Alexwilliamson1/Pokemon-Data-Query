#ifndef HEADER_H
#define HEADER_H

#include <pthread.h>
#include <stdbool.h>

//Global variables:
extern pthread_mutex_t thread_count_lock;
extern pthread_mutex_t data_lock;
extern int active_threads;

//A structure for the data for one Pokemon:
typedef struct {
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
} pokemon;

//An "array" structure to store query results:
typedef struct { 
	int size;
	int capacity;
	pokemon **elements;
} array;

//A structure for program data shared by threads and other functions:
typedef struct {
	array *copiedPokemon;
	char (*type1s)[25];
	int typeCapacity;
	int numTypes;
	char newFile[20];
	char csvFile[25];
	bool fileCreated;
} arguments;

//Declaring functions:
void loop(arguments*, bool*, int*, char(*fileNames)[30], int*); 
void *copy(void*);
void *createFile(void*);
void getOption(char*);
void getType(arguments*);
void writePokemonData(pokemon*, FILE*, int);
void getFileName(arguments*, char(**fileNames)[30], int*, int*);
void closingMessage(int*, char (*fileNames)[]); 
int isType(char*);
array *pokemonArray(int);
arguments *initialization(array*);
void csvFileCheck(arguments*);
int addPokemon(array*, pokemon*);
void reset(array*);
void removeConsecutiveCommas(char*);

#endif

