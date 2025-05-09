#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "cards.h"
#include "display.h"
#include "utils.h"

// initialise le jeu avec la pioche, les joueur et la distribution des cartes
void initialiser_jeu(Jeu* jeu, int nb_joueurs, int nb_cartes) {
    jeu->nb_joueurs = nb_joueurs;
    jeu->tour_actuel = 0;
    jeu->jeu_termine = 0;

    jeu->pioche = generer_pioche_defaut(&jeu->nb_pioche);
    melanger_pioche(jeu->pioche, jeu->nb_pioche);

    jeu->joueurs = malloc(nb_joueurs * sizeof(Joueur));
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%49s", jeu->joueurs[i].nom);
        while (getchar() != '\n');
        initialiser_joueur(&jeu->joueurs[i], nb_cartes);
    }

    distribuer_cartes(jeu);
    jeu->tours_restants = -1;
    jeu->jeu_termine = 0;
}

// distribution des cartes face cachée
void distribuer_cartes(Jeu* jeu) {
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; j++) {
            jeu->joueurs[i].cartes[j] = jeu->pioche[--jeu->nb_pioche];
            jeu->joueurs[i].cartes[j].visible = 0;
        }
    }
}

void jouer_tour(Jeu* jeu) {
    Joueur* joueur = &jeu->joueurs[jeu->tour_actuel];
    printf("\n--- Tour de %s ---\n", joueur->nom);

    afficher_plateau(jeu);

    int choix;
    do {
        printf("Voulez-vous piocher (1) ou prendre une défausse (2) ? ");
        choix = demander_entier_secure("", 1, 2);
    } while (choix != 1 && choix != 2);

    Carte nouvelle;

    if (choix == 1) {
        if (jeu->nb_pioche == 0) {
            printf("La pioche est vide ! Vous ne pouvez pas piocher.\n");
            return;
        } else {
            nouvelle = jeu->pioche[--jeu->nb_pioche];
            nouvelle.visible = 1;
            printf("Vous avez pioché : \n");
            afficher_cartes_en_ligne(&nouvelle, 1, NULL);
        }
    } else {
        printf("Choisissez la défausse d'un joueur (1 à %d) : ", jeu->nb_joueurs);
        int cible = demander_entier_secure("", 1, jeu->nb_joueurs) - 1;

        if (jeu->joueurs[cible].nb_defausse > 0) {
            nouvelle = jeu->joueurs[cible].defausse[jeu->joueurs[cible].nb_defausse - 1];
            jeu->joueurs[cible].nb_defausse--;
        } else {
            printf("Défausse vide.");
            if (jeu->nb_pioche == 0) {
                printf(" Et la pioche est aussi vide. Aucun échange possible ce tour.\n");
                return;
            }
            nouvelle = jeu->pioche[--jeu->nb_pioche];
            nouvelle.visible = 1;
            printf(" Pioche par défaut : ");
            afficher_cartes_en_ligne(&nouvelle, 1, NULL);
        }
    }

    printf("Quelle carte échanger ? (1 à %d) : ", joueur->nb_cartes);
    int index = demander_entier_secure("", 1, joueur->nb_cartes) - 1;

    Carte ancienne = joueur->cartes[index];
    joueur->cartes[index] = nouvelle;
    joueur->cartes[index].visible = 1;

    if (joueur->nb_defausse < MAX_DEFAUSSE) {
        joueur->defausse[joueur->nb_defausse++] = ancienne;
    } else {
        printf("Erreur : la défausse est pleine !\n");
    }

    jeu->tour_actuel = (jeu->tour_actuel + 1) % jeu->nb_joueurs;
}

// Vérifie si un joueur a terminé et que toutes ses cartes sont visibles
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

// Calcule les scores en fin de partie
void calculer_scores(const Jeu* jeu, int* scores) {
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        scores[i] = 0;
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; j++) {
            scores[i] += jeu->joueurs[i].cartes[j].valeur;
        }
    }
}

// Libération de la mémoire
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
