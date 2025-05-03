#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

// Crée une carte avec valeur et visibilité données
Carte creer_carte(int valeur, int visible) {
    Carte c;
    c.valeur = valeur;
    c.visible = visible;
    return c;
}

// Mélange les cartes de la pioche
void melanger_pioche(Carte* pioche, int taille) {
    srand(time(NULL)); // Initialisation du générateur aléatoire
    for (int i = 0; i < taille - 1; ++i) {
        int j = i + rand() % (taille - i);
        Carte temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;
    }
}

// Génère la pioche avec les valeurs et quantités par défaut
Carte* generer_pioche_defaut(int* taille_pioche) {
    int valeurs[]   = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int quantites[] = { 5, 10,15,10,10,10,10,10,10,10,10,10,10,10,10};

    int total = 0;
    for (int i = 0; i < 15; ++i) total += quantites[i];

    Carte* pioche = malloc(total * sizeof(Carte));
    int index = 0;

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < quantites[i]; ++j) {
            pioche[index++] = creer_carte(valeurs[i], 0); // face cachée
        }
    }

    *taille_pioche = total;
    return pioche;
}

// Optionnel : à implémenter si variante VALUE_FILE
Carte* charger_valeurs_depuis_fichier(const char* chemin, int* taille_pioche) {
    // À écrire plus tard si tu veux charger depuis un fichier
    return NULL;
}

// Optionnel : à implémenter si variante VALUE_USER
Carte* demander_valeurs_utilisateur(int* taille_pioche) {
    // À écrire plus tard si tu veux demander les valeurs à l'utilisateur
    return NULL;
}
