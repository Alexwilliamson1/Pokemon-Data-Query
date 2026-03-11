#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"


//Freeing memory for an array:
void cleanUp(Array *arr) {
  	int i;
  	for (i = 0; i < arr -> size; ++i) {
  		free(arr -> elements[i]);
  	}
  	free(arr -> elements);
  	arr -> elements = NULL;
 	arr -> size = 0;
}

//Removing a duplicate commas from a line of text:
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

//Removing spaces before and after a string:
void strtrim(char* str) {
    int start = 0, end = strlen(str) - 1;

    while (str[start] == ' ')
        start++;

    while (str[end] == ' ')
        end--;

    int index = 0;
    for (int i = start; i <= end; i++)
        str[index++] = str[i];

    str[index] = '\0';
}
