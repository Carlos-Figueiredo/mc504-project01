/*
  Wasp.
  This code solves the Generalized Cigarette smokers problem for N threads. It was  based on the solution for 3 threads, presented in the "Little Book Of Semaphores", by Allen B. Downey.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 3 //number of ingredients

sem_t ingredientsUsageMutex, agentMutex;

void* agentN(void *id) {
        
}



int main() {
    pthread_t thr[N];
    
    // Initializing semaphores
    sem_init(&ingredientsUsageMutex, 0, 1);
    sem_init(&agentMutex, 0, 0);
    
    // Alocating and identificating N threads
    int i, id;
    
    for (i = 0; i < N; i++) {
        id = (int*) malloc(sizeof(int));
        (*id) = i;
        pthread_create(&thr[i], NULL, f_thread, (void*) id);
    }
    
    
    
    // pthread_join para N 
    
    return 0;
}
