#ifndef PLAYER_H
#define PLAYER_H

#include "cards.h"

typedef struct {
    char nom[50];           // Nom du joueur
    Carte* cartes;          // Cartes personnelles
    int nb_cartes;

    Carte* defausse;        // Cartes défaussées
    int nb_defausse;
} Joueur;

// Initialise un joueur avec un nombre de cartes
void initialiser_joueur(Joueur* joueur, int nb_cartes);

// Vérifie si toutes les cartes du joueur sont visibles
int toutes_cartes_visibles(const Joueur* joueur);

// Ajoute une carte dans la défausse du joueur
void ajouter_a_defausse(Joueur* joueur, Carte c);

// Échange une carte d'un joueur avec une nouvelle
void echanger_carte(Joueur* joueur, Carte nouvelle, int index_carte);

#endif
