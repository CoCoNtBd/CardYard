#include <stdio.h>
#include <string.h>
#include "display.h"

// Renvoie une couleur ANSI (code terminal) en fonction de la valeur de la carte
const char* couleur_par_valeur(int valeur) {
    if (valeur >= -10 && valeur < -5) return "\033[38;5;201m"; // violet
    if (valeur >= -5  && valeur < 0)  return "\033[38;5;196m"; // rouge
    if (valeur >= 0   && valeur <= 5) return "\033[38;5;208m"; // orange
    if (valeur > 5    && valeur <= 10)return "\033[38;5;226m"; // jaune
    if (valeur > 10   && valeur <= 15)return "\033[38;5;46m";  // vert
    if (valeur > 15   && valeur <= 20)return "\033[38;5;33m";  // bleu
    return "\033[38;5;240m"; // gris par défaut pour autres cas
}

// Affiche une ligne de cartes du joueur + la carte au sommet de la défausse (si présente)
void afficher_cartes_en_ligne(const Carte* cartes, int nb_cartes, const Carte* defausse) {
    // Chaque carte s'affiche en 5 lignes : bordures + contenu
    for (int ligne_index = 0; ligne_index < 5; ligne_index++) {

        // Affiche toutes les cartes personnelles du joueur
        for (int i = 0; i < nb_cartes; i++) {
            const Carte* c = &cartes[i];
            const char* couleur = c->visible ? couleur_par_valeur(c->valeur) : "";
            const char* reset = "\033[0m";

            if (!c->visible) {
                // Carte face cachée (design CARD YARD)
                switch (ligne_index) {
                    case 0: printf("╔══════╗ "); break;
                    case 1: printf("║ CARD ║ "); break;
                    case 2: printf("║~~~~~~║ "); break;
                    case 3: printf("║ YARD ║ "); break;
                    case 4: printf("╚══════╝ "); break;
                }
                continue;
            }

            // Carte visible avec couleur + valeur
            switch (ligne_index) {
                case 0: printf("%s╔══════╗%s ", couleur, reset); break;
                case 1: printf("%s║      ║%s ", couleur, reset); break;
                case 2: printf("%s║  %2d  ║%s ", couleur, c->valeur, reset); break;
                case 3: printf("%s║      ║%s ", couleur, reset); break;
                case 4: printf("%s╚══════╝%s ", couleur, reset); break;
            }
        }

        // Affiche la dernière carte de la défausse à droite, si elle existe
        if (defausse) {
            const Carte* c = defausse;
            const char* couleur = c->visible ? couleur_par_valeur(c->valeur) : "";
            const char* reset = "\033[0m";

            if (!c->visible) {
                // Défausse face cachée (rare si le jeu est bien codé)
                switch (ligne_index) {
                    case 0: printf("       ╔══════╗"); break;
                    case 1: printf("       ║ CARD ║"); break;
                    case 2: printf("       ║~~~~~~║"); break;
                    case 3: printf("       ║ YARD ║"); break;
                    case 4: printf("       ╚══════╝"); break;
                }
                printf("\n");
                continue;
            }

            // Défausse visible
            switch (ligne_index) {
                case 0: printf("       %s╔══════╗%s", couleur, reset); break;
                case 1: printf("       %s║      ║%s", couleur, reset); break;
                case 2: printf("       %s║  %2d  ║%s", couleur, c->valeur, reset); break;
                case 3: printf("       %s║      ║%s", couleur, reset); break;
                case 4: printf("       %s╚══════╝%s", couleur, reset); break;
            }
            printf("\n");
        } else {
            // Si pas de défausse, saut de ligne simple
            printf("\n");
        }
    }
}

// Affiche le plateau complet avec tous les joueurs et la pioche centrale
void afficher_plateau(const Jeu* jeu) {
    printf("\n======================================================= PLATEAU DE JEU =======================================================\n\n");

    for (int i = 0; i < jeu->nb_joueurs; i++) {
        Joueur* j = &jeu->joueurs[i];
        printf("%s\n", j->nom);
        // Récupère la dernière carte de la défausse si elle existe
        Carte* defausse = j->nb_defausse > 0 ? &j->defausse[j->nb_defausse - 1] : NULL;
        afficher_cartes_en_ligne(j->cartes, j->nb_cartes, defausse);
        printf("\n");
    }

    // Affichage de la pioche centrale (visuelle générique)
    printf("Pioche centrale :\n");
    Carte pioche_c = {0, 0}; // Carte fictive face cachée pour design
    afficher_cartes_en_ligne(&pioche_c, 1, NULL);

    printf("\n====================================================================================\n");
    printf("🔁 Tour de : %s (Joueur %d)\n", jeu->joueurs[jeu->tour_actuel].nom, jeu->tour_actuel + 1);
    printf("====================================================================================\n");
}

// Affiche les scores en fin de partie
void afficher_scores(const Jeu* jeu, const int* scores) {
    printf("\n--- Scores des joueurs ---\n");
    for (int i = 0; i < jeu->nb_joueurs; i++) {
        printf("%s : %d point%s\n", jeu->joueurs[i].nom, scores[i], scores[i] > 1 ? "s" : "");
    }
}
