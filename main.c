#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "header.h"

int main()
{
	/* Créé et affiche la fenêtre */
	MLV_create_window( "plateau", "plateau", 27*CASE, 12*CASE );

	gererPartie();

	//
	// Ferme la fenêtre
	//
	MLV_free_window();

	return 0;
}