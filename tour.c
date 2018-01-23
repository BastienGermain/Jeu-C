#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <MLV/MLV_all.h>

/* Test la couleur du joueur */
void gererDemiTour(char joueur, Monde *monde) {
	if (joueur == ROUGE){
		deroulementDemiTour(monde->rouge, monde);
	} else {
		deroulementDemiTour(monde->bleu, monde);
	}
}

void deroulementDemiTour(UListe listeJoueur, Monde *monde) {

	Unite *actuel = listeJoueur;

	/* on parcourt les unités */
	while (actuel != NULL)
    {	
    	/* à chaque unité on affiche le plateau et les infos de l'unité */
        afficheMonde(*monde);
        afficherInfosUnite(*actuel);

        /* indique l'unité sélectionnée */
        MLV_draw_filled_rectangle(actuel->posY*CASE, actuel->posX*CASE, 3, CASE, MLV_rgba(230,230,30,255));
        MLV_draw_filled_rectangle(actuel->posY*CASE, actuel->posX*CASE, CASE, 3, MLV_rgba(230,230,30,255));
        MLV_draw_filled_rectangle((actuel->posY+1)*CASE - 3, actuel->posX*CASE, 3, CASE, MLV_rgba(230,230,30,255));
        MLV_draw_filled_rectangle(actuel->posY*CASE, (actuel->posX+1)*CASE - 3, CASE, 3, MLV_rgba(230,230,30,255));

       	MLV_actualise_window();

        /* demande au joueur une case à cibler */
        int caseX, caseY, code;

        MLV_draw_text(
	        (LARG+1)*CASE,165,
	        "Cliquez sur une case pour attaquer ou vous déplacer",
	        MLV_rgba(255,255,255,255)
	    );

	    MLV_actualise_window();

        /* Attend que l'utilisateur clique sur le bouton gauche de la souris */
			MLV_wait_mouse(&caseY, &caseX);

			caseX /= CASE;
			caseY /= CASE;
			
			code = deplacerOuAttaquer(actuel, monde, caseX, caseY);

		while (code < 0) {
			errorMessage("Cible incorrecte ! Réessayez !");

			MLV_wait_mouse(&caseY, &caseX);

			caseX /= CASE;
			caseY /= CASE;
			
			code = deplacerOuAttaquer(actuel, monde, caseX, caseY);
		}

		/* renvoie le résultat de l'action au joueur */

		if (code == 1) {
			printf("Deplacement\n");
		} else if (code == 2){
			printf("Combat : victoire\n");
		} else if (code == 3){
			printf("Combat : defaite\n");
		}	

        actuel = actuel->suiv;
    }

    afficheMonde(*monde);

    int width_box, height_box; /* Size of the text_box */

    effaceText(60);

    /* Demande la validation de la fin du tour */
    creerButton("Fin du tour", (LARG+1)*CASE, (LONG-2)*CASE, &width_box, &height_box);

    int reponseClick;
    while (reponseClick != 1){

    	int clickX, clickY;
		MLV_wait_mouse(&clickX, &clickY);

    	reponseClick = clickButton(clickX, clickY, (LARG+1)*CASE, (LONG-2)*CASE, width_box, height_box);
    }

}

/* Gère un tour complet (les deux joeurs jouent) */
void gererTour(Monde *monde) {

	effaceText(0);

    monde->tour += 1;

	MLV_draw_text(
        (LARG+1)*CASE,15,
        "Tour : %d",
        MLV_rgba(255,255,255,255),
        monde->tour
    );

	MLV_draw_text(
        (LARG+1)*CASE,45,
        "Joueur Rouge",
        MLV_rgba(255,255,255,255)
    );

	gererDemiTour(ROUGE, monde);

	effaceText(45);

	MLV_draw_text(
        (LARG+1)*CASE,45,
        "Joueur Bleu",
        MLV_rgba(255,255,255,255)
    );

	gererDemiTour(BLEU, monde);	
}