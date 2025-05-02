#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int* loadValuesFromFile(const char* filename, int* totalCards) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        errorHandler(2); 
        return NULL;
    }

    int* values = malloc(100 * sizeof(int)); 
    int capacity = 100;
    *totalCards = 0;

    int value, count;
    while (fscanf(file, "%d:%d", &value, &count) == 2) {
        if (*totalCards + count > capacity) {
            capacity *= 2;
            values = realloc(values, capacity * sizeof(int));
        }
        for (int i = 0; i < count; i++) {
            values[(*totalCards)++] = value;
        }
    }

    fclose(file);
    return values;
}

int* getUserDefinedValues(int* totalCards) {
    printf("Entrez les valeurs (format 'valeur:quantité'), terminez par 'fin':\n");
    
    int* values = malloc(50 * sizeof(int));
    *totalCards = 0;
    char input[50];

    while (1) {
        printf("> ");
        fgets(input, 50, stdin);
        
        if (strcmp(input, "fin\n") == 0) break;

        int value, count;
        if (sscanf(input, "%d:%d", &value, &count) == 2) {
            values = realloc(values, (*totalCards + count) * sizeof(int));
            for (int i = 0; i < count; i++) {
                values[(*totalCards)++] = value;
            }
        }
    }

    return values;
}

int getCustomCardCount() {
    return getValidatedInput("Nombre de cartes par joueur (4-12)", 4, 12);
}

int getRandomCardCount(int min, int max) {
    printf("Génération aléatoire du nombre de cartes...\n");
    return getRandomInt(min, max);
}

    switch (mode) {
        case MODE_VALUE_FILE: {
            int totalCards;
            int* values = loadValuesFromFile("config.txt", &totalCards);
            break;
        }
        case MODE_CARD_RAND:
            int cardCount = getRandomCardCount(4, 10);
            break;

    }
}
