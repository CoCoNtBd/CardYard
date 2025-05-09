#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "player.h"
#include "cards.h"

// Affiche une ligne horizontale de cartes, ainsi que la carte du dessus de la défausse (si présente)
// - cartes     : tableau de cartes personnelles d'un joueur
// - nb_cartes  : nombre de cartes personnelles
// - defausse   : pointeur vers la dernière carte de la défausse (ou NULL)
void afficher_cartes_en_ligne(const Carte* cartes, int nb_cartes, const Carte* defausse);

// Affiche l'état complet du plateau de jeu
// - Montre les cartes de chaque joueur, leur défausse, et la pioche centrale
void afficher_plateau(const Jeu* jeu);

// Affiche les scores des joueurs à la fin de la partie
// - scores : tableau d'entiers correspondant aux scores de chaque joueur
void afficher_scores(const Jeu* jeu, const int* scores);

#endif

