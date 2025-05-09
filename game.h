#ifndef GAME_H
#define GAME_H

#include "cards.h"
#include "player.h"

// Structure principale représentant l'état d'une partie
typedef struct {
    Carte* pioche;       // Pioche centrale du jeu (tableau dynamique)
    int nb_pioche;       // Nombre de cartes restantes dans la pioche

    Joueur* joueurs;     // Tableau dynamique des joueurs
    int nb_joueurs;      // Nombre de joueurs dans la partie

    int tour_actuel;     // Index du joueur dont c’est le tour (0 à nb_joueurs - 1)
    int jeu_termine;     // Booléen : 1 si la partie est terminée, 0 sinon

    int tours_restants;  // Déclenché à -1 (non actif), puis décrémenté à la fin
                         // quand un joueur a révélé toutes ses cartes
} Jeu;

// Initialise la partie (pioche, mélange, joueurs, distribution des cartes)
void initialiser_jeu(Jeu* jeu, int nb_joueurs, int nb_cartes_par_joueur);

// Distribue les cartes de la pioche à chaque joueur (face cachée)
void distribuer_cartes(Jeu* jeu);

// Exécute un tour de jeu pour le joueur courant
void jouer_tour(Jeu* jeu);

// Vérifie si un joueur a terminé (toutes ses cartes sont visibles)
// Déclenche les tours restants pour les autres joueurs
int verifier_fin_partie(Jeu* jeu);

// Calcule le score de chaque joueur en sommant les valeurs de ses cartes
void calculer_scores(const Jeu* jeu, int* scores);

// Libère toute la mémoire dynamique utilisée par la partie
void liberer_jeu(Jeu* jeu);

#endif
