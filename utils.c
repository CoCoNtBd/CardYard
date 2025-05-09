#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// efface tampon d'entrée
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Saisie sécurisée d'un entier
int demander_entier(const char* message, int min, int max) {
    int val;
    do {
        printf("%s (%d-%d) : ", message, min, max);
        int result = scanf("%d", &val);
        if (result != 1) {
            printf("Entrée invalide. Veuillez saisir un entier.\n");
            vider_buffer();
            continue;
        }
        vider_buffer();
    } while (val < min || val > max);
    return val;
}

// Saisie sécurisée d'un entier (version sécurisée globale)
int demander_entier_secure(const char* message, int min, int max) {
    int val, result;
    do {
        printf("%s (%d-%d) : ", message, min, max);
        result = scanf("%d", &val);
        while (getchar() != '\n'); // Vider le buffer
        if (result != 1 || val < min || val > max) {
            printf("Entrée invalide. Veuillez recommencer.\n");
        }
    } while (result != 1 || val < min || val > max);
    return val;
}

// Saisie sécurisée d'une chaîne de caractères
void demander_chaine(const char* message, char* buffer, int taille_max) {
    printf("%s : ", message);
    fgets(buffer, taille_max, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // supprime le \n
}
