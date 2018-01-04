#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define LONG 12
#define LARG 18

#define ROUGE 'R'
#define BLEU 'B'

#define SERF 's'
#define GUERRIER 'g'

int creerUnite(char type, UListe *ULst){
	/* ULst est un pointeur sur pointeur (UListe) */

	Unite *new = malloc(sizeof(Unite));

	if (new == NULL){
		return 0;
	} else {
		new->type = type;
		new->suiv = *ULst; /* La nouvelle unité aura un pointeur vers l'actuelle entrée de liste */
		*ULst = new; /* On fait pointer l'entrée de liste sur la nouvelle unité */
		return 1;
	}

}

int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur){
	/* Si la case est libre */
	if (monde->plateau[posX][posY] == NULL) {
		monde->plateau[posX][posY] = unite;
		unite->couleur = couleur;
		/* On met à jour les listes d'unités des joueurs */
		if (couleur == ROUGE){
			monde->rouge = unite;
		} else {
			monde->bleu = unite;
		}
		return 1;
	} else {
		return 0;
	}

}