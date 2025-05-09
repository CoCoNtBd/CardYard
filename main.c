#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "save.h"
#include "display.h"
#include "utils.h"
#include "cards.h"

#define MAX_JOUEURS 4
#define NB_CARTES_TOTAL 150

typedef struct {
    char nom[50];
    int score;
} Resultat;

int main() {
    Jeu jeu;
    int choix;

    srand(time(NULL)); // Initialisation unique pour l'aléatoire

    printf("Bienvenue dans CardYard !\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger une partie\n");
    printf("3. Quitter\n");

    choix = demander_entier_secure("Choix", 1, 3);

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
        int nb_joueurs = demander_entier_secure("Nombre de joueurs", 2, MAX_JOUEURS);

        // Nombre de cartes personnelles aléatoire pour tous (CARD_RAND)
        int nb_cartes_par_joueur = (rand() % 7) + 4; // entre 4 et 10
        printf("\n");
        printf("Nombre de cartes personnelles aléatoire choisi pour tous les joueurs : %d\n", nb_cartes_par_joueur);

        // Choix des valeurs de cartes
        printf("\nChoisissez les valeurs de carte :\n");
        printf("1. Utiliser les valeurs par défaut\n");
        printf("2. Définir manuellement les valeurs \n");
        int choix_valeurs = demander_entier_secure("Choix", 1, 2);

        jeu.nb_joueurs = nb_joueurs;
        jeu.tour_actuel = 0;
        jeu.jeu_termine = 0;
        jeu.tours_restants = -1;

        if (choix_valeurs == 1) {
            jeu.pioche = generer_pioche_defaut(&jeu.nb_pioche);
        } else {
            jeu.pioche = generer_pioche_personnalisee(&jeu.nb_pioche);
        }

        melanger_pioche(jeu.pioche, jeu.nb_pioche);

        jeu.joueurs = malloc(nb_joueurs * sizeof(Joueur));
        for (int i = 0; i < nb_joueurs; i++) {
            printf("Nom du joueur %d : ", i + 1);
            scanf("%49s", jeu.joueurs[i].nom);
            while (getchar() != '\n'); // nettoyer le buffer
            initialiser_joueur(&jeu.joueurs[i], nb_cartes_par_joueur);
        }

        distribuer_cartes(&jeu);
    }

    while (!jeu.jeu_termine) {
        jouer_tour(&jeu);
        verifier_fin_partie(&jeu);

        if (jeu.tours_restants == 0) {
            jeu.jeu_termine = 1;
            printf("\nLa partie est terminée après le dernier tour !\n");
        } else if (jeu.tours_restants > 0) {
            jeu.tours_restants--;
        }

        printf("\nSouhaitez-vous quitter la partie ? (1=Oui / 0=Non) : ");
        int quitter = demander_entier_secure("", 0, 1);
        if (quitter) {
            printf("Souhaitez-vous sauvegarder avant de quitter ? (1=Oui / 0=Non) : ");
            int save = demander_entier_secure("", 0, 1);
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
            liberer_jeu(&jeu);
            return 0;
        }
    }

    // Afficher une dernière fois le plateau avant les scores finaux
    afficher_plateau(&jeu);

    Resultat scores[MAX_JOUEURS];
    for (int i = 0; i < jeu.nb_joueurs; i++) {
        scores[i].score = 0;
        strcpy(scores[i].nom, jeu.joueurs[i].nom);
        for (int j = 0; j < jeu.joueurs[i].nb_cartes; j++) {
            scores[i].score += jeu.joueurs[i].cartes[j].valeur;
        }
    }

    // Trier les scores par ordre croissant
    for (int i = 0; i < jeu.nb_joueurs - 1; i++) {
        for (int j = i + 1; j < jeu.nb_joueurs; j++) {
            if (scores[j].score < scores[i].score) {
                Resultat tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
        }
    }

    // Affichage des scores
    for (int i = 0; i < jeu.nb_joueurs; i++) {
        printf("%s : %d point", scores[i].nom, scores[i].score);
        if (scores[i].score > 1) printf("s");
        printf("\n");
    }

    // Affichage du gagnant
    printf("\n🎉 Le gagnant est : %s avec %d points ! 🎉\n", scores[0].nom, scores[0].score);
    liberer_jeu(&jeu);
    return 0;
}
