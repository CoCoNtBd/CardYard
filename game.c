#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "cards.h"
#include "display.h"
#include "utils.h"

// Initialise le jeu : crée les joueurs, génère et mélange la pioche, distribue les cartes
void initialiser_jeu(Jeu* jeu, int nb_joueurs, int nb_cartes) {
    jeu->nb_joueurs = nb_joueurs;
    jeu->tour_actuel = 0;
    jeu->jeu_termine = 0;
    jeu->tours_restants = -1;

    // Création de la pioche et mélange
    jeu->pioche = generer_pioche_defaut(&jeu->nb_pioche);
    melanger_pioche(jeu->pioche, jeu->nb_pioche);

    // Initialisation des joueurs
    jeu->joueurs = malloc(nb_joueurs * sizeof(Joueur));
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%49s", jeu->joueurs[i].nom);   // Saisie du nom du joueur
        while (getchar() != '\n');            // Nettoie le buffer d'entrée
        initialiser_joueur(&jeu->joueurs[i], nb_cartes);
    }

    distribuer_cartes(jeu);
}

// Distribue les cartes aux joueurs depuis la pioche (face cachée)
void distribuer_cartes(Jeu* jeu) {
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; j++) {
            jeu->joueurs[i].cartes[j] = jeu->pioche[--jeu->nb_pioche]; // Dernière carte de la pioche
            jeu->joueurs[i].cartes[j].visible = 0; // Toutes les cartes sont distribuées face cachée
        }
    }
}

// Gère le déroulement d'un tour de jeu pour le joueur courant
void jouer_tour(Jeu* jeu) {
    Joueur* joueur = &jeu->joueurs[jeu->tour_actuel];
    printf("\n--- Tour de %s ---\n", joueur->nom);

    afficher_plateau(jeu); // Affiche le plateau avant le tour

    // Demande au joueur de choisir entre piocher ou prendre une défausse
    int choix = demander_entier_secure("Voulez-vous piocher (1) ou prendre une défausse (2)", 1, 2);

    Carte nouvelle;

    if (choix == 1) {
        // Piocher depuis la pioche centrale
        if (jeu->nb_pioche == 0) {
            printf("La pioche est vide ! Vous ne pouvez pas piocher.\n");
            return;
        }
        nouvelle = jeu->pioche[--jeu->nb_pioche];
        nouvelle.visible = 1; // La carte piochée est montrée
        printf("Vous avez pioché :\n");
        afficher_cartes_en_ligne(&nouvelle, 1, NULL);
    } else {
        // Prendre depuis la défausse d'un joueur
        int cible = demander_entier_secure("Choisissez la défausse d'un joueur (1 à nombre de joueurs)", 1, jeu->nb_joueurs) - 1;

        if (jeu->joueurs[cible].nb_defausse > 0) {
            nouvelle = jeu->joueurs[cible].defausse[--jeu->joueurs[cible].nb_defausse];
            nouvelle.visible = 1;
        } else {
            // Défausse vide => pioche de secours
            printf("Défausse vide. ");
            if (jeu->nb_pioche == 0) {
                printf("Et la pioche est vide aussi. Aucun échange possible.\n");
                return;
            }
            nouvelle = jeu->pioche[--jeu->nb_pioche];
            nouvelle.visible = 1;
            printf("Pioche par défaut :\n");
            afficher_cartes_en_ligne(&nouvelle, 1, NULL);
        }
    }

    // Demande au joueur avec quelle carte il veut échanger
    int index = demander_entier_secure("Quelle carte échanger (1 à nb cartes)", 1, joueur->nb_cartes) - 1;

    // Échange : l'ancienne carte va en défausse, la nouvelle prend sa place
    Carte ancienne = joueur->cartes[index];
    joueur->cartes[index] = nouvelle;
    joueur->cartes[index].visible = 1;

    ajouter_a_defausse(joueur, ancienne); // Important : la carte va en défausse visible

    // Passe au joueur suivant
    jeu->tour_actuel = (jeu->tour_actuel + 1) % jeu->nb_joueurs;
}

// Vérifie si un joueur a terminé (toutes ses cartes sont visibles)
int verifier_fin_partie(Jeu* jeu) {
    if (jeu->tours_restants != -1)
        return 0;

    for (int i = 0; i < jeu->nb_joueurs; i++) {
        if (toutes_cartes_visibles(&jeu->joueurs[i])) {
            printf("\n%s a révélé toutes ses cartes ! Dernier tour pour les autres joueurs...\n", jeu->joueurs[i].nom);
            jeu->tours_restants = jeu->nb_joueurs - 1;
            return 1;
        }
    }
    return 0;
}

// Calcule les scores finaux des joueurs en additionnant les valeurs de leurs cartes
void calculer_scores(const Jeu* jeu, int* scores) {
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        scores[i] = 0;
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; j++) {
            scores[i] += jeu->joueurs[i].cartes[j].valeur;
        }
    }
}

// Libère toute la mémoire allouée dynamiquement pour la partie
void liberer_jeu(Jeu* jeu) {
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* joueur = &jeu->joueurs[i];
        if (joueur->cartes != NULL) {
            free(joueur->cartes);
            joueur->cartes = NULL;
        }
        if (joueur->defausse != NULL) {
            free(joueur->defausse);
            joueur->defausse = NULL;
        }
    }

    if (jeu->joueurs != NULL) {
        free(jeu->joueurs);
        jeu->joueurs = NULL;
    }

    if (jeu->pioche != NULL) {
        free(jeu->pioche);
        jeu->pioche = NULL;
    }
}
