#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#include "game.h"
#include "player.h"
#include "cards.h"

int sauvegarder_jeu(const Jeu* jeu, const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "w");
    if (!f) return 0;
    fprintf(f, "%d %d\n", jeu->nb_joueurs, jeu->nb_pioche);
    for (int i = 0; i < jeu->nb_pioche; ++i)
        fprintf(f, "%d %d\n", jeu->pioche[i].valeur, jeu->pioche[i].visible);
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* j = &jeu->joueurs[i];
        fprintf(f, "%s %d %d\n", j->nom, j->nb_cartes, j->nb_defausse);
        for (int k = 0; k < j->nb_cartes; ++k)
            fprintf(f, "%d %d\n", j->cartes[k].valeur, j->cartes[k].visible);
        for (int k = 0; k < j->nb_defausse; ++k)
            fprintf(f, "%d %d\n", j->defausse[k].valeur, j->defausse[k].visible);
    }
    fprintf(f, "%d\n", jeu->tour_actuel);
    fclose(f);
    return 1;
}

int charger_jeu(Jeu* jeu, const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "r");
    if (!f) return 0;

    fscanf(f, "%d %d", &jeu->nb_joueurs, &jeu->nb_pioche);
    jeu->pioche = malloc(jeu->nb_pioche * sizeof(Carte));
    for (int i = 0; i < jeu->nb_pioche; ++i)
        fscanf(f, "%d %d", &jeu->pioche[i].valeur, &jeu->pioche[i].visible);
    jeu->joueurs = malloc(jeu->nb_joueurs * sizeof(Joueur));
    for (int i = 0; i < jeu->nb_joueurs; ++i) {
        Joueur* j = &jeu->joueurs[i];
        fscanf(f, "%s %d %d", j->nom, &j->nb_cartes, &j->nb_defausse);
        j->cartes = malloc(j->nb_cartes * sizeof(Carte));
        for (int k = 0; k < j->nb_cartes; ++k)
            fscanf(f, "%d %d", &j->cartes[k].valeur, &j->cartes[k].visible);
        j->defausse = malloc(j->nb_defausse * sizeof(Carte));
        for (int k = 0; k < j->nb_defausse; ++k)
            fscanf(f, "%d %d", &j->defausse[k].valeur, &j->defausse[k].visible);
    }
    fscanf(f, "%d", &jeu->tour_actuel);
    jeu->jeu_termine = 0;
    jeu->tours_restants = -1;
    fclose(f);
    return 1;
}
