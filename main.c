#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char *argv[])
{

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );

	//
	// Affiche "Bonjour !" a l'écran 
	//
	MLV_draw_rectangle( 10, 50, 40, 20, MLV_rgba(255,0,255,255) );

	//
	// Met a jour l'affichage.
	//
	MLV_actualise_window();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );

	//
	// Ferme la fenêtre
	//
	MLV_free_window();
	gererPartie();

	return 0;
}