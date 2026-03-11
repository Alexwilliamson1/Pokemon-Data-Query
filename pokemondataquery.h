//Including the libraries:
#include <pthread.h>

extern pthread_mutex_t lock;

//Creating a structure, "Pokemon":
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
} Pokemon;

//Creating a structure, "Array":
typedef struct { 
	char pokeFile[20];
	char createdFile[20];
	char userType1[20];
	int size;
	int capacity;
	Pokemon **elements;
} Array;

//Declaring functions:
void appendMain();
void *copyData(void *);
void *createFile(void *);
void displayOptions();
Array* pokemonsArray(int);
char* fileCheck();
void printPokemon(Pokemon*, FILE *file2); 
void createPokemon(char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, Pokemon**);
int addPokemon(Array*, Pokemon*, int);
void cleanUp(Array *);
void removeConsecutiveCommas(char*);
void strtrim(char*);


