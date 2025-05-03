#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "cards.h"

// Initialise un joueur avec un nom et un nombre de cartes
void initialiser_joueur(Joueur* joueur, int nb_cartes) {
    joueur->nb_cartes = nb_cartes;
    joueur->cartes = malloc(nb_cartes * sizeof(Carte));
    joueur->nb_defausse = 0;
    joueur->defausse = NULL;
}

// Vérifie si toutes les cartes du joueur sont visibles
int toutes_cartes_visibles(const Joueur* joueur) {
    for (int i = 0; i < joueur->nb_cartes; ++i) {
        if (!joueur->cartes[i].visible)
            return 0;
    }
    return 1;
}

// Ajoute une carte dans la défausse du joueur
void ajouter_a_defausse(Joueur* joueur, Carte c) {
    joueur->defausse = realloc(joueur->defausse, sizeof(Carte) * (joueur->nb_defausse + 1));
    joueur->defausse[joueur->nb_defausse++] = c;
}

// Échange une carte du joueur avec une nouvelle carte (indexé)
void echanger_carte(Joueur* joueur, Carte nouvelle, int index_carte) {
    Carte ancienne = joueur->cartes[index_carte];
    joueur->cartes[index_carte] = nouvelle;
    joueur->cartes[index_carte].visible = 1;
    ajouter_a_defausse(joueur, ancienne);
}
