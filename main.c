#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "save.h"
#include "display.h"
#include "utils.h"

#define MAX_JOUEURS 4
#define CARTES_PAR_JOUEUR 6

int main() {
    Jeu jeu;
    int scores[MAX_JOUEURS];
    int choix;

    printf("Bienvenue dans CardYard !\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger une partie\n");
    printf("3. Quitter\n");

    choix = demander_entier("Choix", 1, 3);

    if (choix == 3) {
        printf("Au revoir !\n");
        return 0;
    } else if (choix == 2) {
        char fichier[50];
        demander_chaine("Nom du fichier de sauvegarde", fichier, 50);
        if (!charger_jeu(&jeu, fichier)) {
            printf("\nErreur de chargement. Retour au menu.\n");
            return 1;
        }
    } else {
        int nb_joueurs = demander_entier("Nombre de joueurs", 2, MAX_JOUEURS);
        initialiser_jeu(&jeu, nb_joueurs, CARTES_PAR_JOUEUR);
    }

    while (!jeu.jeu_termine) {
        jouer_tour(&jeu);
        if (verifier_fin_partie(&jeu)) {
            printf("\nLa partie est terminée !\n");
            break;
        }

        printf("\nSouhaitez-vous sauvegarder ? (1=Oui / 0=Non) : ");
        int save = demander_entier("", 0, 1);
        if (save) {
            char fichier[50];
            demander_chaine("Nom du fichier de sauvegarde", fichier, 50);
            if (sauvegarder_jeu(&jeu, fichier)) {
                printf("Sauvegarde réussie !\n");
            } else {
                printf("Echec de la sauvegarde.\n");
            }
        }
    }

    calculer_scores(&jeu, scores);
    afficher_scores(&jeu, scores);

    return 0;
}
