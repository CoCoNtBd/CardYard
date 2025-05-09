#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "utils.h"

Carte creer_carte(int valeur, int visible) {
    Carte c;
    c.valeur = valeur;
    c.visible = visible;
    return c;
}

void melanger_pioche(Carte* pioche, int taille) {
    srand(time(NULL));
    for (int i = 0; i < taille - 1; i++) {
        int j = i + rand() % (taille - i);
        Carte temp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = temp;
    }
}

Carte* generer_pioche_defaut(int* taille_pioche) {
    int valeurs[]   = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int quantites[] = { 5, 10,15,10,10,10,10,10,10,10,10,10,10,10,10};

    int total = 0;
    for (int i = 0; i < 15; i++) {
        total += quantites[i];
    }

    Carte* pioche = malloc(total * sizeof(Carte));
    int index = 0;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < quantites[i]; j++) {
            pioche[index++] = creer_carte(valeurs[i], 0);
        }
    }

    *taille_pioche = total;
    return pioche;
}

Carte* generer_pioche_personnalisee(int* taille_pioche) {
    int choix;
    do {
        printf("Choisissez une méthode pour définir les cartes :\n");
        printf("1. Même quantité pour chaque valeur\n");
        printf("2. Quantité personnalisée pour chaque valeur\n");
        choix = demander_entier_secure("Méthode", 1, 2);
    } while (choix < 1 || choix > 2);

    int valeurs[31];
    int quantites[31];
    int total = 0;

    for (int i = 0; i <= 30; i++) {
        valeurs[i] = i - 10;
        if (choix == 1) {
            quantites[i] = 5;
        } else {
            // Utilisation d'un message fixe sans snprintf()
            printf("Combien de cartes pour la valeur %d : ", valeurs[i]);
            quantites[i] = demander_entier_secure("", 0, 50);
        }
        total += quantites[i];
    }

    Carte* pioche = malloc(total * sizeof(Carte));
    int index = 0;
    for (int i = 0; i <= 30; i++) {
        for (int j = 0; j < quantites[i]; j++) {
            pioche[index++] = creer_carte(valeurs[i], 0);
        }
    }

    *taille_pioche = total;
    return pioche;
}
