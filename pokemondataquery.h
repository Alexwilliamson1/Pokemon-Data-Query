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
	int size;
	Pokemon **elements;
} Array;

//Creating a structure for threaded arguments:
struct threadArgs{
	char input2A[20];
	char input2B[20];
	char sFileName[20];
	char *type1s;
	int totalNumQueries;
};

//Declaring functions:
void *optionA(void *);
void *displayOptions(void*);
void printPokemon(Pokemon*, FILE *file2); 
void createPokemon(char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, Pokemon**);
int addPokemon(Array*, Pokemon*, int);
void cleanup(Array *);
void removeConsecutiveCommas(char*);
void strtrim(char* str);

