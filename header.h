#ifndef HEADER_H
#define HEADER_H

/* dimension du monde en nombre de cases */
#define LONG 10
#define LARG 10
/* l'origine est en haut à gauche */

/* taille d'une case du plateau */
#define CASE 50

/* nb de pièges sur le plateau */
#define NBPIEGES 10

#define ROUGE 'R' /* identifiant du premier joueur */ 
#define BLEU 'B' /* identifiant du deuxieme joueur */

/* les types d'unités */
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
	int piege[NBPIEGES][2]; /* tableau de coordonées pour les pieges */
	int tour; /* Numero du tour */
	UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde; 


/* monde.c */
void initialiserMonde(Monde *monde);
int afficheMonde(Monde monde);
void viderMonde(Monde *monde);

/* unite.c */
int creerUnite(char type, UListe *ULst);
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur);
void afficherListe(UListe liste);
void afficherInfosUnite(Unite unite);

/* action.c */
void deplacerUnite(Unite *unite, Monde *monde, int destX, int destY);
void enleverUnite(Unite *unite, Monde *monde);
void supprimerUniteListe(Unite *aSupprime, UListe *liste);
int attaquer(Unite *unite, Monde *monde, int destX, int destY);
int deplacerOuAttaquer(Unite *unite, Monde *monde, int destX, int destY);
int estVoisine(int posX, int posY, int destX, int destY);
char quelProprietaire(Unite *unite, Monde monde);

/* tour.c */
void gererDemiTour(char joueur, Monde *monde);
void deroulementDemiTour(UListe listeJoueur, Monde *monde);
void gererTour(Monde *monde);

/* partie.c */
void gererPartie(void);
void positionneUnite(UListe *liste, char type, Monde *monde, char couleur);
int testGagnant(Monde monde);
int demandeOuiNon(char question[]);

/* mlv.c */
void effaceText(int hauteurDepart);
void creerButton(char message[], int posX, int posY, int *width_text, int *height_text);
int clickButton(int clickX, int clickY, int posX, int posY, int width_box, int height_box);
void errorMessage(char message[]);

#endif