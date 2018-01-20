#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <MLV/MLV_all.h>

void gererDemiTour(char joueur, Monde *monde) {
	if (joueur == ROUGE){
		deroulementDemiTour(monde->rouge, monde);
	} else {
		deroulementDemiTour(monde->bleu, monde);
	}
}

void deroulementDemiTour(UListe listeJoueur, Monde *monde) {

	Unite *actuel = listeJoueur;

	/* on parcourt les unités */
	while (actuel != NULL)
    {	
    	/* à chaque unité on affiche le plateau et les infos de l'unité */
        afficheMonde(*monde);
        afficherInfosUnite(*actuel);

        /* demande au joueur une case à cibler */
        int caseX, caseY, code;
	            	
		printf("Entrez les coordonnees de la case cible :\n");

        /* Attend que l'utilisateur clique sur le bouton gauche de la souris */
		MLV_wait_mouse(&caseY, &caseX);

		caseX /= CASE;
		caseY /= CASE;
		
		code = deplacerOuAttaquer(actuel, monde, caseX, caseY);
	

		/* renvoie le résultat de l'action au joueur */
		if (code < 0) {
			printf("Vous ne pouvez pas cibler cette case\n");
		} else if (code == 1) {
			printf("Deplacement\n");
		} else if (code == 2){
			printf("Combat : victoire\n");
		} else if (code == 3){
			printf("Combat : defaite\n");
		}	

        actuel = actuel->suiv;
    }

    afficheMonde(*monde);

    int width_box, height_box; /* Size of the text_box */

    creerButton("Fin du tour", 19*CASE, 10*CASE, &width_box, &height_box);

    int reponseClick;
    while (reponseClick != 1){

    	int clickX, clickY;
		MLV_wait_mouse(&clickX, &clickY);

    	reponseClick = clickButton(clickX, clickY, 19*CASE, 10*CASE, width_box, height_box);
    }

}

void gererTour(Monde *monde) {

	effaceText(0);

    monde->tour += 1;

	MLV_draw_text(
        19*CASE,15,
        "Tour : %d",
        MLV_rgba(200,200,200,255),
        monde->tour
    );

	MLV_draw_text(
        19*CASE,45,
        "Joueur Rouge",
        MLV_rgba(200,200,200,255)
    );
	gererDemiTour(ROUGE, monde);

	effaceText(45);

	MLV_draw_text(
        19*CASE,45,
        "Joueur Bleu",
        MLV_rgba(200,200,200,255)
    );
	gererDemiTour(BLEU, monde);	
}

void creerButton(char message[], int posX, int posY, int *width_box, int *height_box) {

	MLV_get_size_of_adapted_text_box(
		message,
		CASE/3,
		width_box, height_box
	);

    MLV_draw_adapted_text_box(
        posX, posY,
        message,
        CASE / 3,
        MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,0),
        MLV_TEXT_CENTER
    );

    MLV_actualise_window();;
}

int clickButton(int clickX, int clickY, int posX, int posY, int width_box, int height_box) {

    if (clickX < posX || clickX > posX + width_box || clickY < posY || clickY > posY + height_box) {
    	// Le click n'est pas sur le bouton
    	return 0;
    } else {
    	return 1;
    }
}