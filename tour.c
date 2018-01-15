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

		if (scanf("%d %d", &caseX, &caseY) == 0) {
			printf("Erreur de saisie\n"); /* Le joueur n'a pas saisi de chiffres --> arrêt du programme */
		} else {
			code = deplacerOuAttaquer(actuel, monde, caseX, caseY);
		}

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
	monde->tour += 1;
	printf("Tour : %d\n", monde->tour);

	printf("Joueur rouge :\n");
	gererDemiTour(ROUGE, monde);

	printf("Joueur bleu :\n");
	gererDemiTour(BLEU, monde);	
}