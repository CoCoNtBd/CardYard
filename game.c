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
    jeu->tours_restants = -1; // -1 = aucun joueur n'a encore révélé toutes ses cartes
    jeu->jeu_termine = 0;
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

void jouer_tour(Jeu* jeu) {
    Joueur* joueur = &jeu->joueurs[jeu->tour_actuel];
    printf("\n--- Tour de %s ---\n", joueur->nom);
    afficher_plateau(jeu);
    printf("Voulez-vous piocher (1) ou prendre une défausse (2) ? ");
    int choix;
    scanf("%d", &choix);
    vider_buffer();
    Carte nouvelle;
    if (choix == 1) {
        if (jeu->nb_pioche == 0) {
            printf("La pioche est vide ! Vous ne pouvez pas piocher.\n");
            return;
        } else {
            nouvelle = jeu->pioche[--jeu->nb_pioche];
            nouvelle.visible = 1;
            printf("Vous avez pioché : ");
            afficher_carte(&nouvelle);
            printf("\n");
        }
    } else {
        printf("Choisissez la défausse d'un joueur (1 à %d) : ", jeu->nb_joueurs);
        int cible;
        scanf("%d", &cible);
        vider_buffer();
        cible -= 1;  // Convertir le numéro saisi (1 à N) en index (0 à N-1)
        if (cible < 0 || cible >= jeu->nb_joueurs) {
            printf("Numéro de joueur invalide.\n");
            return;
        }
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
            afficher_carte(&nouvelle);
            printf("\n");
        }
    }
    printf("Quelle carte échanger ? (1 à %d) : ", joueur->nb_cartes);
    int index;
    scanf("%d", &index);
    vider_buffer();
    index -= 1;
    if (index < 0 || index >= joueur->nb_cartes) {
        printf("Index de carte invalide.\n");
        return;
    }
    Carte ancienne = joueur->cartes[index];
    joueur->cartes[index] = nouvelle;
    joueur->cartes[index].visible = 1;
    Carte* temp = realloc(joueur->defausse, sizeof(Carte) * (joueur->nb_defausse + 1));
    if (temp != NULL) {
        joueur->defausse = temp;
        joueur->defausse[joueur->nb_defausse++] = ancienne;
    } else {
        printf("Erreur mémoire lors de la défausse.\n");
    }
    jeu->tour_actuel = (jeu->tour_actuel + 1) % jeu->nb_joueurs;
}


// Vérifie si un joueur a terminé (toutes cartes visibles)
int verifier_fin_partie(Jeu* jeu) {
    if (jeu->tours_restants != -1)
        return 0; // Le dernier tour a déjà été déclenché
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
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
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        scores[i] = 0;
        for (int j = 0; j < jeu->joueurs[i].nb_cartes; ++j) {
            scores[i] += jeu->joueurs[i].cartes[j].valeur;
        }
    }
}
