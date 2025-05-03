#ifndef CARDS_H
#define CARDS_H

typedef struct {
    int valeur;
    int visible; // 0 = face cachée, 1 = visible
} Carte;

// Création et manipulation de cartes
Carte creer_carte(int valeur, int visible);

// Mélange aléatoire d'une pioche
void melanger_pioche(Carte* pioche, int taille);

// Génération de la pioche selon les valeurs par défaut
Carte* generer_pioche_defaut(int* taille_pioche);

// (Facultatif, pour les variantes)
Carte* charger_valeurs_depuis_fichier(const char* chemin, int* taille_pioche);
Carte* demander_valeurs_utilisateur(int* taille_pioche);

#endif

