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

	/* Créé et affiche la fenêtre */
	MLV_create_window( "plateau", "plateau", 18*30+100, 12*30 );
	
	/* Créer les personnages */
	MLV_Image *serfB, *guerrierB, *serfR, *guerrierR;
	MLV_Image *serf, *guerrier;

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

				/* Test du propriétaire & charger les images */
				if (monde.plateau[i][j]->couleur == ROUGE){
					serf=MLV_load_image( "image/serf-r.png" );
					guerrier=MLV_load_image( "image/guerrier-r.png" );					
				} else {
					serf=MLV_load_image( "image/serf-b.png" );
					guerrier=MLV_load_image( "image/guerrier-b.png" );	
				}

				/* Redimensionner les images */
				MLV_resize_image_with_proportions( serf, 30, 30);
				MLV_resize_image_with_proportions( guerrier, 30, 30);	

				/* Test du type d'unité */
				if (monde.plateau[i][j]->type == SERF){
					MLV_draw_image( serf,j*30, i*30);
				} else {
					MLV_draw_image( guerrier,j*30, i*30);
				}
			}

		}

	}

	/* On affiche sur quelle case est la souris */
	while( 1 ){

	int x,y;

        MLV_draw_text(
            555,15,
            "x : %d y : %d",
            MLV_rgba(0,0,0,255),
            x/30, y/30 
            );

        MLV_get_mouse_position( &x, &y );
        MLV_draw_text(
            555,15,
            "x : %d y : %d",
            MLV_rgba(90,90,90,255),
            x/30, y/30 
            );
                
        // On met à jour l'affichage.
        MLV_actualise_window();

    }


	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();

	//
	// Attend 60 secondes avant la fin du programme.
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
