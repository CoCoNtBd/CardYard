#ifndef PLAYER_H
#define PLAYER_H

#define MAX_DEFAUSSE 100   // Limite maximale de cartes dans la défausse d'un joueur

#include "cards.h"

// Structure représentant un joueur
typedef struct {
    char nom[50];         // Nom du joueur
    Carte* cartes;        // Cartes personnelles en main (tableau dynamique)
    int nb_cartes;        // Nombre de cartes personnelles

    Carte* defausse;      // Pile des cartes défaussées (face visible)
    int nb_defausse;      // Nombre de cartes actuellement dans la défausse
} Joueur;

// Initialise un joueur avec un nombre de cartes donné
// Alloue dynamiquement les tableaux de cartes et de défausse
void initialiser_joueur(Joueur* joueur, int nb_cartes);

// Retourne 1 si toutes les cartes du joueur sont visibles, 0 sinon
// Utile pour détecter la fin de partie
int toutes_cartes_visibles(const Joueur* joueur);

// Ajoute une carte à la défausse du joueur (elle est rendue visible automatiquement)
void ajouter_a_defausse(Joueur* joueur, Carte c);

// Échange une carte de la main avec une nouvelle carte, et envoie l'ancienne en défausse
void echanger_carte(Joueur* joueur, Carte nouvelle, int index_carte);

#endif
