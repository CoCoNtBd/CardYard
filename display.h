
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "player.h"
#include "cards.h"

void afficher_carte(const Carte* carte);
void afficher_plateau(const Jeu* jeu);
void afficher_scores(const Jeu* jeu, const int* scores);

#endif
