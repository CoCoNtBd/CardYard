#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

void clearScreen();
void pauseScreen();
int getRandomInt(int min, int max);

typedef enum {
    MODE_STANDARD,
    MODE_VALUE_FILE,
    MODE_VALUE_USER,
    MODE_CARD_USER,
    MODE_CARD_RAND
} GameMode;

int* loadValuesFromFile(const char* filename, int* totalCards);
int* getUserDefinedValues(int* totalCards);

int getCustomCardCount();
int getRandomCardCount(int min, int max);

void applyGameModeSettings(GameMode mode);

#endif
