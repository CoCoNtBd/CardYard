#include <stdio.h>
#include "display.h"

 // largeur pour les ecart en colonne
#define ecart 12

void afficher_carte(const Carte* carte) {
    if (carte->visible) {
        printf("[ %2d ]", carte->valeur);
    } else {
        printf("[ ?? ]");
    }
}

void afficher_plateau(const Jeu* jeu) {
    printf("\n============================== PLATEAU DE JEU ==============================\n\n");

    // Cartes et défausse associées à chaque joueur
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* joueur = &jeu->joueurs[i];
        printf("%-10s : ", joueur->nom);
        for (int j = 0; j < joueur->nb_cartes; ++j) {
            afficher_carte(&joueur->cartes[j]);
            printf(" ");
        }

        // Affichage de la défausse du joueur
        printf("   Défausse : ");
        if (joueur->nb_defausse > 0) {
            Carte top = joueur->defausse[joueur->nb_defausse - 1];
            printf("[ %2d ]", top.valeur);
        } else {
            printf("[    ]");
        }
        printf("\n");
    }

    // Pioche centrale
    printf("\nPioche centrale : ");
    if (jeu->nb_pioche > 0) {
        printf("[ ? ] (%d carte%s)\n", jeu->nb_pioche, jeu->nb_pioche > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }

    // Tour actuel
    printf("Tour actuel : Joueur %d (%s)\n", jeu->tour_actuel + 1, jeu->joueurs[jeu->tour_actuel].nom);
    printf("============================================================================\n");
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
