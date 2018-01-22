#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <MLV/MLV_all.h>

void gererPartie(void) {

	effaceText(0);

	Monde monde;
	initialiserMonde(&monde);

	UListe liste;

	afficheMonde(monde);

	MLV_draw_text(
        (LARG+1)*CASE,15,
        "Joueur Rouge",
        MLV_rgba(255,255,255,255)
    );

	/* Unités rouges */
	positionneUnite(&liste, SERF, &monde, ROUGE);
	positionneUnite(&liste, GUERRIER, &monde, ROUGE);
	positionneUnite(&liste, SERF, &monde, ROUGE);

	effaceText(0);

	MLV_draw_text(
        (LARG+1)*CASE,15,
        "Joueur Bleu",
        MLV_rgba(255,255,255,255)
    );

	/* Unités bleues */
	positionneUnite(&liste, SERF, &monde, BLEU);
	positionneUnite(&liste, GUERRIER, &monde, BLEU);
	positionneUnite(&liste, SERF, &monde, BLEU);

	int finDePartie = 1; // Pour tester la fin de partie sans gagnant

	/* On joue tant qu'il n'y a pas de gagnant ou d'arrêt volontaire sans gagnant */
	while (testGagnant(monde) == 0 && finDePartie == 1) {
		gererTour(&monde);

		/* Propose un arrêt de partie en fin de tour si personne n'a gagné */
		if (testGagnant(monde) == 0) {
			finDePartie = demandeOuiNon("Voulez vous continuer la partie ?");
		}
		
	}

	effaceText(0);

	/* Annonce du gagnant */
	if (testGagnant(monde) == 1) {
		MLV_draw_text(
	        (LARG+1)*CASE,15,
	        "Le joueur bleu remporte la partie !",
	        MLV_rgba(255,255,255,255)
	    );
	} else if (testGagnant(monde) == 2) {
		MLV_draw_text(
	        (LARG+1)*CASE,15,
	        "Le joueur rouge remporte la partie !",
	        MLV_rgba(255,255,255,255)
	    );
	} else {
		MLV_draw_text(
	        (LARG+1)*CASE,15,
	        "Pas de gagnant. Arrêt volontaire de la partie.",
	        MLV_rgba(255,255,255,255)
	    );
	}

	MLV_actualise_window();

	viderMonde(&monde);
}

void positionneUnite(UListe *liste, char type, Monde *monde, char couleur) {

	if(creerUnite(type, liste) == 0){
		printf("erreur allocation memoire\n");
	} else {

		MLV_draw_text(
	        (LARG+1)*CASE,45,
	        "Cliquez sur une case pour positionner votre unité",
	        MLV_rgba(255,255,255,255)
	    );

		/* Message d'information pour placer les unités */
		if (couleur == ROUGE){
			MLV_draw_text(
		        (LARG+1)*CASE,75,
		        "Sélectionner une case de la première colonne",
		        MLV_rgba(255,255,255,255)
		    );
		} else {
		    MLV_draw_text(
		        (LARG+1)*CASE,75,
		        "Sélectionner une case de la dernière colonne",
		        MLV_rgba(255,255,255,255)
		    );
		}

	    effaceText(100);

	    /* Annonce le type d'unité à placer */
	    MLV_draw_text(
	        (LARG+1)*CASE,100,
	        "Unité de type : %c",
	        MLV_rgba(255,255,255,255),
	        type
	    );


	    MLV_actualise_window();

	    int caseX, caseY;

		placeBonCote(&caseX, &caseY, couleur);	

		/* Si la case ciblée est hors du plateau ou que la case est déjà occupée */
		while (caseX < 0 || caseX > (LARG - 1) || caseY < 0 || caseY > (LONG - 1) || placerAuMonde(*liste, monde, caseX, caseY, couleur) == 0){

			errorMessage("Case occupée ! Réessayer !");
			
			placeBonCote(&caseX, &caseY, couleur);		

		}

	}

	afficheMonde(*monde);
}

/* Permet de placer les unités du bon côté du plateau selon leur couleur */
void placeBonCote(int *caseX, int *caseY, char couleur) {
	MLV_wait_mouse(caseY, caseX);
			
	/* Place les unites rouges sur la première colonne */
	if(couleur == ROUGE){
		*caseX /= CASE;
		*caseY = 0;
	}

	/* Place les unités bleues sur la dernière colonne */
	if(couleur == BLEU){
		*caseX /= CASE;
		*caseY = LONG-1;
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