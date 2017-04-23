/*
  Wasp.
  This code solves the non-Generalized Cigarette smokers problem for N threads. It
  was based on the solution for 3 threads, presented in the "Little Book Of
  Semaphores", by Allen B. Downey.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10                 	// Number of ingredients

sem_t agentMutex;         		// Only one agent may act in each cycle.
sem_t pusherMutex[N];     		// Semaphores for pushers.

sem_t smokerMutex[N];			// Semaphores for smokers.
sem_t pusherLock;				// Grants that only one pusher may act at
								// a time.

int ingredients[N]; 			// Informs which ingredients are available.

// Thread-related functions
void* pusherN(void *v);
void* agentN(void *v);
void* smokerN(void *v);

int main() {
	//Initializing ingredients and semaphores.
	sem_init(&pusherLock, 0, 1);
	sem_init(&agentMutex, 0, 1);

	for (int i = 0; i < N; i++) {
	  	ingredients[i] = 0;
		sem_init(&smokerMutex[i], 0, 0);
		sem_init(&pusherMutex[i], 0, 0);

	}


	// Alocating and identifying N threads
	pthread_t agentThread[N], pusherThread[N], smokerThread[N];
	int i, id[N];

	for (i = 0; i < N; i++) {
		id[i] = i;
		pthread_create(&pusherThread[i], NULL, pusherN, &id[i]);
		pthread_create(&agentThread[i], NULL, agentN, &id[i]);
		pthread_create(&smokerThread[i], NULL, smokerN, &id[i]);
	}

  	// Joining all the threads with the main one
	for (i = 0; i < N; i++) {
		pthread_join(agentThread[i], NULL);
		pthread_join(pusherThread[i], NULL);
		pthread_join(smokerThread[i], NULL);
	}

  	return 0;
}

/* Agent function. Manages the pushers by signaling all of them except the
/* one with the same id as the active agent.
/* Parameter: Pointer to the thread's id.
*/
void* agentN(void *v) {
	int thisId = *(int *) v;

	while(1){
   		// The agent that escapes will release all ingredients but one
		sem_wait(&agentMutex);

    	for(int i = 0; i < N; i++)
		  if(i != thisId)
		    sem_post(&pusherMutex[i]); // Releases the ingredients


	}
 	return NULL;
}

/* Pusher function. Each pusher will check if it is possible for any of the
/* smokers to complete a cigarette.
/* Parameter: Pointer to the thread's id.
*/
void* pusherN(void *v) {
	int thisId = *(int *) v;

  	while(1){
		sem_wait(&pusherMutex[thisId]);

		sem_wait(&pusherLock);

		// Sets ingredient as available
		ingredients[thisId] = 1;

		int missingIngredient = 0;
		int amountMissing = 0;

		// Each pusher will check if it is possible for any of the smokers to
		// complete a cigarette. If so, signals the corresponding smokerMutex
		// and resets all ingredients to zero.
		for(int i = 0; i < N && amountMissing <= 1; i++){
	 		if (ingredients[i] == 0) {
	    		missingIngredient = i;
	    		amountMissing += 1;
	  		}

		}

		// If there is only one ingredient missing, the corresponding smoker is
		// signaled.
	  	if (amountMissing == 1) {
	  		// Resets the ingredients list.
		  	for(int i = 0; i < N ; i++){
				ingredients[i] = 0;

		  	}

			// Signals to the correct smoker.
		 	sem_post(&smokerMutex[missingIngredient]);

		}

		sem_post(&pusherLock);
  	}

	return NULL;
}

/* Smoker function. Prints the id of the smoker that completed a cigarette.
/* Parameter: Pointer to the thread's id.
*/
void* smokerN(void *v) {
    int thisId = *(int *) v;

    while(1){
     	sem_wait(&smokerMutex[thisId]);

     	printf("\nSmoker %d made cigarrette.\n", thisId);

		// Signals agentMutex, to allow a new cycle.
		sem_post(&agentMutex);
    }

}
