#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <MLV/MLV_all.h>

void gererPartie(void) {

	Monde monde;
	initialiserMonde(&monde);

	UListe liste;

	/* Unités rouges */
	positionneUnite(&liste, SERF, &monde, 0, 0, ROUGE);
	positionneUnite(&liste, GUERRIER, &monde, 0, 1, ROUGE);
	positionneUnite(&liste, SERF, &monde, 0, 2, ROUGE);

	/* Unités bleues */
	positionneUnite(&liste, SERF, &monde, 1, 0, BLEU);
	positionneUnite(&liste, GUERRIER, &monde, 1, 1, BLEU);
	positionneUnite(&liste, SERF, &monde, 1, 2, BLEU);

	int finDePartie = 0; // Pour tester la fin de partie sans gagnant

	/* On joue tant qu'il n'y a pas de gagnant ou d'arrêt volontaire sans gagnant */
	while (testGagnant(monde) == 0 && finDePartie == 0) {
		gererTour(&monde);

		/* Propose un arrêt de partie en fin de tour si personne n'a gagné */
		if (testGagnant(monde) == 0) {
			finDePartie = demandeArretPartie();
		}
		
	}

	/* Annonce du gagnant */
	if (testGagnant(monde) == 1) {
		printf("Le joueur bleu remporte la partie.\n");
	} else if (testGagnant(monde) == 2) {
		printf("Le joueur rouge remporte la partie.\n");
	} else {
		printf("Pas de gagnant. Arret volontaire de la partie.\n");
	}

	viderMonde(&monde);
}

void positionneUnite(UListe *liste, char type, Monde *monde, int caseX, int caseY, char couleur) {

	if(creerUnite(type, liste) == 0){
		printf("erreur allocation memoire\n");
	} else {
		if (placerAuMonde(*liste, monde, caseX, caseY, couleur) == 0){
			printf("case occupe\n");
		}
	}
}

int testGagnant(Monde monde) {

	if (monde.rouge == NULL) {
		// Bleu a gagné
		return 1;
	} else if (monde.bleu == NULL) {
		// Rouge a gagné
		return 2;
	} else {
		// Pas de gagnant
		return 0;
	}
}

int demandeArretPartie(void) {

	effaceText(60);

	printf("Voulez-vous arreter la partie sans gagnant ?\n");

	int width_box_oui, height_box_oui, width_box_non, height_box_non;

	creerButton("Oui", 19*CASE, 8*CASE, &width_box_oui, &height_box_oui);
	creerButton("Non", 19*CASE, 10*CASE, &width_box_non, &height_box_non);

    int reponseClickOui, reponseClickNon;
    while (reponseClickOui != 1 && reponseClickNon != 1){
    	int clickX, clickY;
		MLV_wait_mouse(&clickX, &clickY);

    	reponseClickOui = clickButton(clickX, clickY, 19*CASE, 8*CASE, width_box_oui, height_box_oui);
    	reponseClickNon = clickButton(clickX, clickY, 19*CASE, 10*CASE, width_box_non, height_box_non);
    }

    if (reponseClickOui == 1) {
    	// Arrête de la partie
    	return 1;
    } else {
		return 0;
	}

}