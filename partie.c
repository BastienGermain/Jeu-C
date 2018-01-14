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

	/* parcourt les unités */

	Unite *actuel = listeJoueur;

	while (actuel != NULL)
    {
        afficheMonde(*monde);
        afficherInfosUnite(*actuel);

        /* demande au joueur */
        int caseX, caseY, code;

		printf("Entrez les coordonnees de la case cible :\n");

		if (scanf("%d %d", &caseX, &caseY) == 0) {
			printf("Erreur de saisie\n");
		} else {
			code = deplacerOuAttaquer(actuel, monde, caseX, caseY);
		}

		if (code < 0) {
			printf("Vous ne pouvez pas cibler cette case\n");
		} else if (code == 1) {
			printf("Deplacement\n");
		} else if (code == 2){
			printf("Victoire\n");
		} else if (code == 3){
			printf("Defaite\n");
		}	

        actuel = actuel->suiv;
    }

    afficheMonde(*monde);

    char fin;

    while(fin != 'f') {
    	printf("Entrez 'f' pour terminer votre tour\n");
    	scanf("%c", &fin);
    }
}
