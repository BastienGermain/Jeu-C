#include <stdio.h>
#include <stdlib.h>

/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18
/* l'origine est en haut à gauche */

#define ROUGE 'R' //identifiant du premier joueur
#define BLEU 'B' //identifiant du deuxieme joueur

/* les types d'unités */
#define SERF 's'
#define GUERRIER 'g'


typedef struct Unite{
	int posX, posY; /* coordonnees de l'unité */
	char couleur; /* ROUGE ou BLEU */
	char type; /* GUERRIER ou SERF */
	struct Unite *suiv; /* pointeur sur unité suivante */
} Unite, *UListe;

/* UListe est un pointeur sur Unite */

typedef struct Monde{
	Unite *plateau[LONG][LARG]; /* tableau de pointeurs sur Unite */
	int tour; /* Numero du tour */
	UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;

void initialiserMonde(Monde *monde){
	monde->tour = 0;

	/* Parcourt du plateau de jeu */
	int i, j;
	for (i = 0; i < LONG; i++){
		for (j = 0; j < LARG; j++) {
			monde->plateau[i][j] = NULL;
		}
	}
}

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
	// Si la case est libre
	if (monde->plateau[posX][posY] == NULL) {
		monde->plateau[posX][posY] = unite;
		unite->couleur = couleur;
		// On met à jour les listes d'unités des joueurs
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

int afficheMonde(Monde monde){
	int i, j;
	for (i = 0; i < LONG; i++){
		printf("------------------------");
		printf("------------------------");
		printf("-------------------------\n");

		for (j = 0; j < LARG; j++) {

			if (monde.plateau[i][j] == NULL){
				printf("|   ");
			} else {
				// Test du propriétaire
				if (monde.plateau[i][j]->couleur == ROUGE){
					printf("|R");
				} else {
					printf("|B");
				}
				//Test du type d'unité
				if (monde.plateau[i][j]->type == SERF){
					printf("* "); // * pour un SERF
				} else {
					printf("+ "); // + pour un GUERRIER
				}
			}
			
		}
		printf("|\n");
	}
	printf("------------------------");
	printf("------------------------");
	printf("-------------------------\n");
}

int main()
{
	Monde monde;
	initialiserMonde(&monde);

	UListe liste;

	if(creerUnite(SERF, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 0, 0, ROUGE) == 0){
			printf("case occupe\n");
		}
	}

	if(creerUnite(GUERRIER, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 0, 1, ROUGE) == 0){
			printf("case occupe\n");
		}
	}

	if(creerUnite(SERF, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 0, 2, ROUGE) == 0){
			printf("case occupe\n");
		}
	}

	if(creerUnite(SERF, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 1, 0, BLEU) == 0){
			printf("case occupe\n");
		}
	}

	if(creerUnite(GUERRIER, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 1, 1, BLEU) == 0){
			printf("case occupe\n");
		}
	}

	if(creerUnite(SERF, &liste) == 0){
		printf("erreur alloc\n");
	} else {
		if (placerAuMonde(liste, &monde, 1, 2, BLEU) == 0){
			printf("case occupe\n");
		}
	}

	afficheMonde(monde);
}