#include <stdio.h>
#include "display.h"

#define ecart 12 // Largeur fixe pour aligner les colonnes

void afficher_carte(const Carte* carte) {
    if (carte->visible) {
        printf("[ %2d ]", carte->valeur);
    } else {
        printf("[ ?? ]");
    }
}

void afficher_plateau(const Jeu* jeu) {
    printf("\n============== PLATEAU DE JEU ==============\n\n");

    // Noms des joueurs
    printf("JOUEURS    :   ");
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        printf("%-*s", ecart, jeu->joueurs[i].nom);
    }
    printf("\n");

    // Cartes personnelles (en ligne)
    int nb_cartes = jeu->joueurs[0].nb_cartes;
    for (int ligne = 0; ligne < nb_cartes; ++ligne) {
        printf("Carte %-5d:   ", ligne + 1);
        for (int j = 0; j < jeu->nb_joueurs; ++j) {
            afficher_carte(&jeu->joueurs[j].cartes[ligne]);
            printf("%*s", ecart - 7, "");
        }
        printf("\n");
    }

    // Défausses
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

    // Tour actuel
    printf("Tour actuel : Joueur %d (%s)\n", jeu->tour_actuel + 1, jeu->joueurs[jeu->tour_actuel].nom);
    printf("============================================\n");
}

void afficher_scores(const Jeu* jeu, const int* scores) {
    printf("\n--- Scores des joueurs ---\n");
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        printf("%s : %d point%s\n", jeu->joueurs[i].nom, scores[i], scores[i] > 1 ? "s" : "");
    }
}

// Facultatif : affichage individuel d’un joueur
void afficher_joueur(const Joueur* joueur) {
    printf("Joueur : %s\n", joueur->nom);
    printf("Cartes : ");
    for (int i = 0; i < joueur->nb_cartes; ++i) {
        afficher_carte(&joueur->cartes[i]);
        printf(" ");
    }
    printf("\n");

    printf("Défausse : ");
    if (joueur->nb_defausse > 0) {
        Carte top = joueur->defausse[joueur->nb_defausse - 1];
        printf("[ %2d ]\n", top.valeur);
    } else {
        printf("[ Vide ]\n");
    }
}

void afficher_defausse(const Carte* defausse, int taille) {
    printf("Défausse : ");
    if (taille > 0) {
        Carte top = defausse[taille - 1];
        printf("[ %2d ] (%d carte%s)\n", top.valeur, taille, taille > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }
}

void afficher_pioche(const Carte* pioche, int taille) {
    printf("Pioche centrale : ");
    if (taille > 0) {
        printf("[ ? ] (%d carte%s)\n", taille, taille > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }
}
