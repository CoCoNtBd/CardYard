#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "save.h"
#include "display.h"
#include "utils.h"
#include "cards.h"

#define MAX_JOUEURS 4          // Limite de joueurs maximum
#define NB_CARTES_TOTAL 150    // Taille maximale totale de la pioche (non utilisée directement ici)

// Structure pour stocker les résultats finaux (nom + score)
typedef struct {
    char nom[50];
    int score;
} Resultat;

int main() {
    Jeu jeu;      // Structure principale contenant tout l'état du jeu
    int choix;

    srand(time(NULL)); // Initialisation de l'aléatoire pour le mélange des cartes

    // Menu principal
    printf("Bienvenue dans CardYard !\n");
    printf("1. Nouvelle partie\n");
    printf("2. Charger une partie\n");
    printf("3. Quitter\n");

    choix = demander_entier_secure("Choix", 1, 3);

    if (choix == 3) {
        printf("Au revoir !\n");
        return 0;
    }
    else if (choix == 2) {
        // Chargement d'une sauvegarde
        char fichier[50];
        demander_chaine("Nom du fichier de sauvegarde", fichier, 50);
        if (!charger_jeu(&jeu, fichier)) {
            printf("\nErreur de chargement. Retour au menu.\n");
            return 1;
        }
    }
    else {
        // Création d'une nouvelle partie
        int nb_joueurs = demander_entier_secure("Nombre de joueurs", 2, MAX_JOUEURS);

        // Nombre de cartes aléatoire entre 4 et 10 pour chaque joueur
        int nb_cartes_par_joueur = (rand() % 7) + 4;
        printf("\nNombre de cartes personnelles aléatoire choisi pour tous les joueurs : %d\n", nb_cartes_par_joueur);

        // Choix du type de pioche
        printf("\nChoisissez les valeurs de carte :\n");
        printf("1. Utiliser les valeurs par défaut\n");
        printf("2. Définir manuellement les valeurs\n");
        int choix_valeurs = demander_entier_secure("Choix", 1, 2);

        // Initialisation du jeu
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

        // Création des joueurs
        jeu.joueurs = malloc(nb_joueurs * sizeof(Joueur));
        for (int i = 0; i < nb_joueurs; i++) {
            printf("Nom du joueur %d : ", i + 1);
            scanf("%49s", jeu.joueurs[i].nom);
            while (getchar() != '\n'); // vide le buffer après scanf
            initialiser_joueur(&jeu.joueurs[i], nb_cartes_par_joueur);
        }

        // Distribution initiale des cartes
        distribuer_cartes(&jeu);
    }

    // Boucle principale du jeu
    while (!jeu.jeu_termine) {
        jouer_tour(&jeu);              // Tour du joueur courant
        verifier_fin_partie(&jeu);     // Vérifie si un joueur a révélé toutes ses cartes

        if (jeu.tours_restants == 0) {
            jeu.jeu_termine = 1;
            printf("\nLa partie est terminée après le dernier tour !\n");
        } else if (jeu.tours_restants > 0) {
            jeu.tours_restants--; // Décompte des derniers tours restants
        }

        // Proposition de quitter ou sauvegarder en cours de partie
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

    // Affichage final du plateau avant de montrer les scores
    afficher_plateau(&jeu);

    // Calcul des scores finaux
    Resultat scores[MAX_JOUEURS];
    for (int i = 0; i < jeu.nb_joueurs; i++) {
        scores[i].score = 0;
        strcpy(scores[i].nom, jeu.joueurs[i].nom);
        for (int j = 0; j < jeu.joueurs[i].nb_cartes; j++) {
            scores[i].score += jeu.joueurs[i].cartes[j].valeur;
        }
    }

    // Tri des scores par ordre croissant (le plus petit gagne)
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

    // Affichage du gagnant (premier du classement)
    printf("\n🎉 Le gagnant est : %s avec %d points ! 🎉\n", scores[0].nom, scores[0].score);

    liberer_jeu(&jeu); // Libération mémoire
    return 0;
}
