#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "player.h"
#include "cards.h"

// Affiche une carte individuelle
void afficher_carte(const Carte* carte);

// Affiche tout le plateau de jeu (joueurs + cartes + défausse + pioche)
void afficher_plateau(const Jeu* jeu);

// Affiche les scores de fin de partie
void afficher_scores(const Jeu* jeu, const int* scores);

#endif
