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

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define N 5                 // Number of ingredients

/*
sem_t agentMutex;           // Only one agent will act every cicle
sem_t ingredientsMutex[N];  // Enables the user of that ingredient to smoke
sem_t pushersMutex[N];      // Only one pusher will act at a time
*/

int agentLock = 0;
int pusherLock = 0;

int agents[N];
int pushers[N];
int smokers[N];
int ingredients[N];         // Signals if the ingredient N is available

void* pusherN(void *v);
void* agentN(void *v);
void* smokerN(void *v);

// Futex implementation taken from:
// http://www.ic.unicamp.br/~islene/1s2017-mc504/prod-cons/prod-cons-futex.c

/* Retorna -1 se o futex não bloqueou e
            0 caso contrário */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT,
                 val1, NULL, NULL, 0);
}

/* Retorna o número de threads que foram acordadas */
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE,
                   n, NULL, NULL, 0);
}


int main() {
    //Initializing ingredients, smokers and pushers.
    for (int i = 0; i < N; i++) {}
        ingredients[i] = 0;
        pushers[i] = 0;
        smokers[i] = 0;
    }
/*
    // Initializing semaphores
    for(int i = 0; i < N; i++){
      sem_init(&ingredientsMutex[i], 0, 0);
      sem_init(&pushersMutex[i], 0, 0);
    }
    sem_init(&agentMutex, 0, 1);
*/
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
      while (agentLock == 1)
        futex_wait(&agentLock, 1);

      agentLock = 1;                       // rever isso

      int i;
      for(i = 0; i < N; i++)
        if(i != thisId)
          futex_wake(&pushers[i], 1); // Releases the ingredients
    }

    return NULL;
}

void* pusherN(void *v) {
    int thisId = *(int *) v;

    while(1){
        while (pushers[thisId] == 0)
          futex_wait(&pushers[thisId], 0);

        while (pusherLock == 1)
          futex_wait(&pusherLock, 1);

        pusherLock = 1;             // rever isso

        ingredients[thisId] = 1;  // Informs that this ingredient is not missing.

        int i;
        // Flag that indicates if the i-th ingredient is the one missing
        int missingIngredient = 0;

        int amountMissing = 0;

        // Each pusher will check if the information of which ingredient is the one
        // missing is available, for every ingredient
        for(int i = 0; i < N && amountMissing <= 1; i++){

          if (ingredients[i] == 0) {
            missingIngredient = i;
            amountMissing += 1;
          }

        }

      // If there is only one ingredient missing, the corresponding smoker is
      // signaled.
      if (amountMissing <= 1) {

          // Resets both the ingredients' and pushers' list.
          for(int i = 0; i < N ; i++){
            ingredients[i] = 0;
            pushers[i] = 0;

          }

          futex_wake(&smokers[missingIngredient], 1);

          // Unlocks agentLock, to allow a new cycle.
          agentLock = 0;
        }

        pusherLock = 0;

    }

    return NULL;
}

void* smokerN(void *v) {
    int thisId = *(int *) v;

    while(1){
        while (smokers[thisId] == 0)
          futex_wait(&smokers[thisId], 0);




    }

}
