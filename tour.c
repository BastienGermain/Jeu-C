#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

    /* demande confirmation à l'utilisateur pour terminer son tour */
    char fin = ' ';
    while (fin != 'f') {
    	printf("Entrez 'f' pour terminer votre tour\n");
    	scanf(" %c", &fin);
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

    MLV_actualise_window();

	MLV_draw_text(
        19*CASE,40,
        "Joueur Rouge",
        MLV_rgba(200,200,200,255)
    );
	gererDemiTour(ROUGE, monde);

	effaceText(40);

	MLV_draw_text(
        19*CASE,40,
        "Joueur Bleu",
        MLV_rgba(200,200,200,255)
    );
	gererDemiTour(BLEU, monde);	
}