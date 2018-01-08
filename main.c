#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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

	deplacerUnite(liste, &monde, 2, 0);

	afficheMonde(monde);

	printf("Le joueur rouge a :\n");
	afficherListe(monde.rouge);

	printf("Le joueur bleu a :\n");
	afficherListe(monde.bleu);

	enleverUnite(monde.bleu->suiv->suiv, &monde);

	printf("Le joueur bleu a :\n");
	afficherListe(monde.bleu);

	enleverUnite(monde.bleu, &monde);

	printf("Le joueur bleu a :\n");
	afficherListe(monde.bleu);

	afficheMonde(monde);

	return 0;
}