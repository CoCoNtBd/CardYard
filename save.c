#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#include "game.h"
#include "player.h"
#include "cards.h"

// Sauvegarde l'état actuel du jeu dans un fichier texte
// Retourne 1 si succès, 0 si erreur (ex : fichier non ouvert)
int sauvegarder_jeu(const Jeu* jeu, const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "w");  // Ouvre le fichier en écriture
    if (!f) return 0;                   // Échec ouverture = erreur

    // Écrit le nombre de joueurs et le nombre de cartes restantes dans la pioche
    fprintf(f, "%d %d\n", jeu->nb_joueurs, jeu->nb_pioche);

    // Sauvegarde toutes les cartes restantes dans la pioche
    for (int i = 0; i < jeu->nb_pioche; ++i)
        fprintf(f, "%d %d\n", jeu->pioche[i].valeur, jeu->pioche[i].visible);

    // Sauvegarde les données de chaque joueur
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* j = &jeu->joueurs[i];

        // Nom, nombre de cartes en main et nombre de cartes en défausse
        fprintf(f, "%s %d %d\n", j->nom, j->nb_cartes, j->nb_defausse);

        // Cartes personnelles
        for (int k = 0; k < j->nb_cartes; ++k)
            fprintf(f, "%d %d\n", j->cartes[k].valeur, j->cartes[k].visible);

        // Cartes en défausse
        for (int k = 0; k < j->nb_defausse; ++k)
            fprintf(f, "%d %d\n", j->defausse[k].valeur, j->defausse[k].visible);
    }

    // Sauvegarde du joueur dont c'est le tour
    fprintf(f, "%d\n", jeu->tour_actuel);

    fclose(f); // Ferme le fichier
    return 1;  // Sauvegarde réussie
}

// Charge l'état d'une partie à partir d'un fichier texte
// Retourne 1 si succès, 0 si échec
int charger_jeu(Jeu* jeu, const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "r");  // Ouvre le fichier en lecture
    if (!f) return 0;                   // Échec d'ouverture

    // Récupère le nombre de joueurs et la taille de la pioche
    fscanf(f, "%d %d", &jeu->nb_joueurs, &jeu->nb_pioche);

    // Allocation de la pioche et chargement des cartes
    jeu->pioche = malloc(jeu->nb_pioche * sizeof(Carte));
    for (int i = 0; i < jeu->nb_pioche; ++i)
        fscanf(f, "%d %d", &jeu->pioche[i].valeur, &jeu->pioche[i].visible);

    // Allocation des joueurs
    jeu->joueurs = malloc(jeu->nb_joueurs * sizeof(Joueur));
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* j = &jeu->joueurs[i];

        // Lecture du nom, du nombre de cartes et de la taille de la défausse
        fscanf(f, "%s %d %d", j->nom, &j->nb_cartes, &j->nb_defausse);

        // Allocation et chargement des cartes personnelles
        j->cartes = malloc(j->nb_cartes * sizeof(Carte));
        for (int k = 0; k < j->nb_cartes; ++k)
            fscanf(f, "%d %d", &j->cartes[k].valeur, &j->cartes[k].visible);

        // Allocation et chargement des cartes en défausse
        j->defausse = malloc(j->nb_defausse * sizeof(Carte));
        for (int k = 0; k < j->nb_defausse; ++k)
            fscanf(f, "%d %d", &j->defausse[k].valeur, &j->defausse[k].visible);
    }

    // Récupère le joueur courant (tour en cours)
    fscanf(f, "%d", &jeu->tour_actuel);

    // Réinitialise les indicateurs de fin de partie
    jeu->jeu_termine = 0;
    jeu->tours_restants = -1;

    fclose(f); // Ferme le fichier
    return 1;  // Chargement réussi
}
