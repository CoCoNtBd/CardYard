#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "utils.h"

// Crée une carte avec une valeur donnée et un état de visibilité
Carte creer_carte(int valeur, int visible) {
    Carte c;
    c.valeur = valeur;   // valeur numérique de la carte (ex: -2, 0, 5...)
    c.visible = visible; // 0 = face cachée, 1 = face visible
    return c;
}

// Mélange la pioche de cartes avec un algorithme de Fisher–Yates
void melanger_pioche(Carte* pioche, int taille) {
    srand(time(NULL)); // Initialise la graine aléatoire avec l'heure actuelle
    for (int i = 0; i < taille - 1; i++) {
        int j = i + rand() % (taille - i); // Choisit un index aléatoire dans [i, taille[
        Carte temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;
    }
}

// Génère la pioche par défaut avec les valeurs et quantités fixées
Carte* generer_pioche_defaut(int* taille_pioche) {
    int valeurs[]   = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int quantites[] = { 5, 10,15,10,10,10,10,10,10,10,10,10,10,10,10};

    int total = 0;
    // Calcule le nombre total de cartes à allouer
    for (int i = 0; i < 15; i++) {
        total += quantites[i];
    }

    Carte* pioche = malloc(total * sizeof(Carte)); // Allocation dynamique
    int index = 0;

    // Remplit la pioche avec les cartes définies
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < quantites[i]; j++) {
            pioche[index++] = creer_carte(valeurs[i], 0); // Toutes cartes face cachée au départ
        }
    }

    *taille_pioche = total;
    return pioche;
}

// Génère une pioche personnalisée selon l'utilisateur
Carte* generer_pioche_personnalisee(int* taille_pioche) {
    int choix;
    do {
        printf("Choisissez une méthode pour définir les cartes :\n");
        printf("1. Même quantité pour chaque valeur\n");
        printf("2. Quantité personnalisée pour chaque valeur\n");
        choix = demander_entier_secure("Méthode", 1, 2); // Entrée sécurisée
    } while (choix < 1 || choix > 2);

    int valeurs[31];     // [-10 à 20] => 31 valeurs possibles
    int quantites[31];   // Quantité de chaque valeur
    int total = 0;

    // Remplit le tableau de valeurs et demande les quantités
    for (int i = 0; i <= 30; i++) {
        valeurs[i] = i - 10; // Décale pour avoir des valeurs de -10 à 20
        if (choix == 1) {
            quantites[i] = 5; // Quantité fixe
        } else {
            printf("Combien de cartes pour la valeur %d : ", valeurs[i]);
            quantites[i] = demander_entier_secure("", 0, 50); // Quantité personnalisée
        }
        total += quantites[i]; // Compte total de cartes à créer
    }

    Carte* pioche = malloc(total * sizeof(Carte)); // Allocation de la pioche
    int index = 0;

    // Remplissage de la pioche avec les valeurs et quantités choisies
    for (int i = 0; i <= 30; i++) {
        for (int j = 0; j < quantites[i]; j++) {
            pioche[index++] = creer_carte(valeurs[i], 0); // Toutes cartes face cachée
        }
    }

    *taille_pioche = total;
    return pioche;
}

