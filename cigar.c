/*
  Wasp.
  This code solves the Generalized Cigarette smokers problem for N threads. It
  was based on the solution for 3 threads, presented in the "Little Book Of
  Semaphores", by Allen B. Downey.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 2                 		// Number of ingredients

pthread_mutex_t agentMutex;         // Only one agent may act each cycle
pthread_mutex_t pusherMutex[N];     // Act as barriers until agents make
									// the corresponding ingredient available
pthread_mutex_t smokerMutex[N];		// Only one smoker may act each cycle.
pthread_mutex_t pusherLock;			// Only one pusher may act at a time
pthread_cond_t cond_pusher[N], cond_smoker[N];// Signaling conditions.

int ingredients[N]; 				// Informs which ingredients are available

// Thread-related functions
void* pusherN(void *v);
void* agentN(void *v);
void* smokerN(void *v);

int main() {
	//Initializing ingredients, mutexes and condition variables.
	for (int i = 0; i < N; i++) {
	  	ingredients[i] = 0;
		pthread_cond_init(&cond_pusher[i], 0);
		pthread_cond_init(&cond_smoker[i], 0);
		pthread_mutex_init(&pusherMutex[i], 0);
		pthread_mutex_init(&smokerMutex[i], 0);
	}

	pthread_mutex_init(&pusherLock, 0);
	pthread_mutex_init(&agentMutex, 0);


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

void* agentN(void *v) {
	int thisId = *(int *) v;

	while(1){
   		// The agent that escapes will release all ingredient but one
		pthread_mutex_lock(&agentMutex);

		printf("\n\nAGENT %d\n\n", thisId);

    	for(int i = 0; i < N; i++)
		  if(i != thisId)
		    pthread_cond_signal(&cond_pusher[i]); // Releases the ingredients


	}
 	return NULL;
}

void* pusherN(void *v) {
	int thisId = *(int *) v;

  	while(1){
		pthread_cond_wait(&cond_pusher[thisId], &pusherMutex[thisId]);

		pthread_mutex_lock(&pusherLock);

		// Sets ingredient as available
		ingredients[thisId] = 1;

		//printf("\n\nPUSHER %d\n\n", thisId);
		int missingIngredient = 0;
		int amountMissing = 0;

		// Each pusher will check if the information of which ingredient is the one
		// missing is available, for every ingredient
		for(int i = 0; i < N && amountMissing <= 1; i++){
			//printf("\n\ni %d\n\n", amountMissing);
	 		if (ingredients[i] == 0) {
	    		missingIngredient = i;
	    		amountMissing += 1;
	  		}

		}

		// If there is only one ingredient missing, the corresponding smoker is
		// signaled.
	  	if (amountMissing == 1) {
			//printf("\n\nMISSING %d\n\n", missingIngredient);
	  		// Resets the ingredients list.
		  	for(int i = 0; i < N ; i++){
				ingredients[i] = 0;

		  	}

			// Signals to the correct smoker.
		 	pthread_cond_signal(&cond_smoker[missingIngredient]);

		}

		pthread_mutex_unlock(&pusherLock);
		pthread_mutex_unlock(&pusherMutex[thisId]);
  	}

	return NULL;
}

void* smokerN(void *v) {
    int thisId = *(int *) v;

    while(1){
     	 pthread_cond_wait(&cond_smoker[thisId], &smokerMutex[thisId]);

     	 printf("\nSmoker %d made cigarrette.\n", thisId);

		// Signals agentMutex, to allow a new cycle.
		pthread_mutex_unlock(&agentMutex);

		pthread_mutex_unlock(&smokerMutex[thisId]);
    }

}
