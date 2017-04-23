/*
  Wasp.
  Header for the code that animates the the Generalized Cigarette smokers
  problem for N threads. It was based on the solution for 3 threads, presented
  in the "Little Book Of Semaphores", by Allen B. Downey.
  It is adapted to represent a fictional scenario that takes place in the
  university restaurat, in which the agent is represented by one of the workers
  that serve the food and the smokers are represented by the people eating it.
 */

#ifndef ASCII_ANIMATION
#define ASCII_ANIMATION

#include <stdio.h>
#include <stdlib.h>

 /* Setup function. Sets the number of threads used.
  * Parameter: Number (int) of threads.
 */
 void thread_setup(int number);

 /* Prints agent function. Animates the action of an agent.
  * Parameter: Thread's id (int) and pointer to array of ingredients (int*).
 */
void prints_smoker(int id, int *ingredients);

/* Prints smoker function. Animates the action of a smoker.
 * Parameter: Thread's id (int) and pointer to array of ingredients (int*).
*/
void prints_agent(int id, int *ingredients);

#endif
