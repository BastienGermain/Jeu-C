#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main()
{
	/* Créé et affiche la fenêtre */
	MLV_create_window( "plateau", "plateau", 25*CASE, 12*CASE );

	gererPartie();

	//
	// Ferme la fenêtre
	//
	MLV_free_window();

	return 0;
}