#ifndef SAVE_H
#define SAVE_H
#include "game.h"

// Sauvegarde l'état du jeu dans un fichier texte
// Retourne 1 si succès, 0 si échec
int sauvegarder_jeu(const Jeu* jeu, const char* nom_fichier);
// Charge l'état du jeu depuis un fichier texte
// Retourne 1 si succès, 0 si échec
int charger_jeu(Jeu* jeu, const char* nom_fichier);

#endif
