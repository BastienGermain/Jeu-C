#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "header.h"

int main()
{
	/* Créé et affiche la fenêtre */
	MLV_create_window( "plateau", "plateau", (LARG+9)*CASE, LONG*CASE );

	int nouvellePartie = 1;
		
	while (nouvellePartie == 1) {
		// on (re)commence une partie
		gererPartie();

		nouvellePartie = demandeOuiNon("Voulez vous recommencer une partie ?");
	} 
		
	MLV_free_window();
	
	return 0;
}