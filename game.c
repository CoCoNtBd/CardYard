#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "cards.h"
#include "display.h"
#include "utils.h"

// Initialise le jeu : pioche, joueurs, distribution
void initialiser_jeu(Jeu* jeu, int nb_joueurs, int nb_cartes) {
    jeu->nb_joueurs = nb_joueurs;
    jeu->tour_actuel = 0;
    jeu->jeu_termine = 0;

    jeu->pioche = generer_pioche_defaut(&jeu->nb_pioche);
    melanger_pioche(jeu->pioche, jeu->nb_pioche);

    jeu->joueurs = malloc(nb_joueurs * sizeof(Joueur));
    for (int i = 0; i < nb_joueurs; ++i) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%s", jeu->joueurs[i].nom);
        initialiser_joueur(&jeu->joueurs[i], nb_cartes);
    }

    distribuer_cartes(jeu);
}

// Distribution des cartes face cachée
void distribuer_cartes(Jeu* jeu) {
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; ++j) {
            jeu->joueurs[i].cartes[j] = jeu->pioche[--jeu->nb_pioche];
            jeu->joueurs[i].cartes[j].visible = 0;
        }
    }
}

// Effectue un tour de jeu
void jouer_tour(Jeu* jeu) {
    Joueur* joueur = &jeu->joueurs[jeu->tour_actuel];
    printf("\n--- Tour de %s ---\n", joueur->nom);

    afficher_plateau(jeu);

    printf("Voulez-vous piocher (1) ou prendre une defausse (2) ? ");
    int choix;
    scanf("%d", &choix);

    Carte nouvelle;
    if (choix == 1) {
        nouvelle = jeu->pioche[--jeu->nb_pioche];
        nouvelle.visible = 1;
        printf("Vous avez pioché : ");
        afficher_carte(&nouvelle);
        printf("\n");
    } else {
        printf("Choisissez la defausse d'un joueur (0-%d) : ", jeu->nb_joueurs - 1);
        int cible;
        scanf("%d", &cible);
        if (jeu->joueurs[cible].nb_defausse > 0) {
            nouvelle = jeu->joueurs[cible].defausse[jeu->joueurs[cible].nb_defausse - 1];
            jeu->joueurs[cible].nb_defausse--;
        } else {
            printf("Defausse vide, pioche par défaut.\n");
            nouvelle = jeu->pioche[--jeu->nb_pioche];
        }
    }

    printf("Quelle carte échanger ? (0-%d) : ", joueur->nb_cartes - 1);
    int index;
    scanf("%d", &index);
    Carte ancienne = joueur->cartes[index];
    joueur->cartes[index] = nouvelle;
    joueur->cartes[index].visible = 1;

    joueur->defausse = realloc(joueur->defausse, sizeof(Carte) * (joueur->nb_defausse + 1));
    joueur->defausse[joueur->nb_defausse++] = ancienne;

    // Tour suivant
    jeu->tour_actuel = (jeu->tour_actuel + 1) % jeu->nb_joueurs;
}

// Vérifie si un joueur a terminé (toutes cartes visibles)
int verifier_fin_partie(Jeu* jeu) {
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        if (toutes_cartes_visibles(&jeu->joueurs[i])) {
            jeu->jeu_termine = 1;
            return 1;
        }
    }
    return 0;
}

// Calcule les scores en fin de partie
void calculer_scores(const Jeu* jeu, int* scores) {
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        scores[i] = 0;
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; ++j) {
            scores[i] += jeu->joueurs[i].cartes[j].valeur;
        }
    }
}
