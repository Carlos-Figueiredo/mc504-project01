/*
  Wasp.
  This code solves the Generalized Cigarette smokers problem for N threads. It was  based on the solution for 3 threads, presented in the "Little Book Of Semaphores", by Allen B. Downey.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 //number of ingredients

sem_t agentMutex; //only one agent will act every cicle
sem_t ingredientsMutex[N];  //enables the user of that ingredient to smoke
sem_t pushersMutex[N]; //only one pusher will act at a time

int ingredients[N]; //signals if the ingredient N is available

void* pusherN(void *v);
void* agentN(void *v);


int main() {
    //Initializing ingredients
    for (int i = 0; i < N; i++)
      ingredients[i] = 0;

    // Initializing semaphores
    for(int i = 0; i < N; i++){
      sem_init(&ingredientsMutex[i], 0, 0);
      sem_init(&pushersMutex[i], 0, 0);
    }
    sem_init(&agentMutex, 0, 1);

    // Alocating and identificating N threads
    pthread_t agentThread[N], pusherThread[N];
    int i, id[N];

    for (i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&pusherThread[i], NULL, pusherN, &id[i]);
        pthread_create(&agentThread[i], NULL, agentN, &id[i]);
    }

    // Joining all the threads with the main one
    for (i = 0; i < N; i++) {
      pthread_join(agentThread[i], NULL);
      pthread_join(pusherThread[i], NULL);
    }

    return 0;
}

void* agentN(void *v) {
  int thisId = *(int *) v;
  while(1){
    sem_wait(&agentMutex);  //the agent that escapes will release all ingredient but its one
    int i;
    for(i = 0; i < N; i++)
      if(i != thisId)
        sem_post(&ingredientsMutex[i]); //realeases the ingredients
  }
  return NULL;
}

void* pusherN(void *v) {
  int thisId = *(int *) v;

  while(1){
    sem_wait(&pushersMutex[thisId]);    // MELHOR USAR FUTEX
    int i;
    // every pusher will check if the information of which ingredient is the one missing is available, for every ingredient
    for(int i = 0; i < N; i++){
      int missingIngredient = 1; //flag that indicates if the ith ingredient is the one missing
      for(int j = 0; j < N; j++){ //checks if the ith ingredient is the one missing
        if(j != i && ingredients[j] == 0){
          missingIngredient = 0;
        }
        if(missingIngredient == 1)  //if its the missing ingredient, lets the consumer with this ingredient know it can smoke
          sem_post(&ingredientsMutex[i]);
      }
    }
  }

  return NULL;
}
