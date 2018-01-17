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

			/* Création du damier */
			if ((i + j) % 2 == 0){
				MLV_draw_filled_rectangle(j*30, i*30, 30, 30, MLV_rgba(206,206,206,255));
			} else {
				MLV_draw_filled_rectangle(j*30, i*30, 30, 30, MLV_rgba(90,90,90,255));
			}			

			if (monde.plateau[i][j] != NULL){

				MLV_Color color;

				/* Test du propriétaire */
				if (monde.plateau[i][j]->couleur == ROUGE){
					color = MLV_rgba(191,63,63,255);
					
				} else {
					color = MLV_rgba(63,127,191,255);
				}

				/* Test du type d'unité */
				if (monde.plateau[i][j]->type == SERF){
					MLV_draw_ellipse(j*30 + 15, i*30 + 15, 7, 7, color);
				} else {
					MLV_draw_filled_ellipse(j*30 + 15, i*30 + 15, 7, 7, color);
				}
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
	MLV_wait_seconds(10);

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
