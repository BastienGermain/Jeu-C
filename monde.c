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

	
	/* Créer les personnages */
	MLV_Image *serf, *guerrier;

	int i, j;

	for (i = 0; i < LONG; i++){

		for (j = 0; j < LARG; j++) {



			/* Création du damier */
			if ((i + j) % 2 == 0){
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(206,206,206,255));
			} else {
				MLV_draw_filled_rectangle(j*CASE, i*CASE, CASE, CASE, MLV_rgba(90,90,90,255));
			}

			if (monde.plateau[i][j] != NULL){

				/* Test du propriétaire & charger les images */
				if (monde.plateau[i][j]->couleur == ROUGE){
					serf = MLV_load_image( "image/serf-r.png" );
					guerrier = MLV_load_image( "image/guerrier-r.png" );					
				} else {
					serf = MLV_load_image( "image/serf-b.png" );
					guerrier = MLV_load_image( "image/guerrier-b.png" );
				}

				/* Redimensionner les images */
				MLV_resize_image_with_proportions(serf, CASE, CASE);
				MLV_resize_image_with_proportions(guerrier, CASE, CASE);	

				/* Test du type d'unité */
				if (monde.plateau[i][j]->type == SERF){
					MLV_draw_image(serf, j*CASE, i*CASE);
				} else {
					MLV_draw_image(guerrier, j*CASE, i*CASE);
				}
			}

		}

	}


    const char *text_box = "-> REGLE DU JEU <-\nPasser tour : f\nArrêter la partie : échap\nContinuer la partie : autre touche\n";

    /* Affiche les regles du jeu */
    /*MLV_draw_adapted_text_box(
                19*CASE, CASE,
                text_box,
                9,
                MLV_rgba(255,255,255,0), MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,0),
                MLV_TEXT_CENTER
     );*/
	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();


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


/* Efface le texte dans la partie noire à partir de la hauteur en paramètre */
void effaceText(int hauteurDepart) {
	MLV_draw_filled_rectangle(18*CASE, hauteurDepart, 7*CASE, 12*CASE - hauteurDepart, MLV_rgba(0,0,0,255));

	MLV_actualise_window();
}
