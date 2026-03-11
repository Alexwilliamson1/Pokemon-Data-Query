//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pokemondataquery.h"

//Creating a mutex:
	pthread_mutex_t lock;

//The "main" function:
int main() {
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("There was a problem initializing the mutex.\n");
		exit(1);
	}
	appendMain();
	pthread_mutex_destroy(&lock);
	return 0;
}





