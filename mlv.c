#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <MLV/MLV_all.h>

/* Efface le texte dans la partie noire à partir de la hauteur en paramètre */
void effaceText(int hauteurDepart) {
	MLV_draw_filled_rectangle(LARG*CASE, hauteurDepart, 9*CASE, LONG*CASE - hauteurDepart, MLV_rgba(0,0,0,255));

	MLV_actualise_window();
}

void creerButton(char message[], int posX, int posY, int *width_box, int *height_box) {

	/* récupère la taille de la boîte contenant le texte (utile pour vérifier le click) */
	MLV_get_size_of_adapted_text_box(
		message,
		CASE/3,
		width_box, height_box
	);

    MLV_draw_adapted_text_box(
        posX, posY,
        message,
        CASE / 3,
        MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,255), MLV_rgba(255,255,255,0),
        MLV_TEXT_CENTER
    );

    MLV_actualise_window();
}

int clickButton(int clickX, int clickY, int posX, int posY, int width_box, int height_box) {

    if (clickX < posX || clickX > posX + width_box || clickY < posY || clickY > posY + height_box) {
    	// Le click n'est pas sur le bouton
    	return 0;
    } else {
    	return 1;
    }
}

void errorMessage(char message[]) {
	MLV_draw_text(
        (LARG+1)*CASE,(LONG-1)*CASE,
        message,
        MLV_rgba(255,100,100,255)
    );

    MLV_actualise_window();
}