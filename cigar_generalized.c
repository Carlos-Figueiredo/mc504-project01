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

#define N 10                 		// Number of ingredients

pthread_mutex_t agentMutex;         // Only one agent may act each cycle
sem_t pusherMutex[N];     			// Act as barriers until agents make
									// the corresponding ingredient available
sem_t smokerMutex[N];				// Only one smoker may act each cycle.
sem_t pusherLock;					// Only one pusher may act at a time
pthread_cond_t condAgent;

int ingredients[N]; 				// Informs which ingredients are available
int loop_stop = 0;
int agentActive = 0;

// Thread-related functions
void* pusherN(void *v);
void* agentN(void *v);
void* smokerN(void *v);

int main() {
	//Initializing ingredients and semaphores.
	sem_init(&pusherLock, 0, 1);
	pthread_mutex_init(&agentMutex, 0);
	pthread_cond_init(&condAgent, 0);

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
	
void* agentN(void *v) {
	int thisId = *(int *) v;

	while(1){
   		// The agent that escapes will release all ingredients but one
		pthread_mutex_lock(&agentMutex);
		
		while (agentActive > 0)
			pthread_cond_wait(&condAgent, &agentMutex);
		
		agentActive++;
		//printf("AGENT: %d\n", thisId);
    	for(int i = 0; i < N; i++)
		  if(i != thisId)
		    sem_post(&pusherMutex[i]); // Releases the ingredients

		// Signals agentMutex, to allow a new cycle.
		agentActive--;
		pthread_cond_signal(&condAgent);
		pthread_mutex_unlock(&agentMutex);
		//sleep(3);
	}
 	return NULL;
}

void* pusherN(void *v) {
	int thisId = *(int *) v;

  	while(1){
		sem_wait(&pusherMutex[thisId]);

		sem_wait(&pusherLock);

		ingredients[thisId]++;
		
		// Each pusher will check if the information of which ingredient is the one
		// missing is available, for every ingredient
		int index_minimum = 0;
		int amount_zeros = 0;
		
		int i = loop_stop;
		do {
			if (ingredients[i] == 0) {
				amount_zeros++;
	  		}
		
			if (ingredients[i] < ingredients[index_minimum] ) {
				index_minimum = i;
			
			}
			
			i = (i+1)%N;
			
		} while ( i != loop_stop );

		loop_stop = (index_minimum + 1)%N;

		// If , the corresponding smoker is
		// signaled.
	  	if (amount_zeros <= 1) {
	  		// Resets the ingredients list.
		  	for(i = 0; i < N ; i++){
				ingredients[i]--;

		  	}
			ingredients[index_minimum]++;
			// Signals to the correct smoker.
		 	sem_post(&smokerMutex[index_minimum]);

		}

		sem_post(&pusherLock);
  	}

	return NULL;
}

void* smokerN(void *v) {
    int thisId = *(int *) v;

    while(1){
     	sem_wait(&smokerMutex[thisId]);

     	printf("\nSmoker %d made cigarrette.\n", thisId);
		
    }

}
