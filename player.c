#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "cards.h"

// Initialise un joueur avec un certain nombre de cartes
// Alloue dynamiquement l'espace pour ses cartes personnelles et sa défausse
void initialiser_joueur(Joueur* joueur, int nb_cartes) {
    joueur->nb_cartes = nb_cartes;                                  // Nombre de cartes à jouer
    joueur->cartes = malloc(nb_cartes * sizeof(Carte));             // Allocation des cartes en main
    joueur->nb_defausse = 0;                                        // Défausse vide au départ
    joueur->defausse = malloc(MAX_DEFAUSSE * sizeof(Carte));       // Allocation de la pile de défausse
}

// Vérifie si un joueur a révélé toutes ses cartes (fin de partie possible)
int toutes_cartes_visibles(const Joueur* joueur) {
    for (int i = 0; i < joueur->nb_cartes; ++i) {
        if (!joueur->cartes[i].visible)  // Si au moins une carte est encore face cachée
            return 0;
    }
    return 1; // Toutes les cartes sont visibles
}

// Ajoute une carte dans la défausse du joueur (elle est automatiquement retournée face visible)
void ajouter_a_defausse(Joueur* joueur, Carte c) {
    if (joueur->nb_defausse < MAX_DEFAUSSE) {
        c.visible = 1; // ⚠ Important : les cartes dans la défausse sont toujours visibles
        joueur->defausse[joueur->nb_defausse++] = c;
    } else {
        // Message d'erreur si on dépasse la taille autorisée de la défausse
        printf("Erreur : la défausse de %s est pleine !\n", joueur->nom);
    }
}

// Remplace une carte de la main par une nouvelle, et ajoute l'ancienne à la défausse
void echanger_carte(Joueur* joueur, Carte nouvelle, int index_carte) {
    Carte ancienne = joueur->cartes[index_carte];  // Sauvegarde l'ancienne carte
    joueur->cartes[index_carte] = nouvelle;        // Remplace par la nouvelle
    joueur->cartes[index_carte].visible = 1;       // La nouvelle carte est toujours visible
    ajouter_a_defausse(joueur, ancienne);          // L'ancienne carte part dans la défausse (visible)
}
