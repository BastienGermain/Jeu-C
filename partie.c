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

	MLV_Keyboard_button touche;

	printf("Voulez-vous arreter la partie sans gagnant ? (ECHAP = oui) (autre touche = non)\n");

	MLV_wait_keyboard( &touche, NULL, NULL );

	if (touche == MLV_KEYBOARD_ESCAPE) {
		return 1;
	} else {
		return 0;
	}
}