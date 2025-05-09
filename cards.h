#ifndef CARDS_H
#define CARDS_H

typedef struct {
    int valeur;
    int visible; // 0 = carte de dos, 1 = carte visible
} Carte;

// création et manipulation de cartes
Carte creer_carte(int valeur, int visible);

// melange aléatoire de la pioche
void melanger_pioche(Carte* pioche, int taille);

// genere la pioche avec les valeur par defaut
Carte* generer_pioche_defaut(int* taille_pioche);

Carte* generer_pioche_personnalisee(int* taille_pioche);



#endif
