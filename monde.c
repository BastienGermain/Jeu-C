#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
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

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "plateau", "plateau", 640, 480 );
	

	int i, j;

	for (i = 0; i < LONG; i++){

		for (j = 0; j < LARG; j++) {

			MLV_draw_rectangle( i*10 , j*10, 10, 10, MLV_rgba(255,0,255,255) );

			if (monde.plateau[i][j] == NULL){
				//printf("|   ");
			} else {

				/* Test du propriétaire */
				/*if (monde.plateau[i][j]->couleur == ROUGE){
					printf("|R");
				} else {
					printf("|B");
				}*/

				/* Test du type d'unité */
				/*if (monde.plateau[i][j]->type == SERF){
					printf("s ");
				} else {
					printf("g ");
				}*/
			}

		}

	}

	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );

	//
	// Ferme la fenêtre
	//
	MLV_free_window();
}

void viderMonde(Monde *monde) {

	int i, j;

	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			if (monde->plateau[i][j] != NULL) {

				/* Supprime toutes les unités restantes sur le plateau */
				enleverUnite(monde->plateau[i][j], monde);
				monde->plateau[i][j] = NULL;
			}
		}
	}

	monde->tour = 0;
	monde->rouge = NULL;
	monde->bleu = NULL;

}
