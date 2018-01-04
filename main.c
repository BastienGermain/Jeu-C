#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18
/* l'origine est en haut à gauche */

#define ROUGE 'R' /* identifiant du premier joueur */ 
#define BLEU 'B' /* identifiant du deuxieme joueur */

/* les types d'unités */
#define SERF 's'
#define GUERRIER 'g'


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

	return 0;
}