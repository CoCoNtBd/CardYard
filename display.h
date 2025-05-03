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

// (Facultatif mais utile pour debug ou affichage individuel)
void afficher_joueur(const Joueur* joueur);
void afficher_defausse(const Carte* defausse, int taille);
void afficher_pioche(const Carte* pioche, int taille);

#endif
