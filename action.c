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

	/* On met à jour les infos de l'unité */
	unite->posX = destX;
	unite->posY = destY;
	
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

int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY) {
	
	/* Si la case ciblée est hors du plateau */
	if (destX < 0 || destX > (LARG - 1) || destY < 0 || destY > (LONG - 1)){
		return -1;
	}
	
	/* On cherche la case actuelle de l'unité */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			
			if (monde->plateau[i][j] == unite){
				/* Si la case n'est pas voisine */
				if (estVoisine(i, j, destX, destY) == 0){
					return -2;
				}
			}
		}
	}

	/* On teste si la case ciblée n'est pas un piège */
	int p = 0;
	while (p < NBPIEGES) {
		if (monde->piege[p][0] == destY && monde->piege[p][1] == destX) {
			return -4;
		}

		p++;
	}

	/* On regarde si la case ciblée est déjà occupée */
	if (monde->plateau[destX][destY] != NULL){
		/* Si l'unité ciblée est alliée */
		if (quelProprietaire(unite, *monde) == quelProprietaire(monde->plateau[destX][destY], *monde)){
			return -3;
		} else {
			if (attaquer(unite, monde, destX, destY) == 1){
				return 2; /* Victoire */
			} else {
				return 3; /* Défaite */
			}			
		}

	} else {
		/* Si la case n'est pas occupée, on se déplace */
		deplacerUnite(unite, monde, destX, destY);

		/* Si le SERF arrive au bout du plateau on le transforme en GUERRIER */
		if (unite->type == SERF) {
			if (quelProprietaire(unite, *monde) == ROUGE) {
				if (destY == LONG-1) {
					unite->type = GUERRIER;
				}
			} else {
				if (destY == 0) {
					unite->type = GUERRIER;
				}
			}
		}

		return 1;
	}
}

/* Test si la case est voisine de l'unité */
int estVoisine(int posX, int posY, int destX, int destY) {
	int diffX = posX - destX;
	int diffY = posY - destY;

	/* Test si la case ciblée est la même que la case de l'unité */
	if (diffX != 0 || diffY != 0) {
		/* Test si la case ciblée n'est pas une des 8 cases autour de l'unité */
		if (diffX > 3 || diffX < -3 || diffY > 3 || diffY < -3) {
			return 0;
		} else {
			// La case est voisine
			return 1;
		}
	} else {
		return 0;
	}	
}


/* Détermine le propriétaire d'une unité */
char quelProprietaire(Unite *unite, Monde monde) {

    while (monde.rouge != NULL)
    {
        if (monde.rouge == unite) {
        	return ROUGE;
        } else {
        	monde.rouge = monde.rouge->suiv;
        }
        
    }

    return BLEU;
}