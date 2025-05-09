#ifndef CARDS_H
#define CARDS_H

// Structure représentant une carte du jeu
typedef struct {
    int valeur;    // Valeur numérique de la carte (ex : -2, 0, 5, 12)
    int visible;   // 0 = carte face cachée (dos), 1 = carte visible (face)
} Carte;

// Crée une carte avec une valeur donnée et un état (visible ou non)
Carte creer_carte(int valeur, int visible);

// Mélange les cartes de la pioche de façon aléatoire
void melanger_pioche(Carte* pioche, int taille);

// Génère la pioche de cartes avec les valeurs et quantités par défaut
Carte* generer_pioche_defaut(int* taille_pioche);

// Génère une pioche personnalisée selon les choix de l'utilisateur
Carte* generer_pioche_personnalisee(int* taille_pioche);

#endif
