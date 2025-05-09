#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Vide le tampon d'entrée pour éviter que des caractères résiduels perturbent les saisies suivantes
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Consomme tous les caractères jusqu'à la fin de ligne
}

// Demande à l'utilisateur un entier dans un intervalle donné [min, max]
// Affiche un message et recommence en cas d'erreur
int demander_entier(const char* message, int min, int max) {
    int val;
    do {
        printf("%s (%d-%d) : ", message, min, max);  // Message personnalisé
        int result = scanf("%d", &val);
        if (result != 1) {
            printf("Entrée invalide. Veuillez saisir un entier.\n");
            vider_buffer(); // Nettoyage du buffer si l'utilisateur a tapé autre chose qu'un entier
            continue;
        }
        vider_buffer(); // Nettoie même après une saisie correcte
    } while (val < min || val > max); // Tant que la valeur n'est pas dans les bornes
    return val;
}

// Variante plus robuste pour la saisie d'entiers, utilisée dans tout le projet
int demander_entier_secure(const char* message, int min, int max) {
    int val, result;
    do {
        printf("%s (%d-%d) : ", message, min, max);
        result = scanf("%d", &val);
        while (getchar() != '\n'); // Consomme tout le reste de la ligne (nettoyage)
        if (result != 1 || val < min || val > max) {
            printf("Entrée invalide. Veuillez recommencer.\n");
        }
    } while (result != 1 || val < min || val > max);
    return val;
}

// Demande à l'utilisateur une chaîne de caractères avec gestion de la taille maximale
void demander_chaine(const char* message, char* buffer, int taille_max) {
    printf("%s : ", message);
    fgets(buffer, taille_max, stdin);                      // Lecture sécurisée
    buffer[strcspn(buffer, "\n")] = '\0';                  // Remplace le \n final par \0 pour éviter les bugs
}
