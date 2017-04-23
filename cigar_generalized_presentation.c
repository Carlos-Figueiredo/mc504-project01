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
#include "ascii_animation.h"

#define N 10                 		// Number of ingredients

pthread_mutex_t agentMutex;         // Grants mutual exclusion while modifying
									// pusherMutex[N].

sem_t pusherMutex[N];     			// Semaphores for pushers.

sem_t smokerMutex[N];				// Semaphores for smokers.
sem_t ingredientLock;				// Semaphore for ingredients.

pthread_cond_t condAgent;			// Condition used in signaling/waiting
									// agents.

int ingredients[N]; 				// Informs which ingredients are available.
int ingredients_copy[N];			// Copy to avoid unwanted changes.
int loop_stop = 0;					// Informs the stopping point in the loop
									// that access ingredients[i] to avoid
									// starvation.

int agentActive = 0;				// Condition that grants that only one
									// agent may act at a time.
int lastId = -1;					// Informs the last active agent, to avoid
 									// one agent being able to run multiple
									// times through AgentN(void *v).

// Thread-related functions
void* pusherN(void *v);
void* agentN(void *v);
void* smokerN(void *v);

int main() {
	//Initializing ingredients, pthread variables and semaphores.
	sem_init(&ingredientLock, 0, 1);
	pthread_mutex_init(&agentMutex, 0);
	pthread_cond_init(&condAgent, 0);

	for (int i = 0; i < N; i++) {
	  	ingredients[i] = 0;
		sem_init(&smokerMutex[i], 0, 0);
		sem_init(&pusherMutex[i], 0, 0);

	}

	// Setup function for animations.
	thread_setup(N);

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
 * one with the same id as the active agent.
 * Parameter: Pointer to the thread's id.
*/
void* agentN(void *v) {
	int thisId = *(int *) v;

	while(1){

		while (lastId == thisId)
			pthread_cond_signal(&condAgent);

		while (__sync_bool_compare_and_swap(&agentActive, 0, 1))
        	pthread_cond_wait(&condAgent, &agentMutex);

		lastId = thisId;

		sem_wait(&ingredientLock);

		int i;

     	prints_agent(thisId, ingredients);
		sleep(1);

		sem_post(&ingredientLock);

    	for(i = 0; i < N; i++)
		  if(i != thisId)
		    sem_post(&pusherMutex[i]); // Releases the ingredients

		// Signals agentMutex, to allow a new cycle.
		agentActive--;
		//sleep(1);
	}
 	return NULL;
}

/* Pusher function. Each pusher will check if it is possible for any of the
 * smokers to complete a cigarette.
 * Parameter: Pointer to the thread's id.
*/
void* pusherN(void *v) {
	int thisId = *(int *) v;

  	while(1){

		// Waits for the signal sent by the agents.
		sem_wait(&pusherMutex[thisId]);

		// Locks the critical region associated with ingredients[i].
		sem_wait(&ingredientLock);

		// Increments the ingredient associated with the pusher.
		ingredients[thisId]++;

		int index_minimum = 0;
		int amount_zeros = 0;

		// Each pusher will check if it is possible for any of the smokers to
		// complete a cigarette. If so, signals the corresponding smokerMutex
		// and decrements all ingredients used.
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

		// If there are fewer than 1 zeros, that means it is possible to
		// complete a cigarette.
	  	if (amount_zeros <= 1) {

			for(i = 0; i < N ; i++)
				ingredients_copy[i] = ingredients[i];

			// Signals to the correct smoker.
		 	sem_post(&smokerMutex[index_minimum]);


	  		// Updates the ingredients list.
		  	for(i = 0; i < N ; i++){
				ingredients[i]--;

		  	}
			ingredients[index_minimum]++;

		}

		sem_post(&ingredientLock);
  	}

	return NULL;
}

/* Smoker function. Prints the id of the smoker that completed a cigarette.
 * Parameter: Pointer to the thread's id.
*/
void* smokerN(void *v) {
    int thisId = *(int *) v;

    while(1){
		// Waits for the signal sent by the pushers.
     	sem_wait(&smokerMutex[thisId]);

		sem_wait(&ingredientLock);

     	prints_smoker(thisId, ingredients_copy);
		sleep(1);

		sem_post(&ingredientLock);

    }

}
