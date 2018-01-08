#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void initialiserMonde(Monde *monde) {
	monde->tour = 0;
	monde->rouge = NULL;
	monde->bleu = NULL;

	/* Parcours du plateau de jeu */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			monde->plateau[i][j] = NULL;
		}
	}
}

int afficheMonde(Monde monde) {

	int i, j;

	for (i = 0; i < LONG; i++){

		printf("------------------------");
		printf("------------------------");
		printf("-------------------------\n");

		for (j = 0; j < LARG; j++) {

			if (monde.plateau[i][j] == NULL){
				printf("|   ");
			} else {

				/* Test du propriétaire */
				if (monde.plateau[i][j]->couleur == ROUGE){
					printf("|R");
				} else {
					printf("|B");
				}

				/* Test du type d'unité */
				if (monde.plateau[i][j]->type == SERF){
					printf("* "); /* * pour un SERF */
				} else {
					printf("+ "); /* + pour un GUERRIER */
				}
			}

		}

		printf("|\n");
	}

	printf("------------------------");
	printf("------------------------");
	printf("-------------------------\n");
}