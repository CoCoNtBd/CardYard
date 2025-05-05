#ifndef UTILS_H
#define UTILS_H

// Vide le buffer de saisie standard (stdin)
void vider_buffer();
// Demande un entier à l'utilisateur entre min et max (inclus)
// Affiche un message d'invite
int demander_entier(const char* message, int min, int max);
// Demande une chaîne de caractères à l'utilisateur
// Le résultat est stocké dans `buffer` (de taille `taille_max`)
void demander_chaine(const char* message, char* buffer, int taille_max);

#endif
