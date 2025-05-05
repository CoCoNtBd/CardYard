#include <stdio.h>
#include "display.h"

// ecart entre les colonnes
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

    // creation carte et defausse de chaque joueur
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        Joueur* joueur = &jeu->joueurs[i];
        printf("%-10s : ", joueur->nom);
        for (int j = 0; j < joueur->nb_cartes; j++) {
            afficher_carte(&joueur->cartes[j]);
            printf(" ");
        }

        // affichage de la defausse
        printf("   Défausse : ");
        if (joueur->nb_defausse > 0) {
            Carte top = joueur->defausse[joueur->nb_defausse - 1];
            printf("[ %2d ]", top.valeur);
        } else {
            printf("[    ]");
        }
        printf("\n");
    }

    // pioche centrale
    printf("\nPioche centrale : ");
    if (jeu->nb_pioche > 0) {
        printf("[ ? ] (%d carte)\n", jeu->nb_pioche);
    } else {
        printf("[ Vide ]\n");
    }

    // les tours
    printf("Tour actuel : Joueur %d (%s)\n", jeu->tour_actuel + 1, jeu->joueurs[jeu->tour_actuel].nom);
    printf("============================================================================\n");
}



void afficher_scores(const Jeu* jeu, const int* scores) {
    printf("\n--- Scores des joueurs ---\n");
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        printf("%s : %d point", jeu->joueurs[i].nom, scores[i]);
        if (scores[i] > 1) {
            printf("s");
        }
        printf("\n");
    }
}
