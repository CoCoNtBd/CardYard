#ifndef SAVE_H
#define SAVE_H

#include "game.h"

// Sauvegarde l'état complet d'une partie dans un fichier texte
// - jeu : pointeur vers la structure Jeu à sauvegarder
// - nom_fichier : nom du fichier où enregistrer
// Retourne 1 si la sauvegarde a réussi, 0 sinon (ex : problème d'ouverture de fichier)
int sauvegarder_jeu(const Jeu* jeu, const char* nom_fichier);

// Charge l'état d'une partie depuis un fichier texte
// - jeu : pointeur vers la structure Jeu à remplir
// - nom_fichier : nom du fichier à lire
// Retourne 1 si le chargement a réussi, 0 sinon (ex : fichier introuvable)
int charger_jeu(Jeu* jeu, const char* nom_fichier);

#endif
