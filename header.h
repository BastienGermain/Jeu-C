#ifndef UNITE_H
#define UNITE_H

#define LONG 12
#define LARG 18
#define ROUGE 'R'
#define BLEU 'B'
#define SERF 's'
#define GUERRIER 'g'

typedef struct Unite{
	int posX, posY;
	char couleur; 
	char type; 
	struct Unite *suiv; 
} Unite, *UListe;

typedef struct Monde {
	Unite *plateau[LONG][LARG]; /* tableau de pointeurs sur Unite */
	int tour; /* Numero du tour */
	UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde; 

void initialiserMonde(Monde *monde);
int afficheMonde(Monde monde);

int creerUnite(char type, UListe *ULst);
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur);

#endif