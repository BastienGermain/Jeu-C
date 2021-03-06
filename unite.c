#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int creerUnite(char type, UListe *liste) {
	/* liste est un pointeur sur pointeur (UListe) */

	Unite *new = malloc(sizeof(Unite));

	if (new == NULL){ /* Si malloc échoue */
		return 0;
	} else {
		new->type = type;
		new->suiv = *liste; /* La nouvelle unité aura un pointeur vers l'actuelle entrée de liste (càd unité déjà existante) */
		*liste = new; /* On fait pointer l'entrée de liste sur la nouvelle unité */
		return 1;
	}

}

int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur) {

	/* Si la case est libre */
	if (monde->plateau[posX][posY] == NULL) {
		monde->plateau[posX][posY] = unite;

		unite->couleur = couleur;
		unite->posX = posX;
		unite->posY = posY;

		/* On met à jour les listes d'unités des joueurs */
		if (couleur == ROUGE){
			unite->suiv = monde->rouge; /* monde->rouge ==> UListe */
			monde->rouge = unite;
		} else {
			unite->suiv = monde->bleu;
			monde->bleu = unite;
		}

		return 1;

	} else {
		return 0;
	}

}

/* Pas nécessaire mais utile pour tester */
void afficherListe(UListe liste) {

	Unite *actuel = liste;

    while (actuel != NULL)
    {
        afficherInfosUnite(*actuel);
        actuel = actuel->suiv;
    }
}

void afficherInfosUnite(Unite unite) {

	effaceText(60);

	MLV_draw_text(
        (LARG+1)*CASE, 75,
        "Unité sélectionnée :",
        MLV_rgba(255,255,255,255)
    );

    MLV_draw_text(
        (LARG+1)*CASE, 105,
        "Type : %c",
        MLV_rgba(255,255,255,255),
        unite.type
    );

    MLV_draw_text(
        (LARG+1)*CASE, 135,
        "Position : %d, %d",
        MLV_rgba(255,255,255,255),
        unite.posY + 1, unite.posX + 1

    );

    MLV_actualise_window();
}
