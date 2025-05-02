#include <stdio.h>
#include "game.h"
#include "player.h"
#include "cards.h"

#define ecart 12  // largeur fixe pour aligner les colonnes

void afficher_carte(const Carte* carte) {
    if (carte->visible) {
        printf("[ %2d ]", carte->valeur);
    } else {
        printf("[ ?? ]");
    }
}

void afficher_plateau(const Jeu* jeu) {
    printf("\n============== PLATEAU DE JEU ==============\n\n");

    // noms joueurs
    printf("JOUEURS    :   ");
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        printf("%-*s", ecart, jeu->joueurs[i].nom);
    }
    printf("\n");

    int nb_cartes = jeu->joueurs[0].nb_cartes;

    // carte
    for (int ligne = 0; ligne < nb_cartes; ++ligne) {
        printf("Carte %-5d:   ", ligne + 1);
        for (int j = 0; j < jeu->nb_joueurs; ++j) {
            afficher_carte(&jeu->joueurs[j].cartes[ligne]);
            printf("%*s", ecart - 7, ""); // espace après chaque carte
        }
        printf("\n");
    }

    // défausses
    printf("Défausse   :   ");
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* j = &jeu->joueurs[i];
        if (j->nb_defausse > 0) {
            Carte top = j->defausse[j->nb_defausse - 1];
            printf("[ %2d ]%*s", top.valeur, ecart - 7, "");
        } else {
            printf("[    ]%*s", ecart - 7, "");
        }
    }
    printf("\n");

    // Pioche
    printf("\nPioche centrale : ");
    if (jeu->nb_pioche > 0) {
        printf("[ ? ] (%d carte%s)\n", jeu->nb_pioche, jeu->nb_pioche > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }

    // Tour
    printf("Tour actuel : Joueur %d (%s)\n", jeu->tour_actuel + 1, jeu->joueurs[jeu->tour_actuel].nom);
    printf("============================================\n");
}

void afficher_scores(const Jeu* jeu, const int* scores) {
    printf("\n--- Scores des joueurs ---\n");
    for (int i = 0; i




