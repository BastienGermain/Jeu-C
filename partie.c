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
        int caseX, caseY;
		printf("Entrez les coordonnées de la case où vous souhaitez vous déplacer :\n");
		scanf("%d %d\n", &caseX, &caseY);

		deplacerOuAttaquer(actuel, monde, caseX, caseY);

        actuel = actuel->suiv;
    }
}
