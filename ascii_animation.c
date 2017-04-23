/*
  Wasp.
  This code animates the the Generalized Cigarette smokers problem for N
  threads. It was based on the solution for 3 threads, presented in the "Little
  Book Of Semaphores", by Allen B. Downey.
  It is adapted to represent a fictional scenario that takes place in the
  university restaurat, in which the agent is represented by one of the workers
  that serve the food and the smokers are represented by the people eating it.
 */

#include "ascii_animation.h"

void prints_ingredients(int* ingredients);
void prints_title();

int N;

/* Setup function. Sets the number of threads used.
 * Parameter: Number (int) of threads.
*/
void thread_setup(int number) {

	N = number;

}

/* Prints agent function. Animates the action of an agent.
 * Parameter: Thread's id (int) and pointer to array of ingredients (int*).
*/
void prints_agent(int id, int *ingredients) {

	printf("\033[2J"); // Clear screen

	prints_title();

	// Prints agent.
	printf("                                 ____________\n");
	printf("                                /    %2d     /\n", id);
	printf("                  ,-.,~~.      / _________/\n");
	printf("                ,'///||\\\\`.   /_/\n");
	printf("               ///(((||)))\\\\.\n");
	printf("              (((         )))\n");
	printf("              _))) o` ´o  |(_\n");
	printf("             ._//\\   _   /\\\\_.\n");
	printf("             `-'_/`-._.-'\\-`-'           ___\n");
	printf("              _' \\/=._.=\\/ _____ _______/ _/_\n");
	printf("             / (           )__ _/______/ /__/\n");
	printf("            /__|           |          / /\n");
	printf("            | ||           |      ___/ /\n");
	printf("             \\_|           (      \\____/\n");
	printf("               |           |\n");
	printf("               (_ __  __ __)\n");
	printf("\n");
	printf("                    )  )\n");
	printf("                ______(____\n");
	printf("               (___________)\n");
	printf("                /         \\\n");
	printf("               /           \\\n");
	printf("              |             |\n");
	printf("              \\             /\n");
	printf("               '._________.'\n");

	prints_ingredients(ingredients);

	int i;

	// Prints smokers

	printf("\n\n\n\n");
	for(i = 0; i < N; i++)
		printf("  _______     ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" ((/---\\))    ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("/()o` ´o()\\   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(") \\__c__/ (   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("   /   \\      ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("__||___||__   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("\\ ~~ %.2d ~~ \\  ", i);

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" \\__________\\ ");

	printf("\n");


}

/* Prints smoker function. Animates the action of a smoker.
 * Parameter: Thread's id (int) and pointer to array of ingredients (int*).
*/
void prints_smoker(int id, int *ingredients) {

	printf("\033[2J"); // Clear screen

	prints_title();
	printf("\n\n"); // Alignment correction.

	printf("                  ,-.,~~.\n");
	printf("                ,'///||\\\\`.\n");
	printf("               ///(((||)))\\\\.\n");
	printf("              (((         )))\n");
	printf("              _))) o` ´o  |(_\n");
	printf("             ._//\\   _   /\\\\_.\n");
	printf("             `-'_/`-._.-'\\-`-'\n");
	printf("              _' \\/=._.=\\/ __\n");
	printf("             / (           ) \\\n");
	printf("            /__|           |__\\\n");
	printf("            | ||           || |\n");
	printf("             \\_|           (_/\n");
	printf("               |           |\n");
	printf("               (_ __  __ __)\n");
	printf("\n");
	printf("                    )  )\n");
	printf("                ______(____\n");
	printf("               (___________)\n");
	printf("                /         \\\n");
	printf("               /           \\\n");
	printf("              |             |\n");
	printf("              \\             /\n");
	printf("               '._________.'\n");


	prints_ingredients(ingredients);

	int i;

	// Prints chat box.
	for(i = 0; i < id; i++)
		printf("              ");

	printf("_____________");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("              ");

	printf("\\  PRONTO!  /");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("              ");

	printf(" \\___  ____/ ");

	printf("\n");

	for(i = 0; i < id; i++)
		printf("              ");

	printf("     \\/      ");

	printf("\n");


	// Prints smokers

	for(i = 0; i < N; i++)
		printf("  _______     ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" ((/---\\))    ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("/()o` ´o()\\   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf(") \\__c__/ (   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("   /   \\      ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("__||___||__   ");

	printf("\n");

	for(i = 0; i < N; i++)
		printf("\\ ~~ %.2d ~~ \\  ", i);

	printf("\n");

	for(i = 0; i < N; i++)
		printf(" \\__________\\ ");

	printf("\n");

}

/* Prints ingredients function. Auxiliar function that nimates the amount of
 * ingredients.
 * Parameter: Pointer to array of ingredients (int*).
*/
void prints_ingredients(int* ingredients) {

	int i;
	for(i = 0; i < N ;i++)
		printf(" ______  ");

	printf("\n");

	for(i = 0; i < N ;i++)
		printf("|  %.2d  | ", ingredients[i]);

	printf("\n");


	for(i = 0; i < N ;i++)
		printf("|______| ");

	printf("\n\n");

	for(i = 0; i < N ;i++)
		printf(" INGRED  ");

	printf("\n");

	for(i = 0; i < N ;i++)
		printf("   %.2d    ", i);

	printf("\n");

}


void prints_title() {

	printf("                                  _\n");
	printf("_________                 __     | |          _  _   __          __\n");
	printf("\\_   ___ \\   ___________ |__| ___| | ____    / \\/ \\ |__| ______ |  |_   ____\n");
	printf(" \\   \\  \\/  /  _ \\___   /|  |/  _  |/  _ \\  |      ||  |/  ___/|    _| /  _ \\\n");
	printf("  \\   \\____(  (_) )/   / |  || |_| (  (_) ) | |\\/| ||  |\\___ \\  |  |_ (  (_) )\n");
	printf("   \\_______\\\\____//_____\\|__||_____|\\____/  |_|  |_||__|/____/   \\___| \\____/\n");
	printf("\n\n\n");


}
