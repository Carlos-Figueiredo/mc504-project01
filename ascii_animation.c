/*
  Wasp.
  This code animates the the Generalized Cigarette smokers problem for N
  threads. It was based on the solution for 3 threads, presented in the "Little
  Book Of Semaphores", by Allen B. Downey.
  It is adapted to represent a fictional scenario that takes place in the
  university restaurat, in which the agent is represented by one of the workers
  that serve the food and the smokers are represented by the people eating it.
 */

#include <stdio.h>
#include <stdlib.h>

int N = 0;

void setup(int n) {

	N = n;

}

void prints_agent(int id) {



}

void prints_smoker(int id) {

	printf("				  ,-.,~~.\n");
	printf("				,'///||\\\\`.\n");
	printf("			   ///(((||)))\\\\.\n");
	printf("			  (((         )))\n");
	printf("			  _))) o` ´o  |(_\n");
	printf("			 ._//\\   _   /\\\\_.\n");
	printf("			 `-'_/`-._.-'\\-`-'\n");
	printf("			  _' \\/=._.=\\/ __\n");
	printf("			 / (           ) \\\n");
	printf("			/__|           |__\\\n");
	printf("			| ||           || |\n");
	printf("			 \\_|           (_/\n");
	printf("			   |           |\n");
	printf("			   (_ __  __ __)\n");
	printf("\n");
	printf("					)  )\n");
	printf("				______(____\n");
	printf("			   (___________)\n");
	printf("				/         \\\n");
	printf("			   /           \\\n");
	printf("			  |             |\n");
	printf("			  \\             /\n");
	printf("			   '._________.'\n");


	int i;

	// Prints chat box.
	for(i = 0; i < id; i++)
		printf("          ");

	printf("__________");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("          ");

	printf("\\  PRONTO!  /");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("          ");

	printf(" \\___  ____/ ");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("          ");

	printf("     \\/      ");

	printf("\n");


	// Prints smokers

	for(i = 0; i < N; i++)
		printf("  _______    ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" ((/---\\))   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("/()o` ´o()\\\\  ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(") \\__c__/ (  ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("   /   \\     ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("__||___||__  ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("\\ ~~ %2d ~~ \\ ", i);

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" \\__________\\");

	printf("\n");

}

void prints_ingredients(int *ingredients) {

	int i;
	for(i = 0; i < N ;i++)
		printf(" ______ ");

	printf("\n");

	for(i = 0; i < N ;i++)
		printf("|  %2d  | ", ingredients[i]);

	printf("\n");


	for(i = 0; i < N ;i++)
		printf("|______| ");

	printf("\n\n");

	for(i = 0; i < N ;i++)
		printf(" INGRED  ");

	printf("\n");

	for(i = 0; i < N ;i++)
		printf("---%2d--- ", i);

	printf("\n");

}
