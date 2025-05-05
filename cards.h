#ifndef CARDS_H
#define CARDS_H

typedef struct {
    int valeur;
    int visible; // 0 = carte face caché, 1 = carte visible
} Carte;

// creation, manipulation des carte
Carte creer_carte(int valeur, int visible);

// Mélange de la pioche
void melanger_pioche(Carte* pioche, int taille);

// generation de la pioche avec les valeurs par defaut
Carte* generer_pioche_defaut(int* taille_pioche);

#endif
