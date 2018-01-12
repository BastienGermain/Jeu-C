#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void deplacerUnite(Unite *unite, Monde *monde, int destX, int destY) {

	/* On cherche la case actuelle de l'unité */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			if (monde->plateau[i][j] == unite){
				/* On efface l'unité de sa case actuelle */
				monde->plateau[i][j] = NULL;
			}
		}
	}
	/* On inscrit l'unité dans sa nouvelle case */
	monde->plateau[destX][destY] = unite;
}

void enleverUnite(Unite *unite, Monde *monde) {

	/* On cherche la case actuelle de l'unité */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			if (monde->plateau[i][j] == unite){
				/* On efface l'unité de sa case actuelle */
				monde->plateau[i][j] = NULL;
			}
		}
	}

	/* On met à jour les listes d'unités des joueurs */
	if (unite->couleur == ROUGE){
		supprimerUniteListe(unite, &monde->rouge);
	} else {
		supprimerUniteListe(unite, &monde->bleu);
	}

	/* Libère la mémoire */
	free(unite);
}

/* Fonction auxiliaire permettant de supprimer une unité d'une liste */
void supprimerUniteListe(Unite *aSupprime, UListe *liste) {

	/* Si l'unite à supprimer est en début de liste */
	if (aSupprime == *liste){			

		/* On fait pointer la liste sur l'unité qui suit celle à supprimé */
		*liste = aSupprime->suiv;

	/* Si l'unité à supprimer est en seconde position */
	} else if (aSupprime == (*liste)->suiv) {

		/* On fait pointer la première unité de la liste sur celle qui suit l'unité à supprime */
		(*liste)->suiv = aSupprime->suiv;

	} else {
		/* On conserve la valeur d'entrée de la liste */
		UListe conserve = *liste;

		/* On boucle jusqu'à arriver à l'unité qui précède celle à supprimer */
		while (aSupprime != (*liste)->suiv) {
			*liste = (*liste)->suiv; /* !!! ici l'entrée de la liste est modifiée !!! */
		}

		/* On fait pointer l'unité qui précède sur celle qui suit l'unité à supprimé */
		(*liste)->suiv = aSupprime->suiv;

		/* On remet la bonne valeur d'entrée pour la liste */
		*liste = conserve;
	}
}

int attaquer(Unite *unite, Monde *monde, int cibleX, int cibleY) {

	/* Si l'unité attaquant est un guerrier, elle gagne tout le temps */

	if (unite->type == GUERRIER){
		/* On supprime l'unité attaquée */
		enleverUnite(monde->plateau[cibleX][cibleY], monde);	

		return 1;	
	} else {

		if (monde->plateau[cibleX][cibleY]->type == GUERRIER){
			/* L'unité attaquante est un serf, elle perd face à un guerrier */
			enleverUnite(unite, monde);

			return 0;
		} else {
			/* Les deux unités sont des serfs, on élimine l'unité attaquée */
			enleverUnite(monde->plateau[cibleX][cibleY], monde);

			return 1;
		}
	}
}