#ifndef GAME_H
#define GAME_H

#include "cards.h"
#include "player.h"

// structure principal du jeu
typedef struct {
    Carte* pioche;         // Pioche centrale
    int nb_pioche;

    Joueur* joueurs;       // Tableau de joueurs
    int nb_joueurs;

    int tour_actuel;       // Index du joueur dont c’est le tour
    int jeu_termine;  // Booléen : 1 si le jeu est fini
    
    int tours_restants;
} Jeu;


// Initialise la partie
void initialiser_jeu(Jeu* jeu, int nb_joueurs, int nb_cartes_par_joueur);

// Distribue les cartes de la pioche à chaque joueur
void distribuer_cartes(Jeu* jeu);

// Joue un tour complet pour le joueur courant
void jouer_tour(Jeu* jeu);

// Vérifie si la partie est terminée (un joueur a toutes ses cartes visibles)
int verifier_fin_partie(Jeu* jeu);

// Calcule les scores finaux et les stocke dans un tableau externe
void calculer_scores(const Jeu* jeu, int* scores);

//liberation de la memoire pour evité les crash
void liberer_jeu(Jeu* jeu);


#endif
