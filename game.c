#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "save.h"
#include "display.h"
#include "utils.h"

#define MAX_JOUEURS 4
#define CARTES_PAR_JOUEUR 6

typedef struct {
    char nom[50];
    int score;
} Resultat;

int main() {
    Jeu jeu;
    int choix;
    
    //introduction jeu
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
        
        // lance le dernier tour si les condition sont reuni
        verifier_fin_partie(&jeu); 

        if (jeu.tours_restants == 0) {
            jeu.jeu_termine = 1;
            printf("\nLa partie est terminée après le dernier tour !\n");
        } else if (jeu.tours_restants > 0) {
            jeu.tours_restants--;
        }

        // demande si le joueur souhaite quitter la partie
        printf("\nSouhaitez-vous quitter la partie ? (1=Oui / 0=Non) : ");
        int quitter = demander_entier("", 0, 1);
        if (quitter) {
            printf("Souhaitez-vous sauvegarder avant de quitter ? (1=Oui / 0=Non) : ");
            int save = demander_entier("", 0, 1);
            if (save) {
                char fichier[50];
                demander_chaine("Nom du fichier de sauvegarde", fichier, 50);
                if (sauvegarder_jeu(&jeu, fichier)) {
                    printf("Sauvegarde réussie !\n");
                } else {
                    printf("Échec de la sauvegarde.\n");
                }
            }
            printf("Vous avez quitté la partie.\n");
            return 0;
        }
    }



Resultat scores[MAX_JOUEURS];

// calcule des score
for (int i = 0; i < jeu.nb_joueurs; i++) {
    scores[i].score = 0;
    strcpy(scores[i].nom, jeu.joueurs[i].nom);
    for (int j = 0; j < jeu.joueurs[i].nb_cartes; j++) {
        scores[i].score += jeu.joueurs[i].cartes[j].valeur;
    }
}

// tri des scores dans l'ordre croissant
for (int i = 0; i < jeu.nb_joueurs - 1; i++) {
    for (int j = i + 1; j < jeu.nb_joueurs; j++) {
        if (scores[j].score < scores[i].score) {
            Resultat tmp = scores[i];
            scores[i] = scores[j];
            scores[j] = tmp;
        }
    }
}

// affichage final
for (int i = 0; i < jeu.nb_joueurs; i++) {
    printf("%s : %d point", scores[i].nom, scores[i].score);
    if (scores[i].score > 1) {
        printf("s");
    }
    printf("\n");
}

printf("\n🎉 Le gagnant est : %s avec %d points ! 🎉\n", scores[0].nom, scores[0].score);

//liberation de la memoire
liberer_jeu(&jeu);

return 0;
}
