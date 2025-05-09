#ifndef UTILS_H
#define UTILS_H

// Vide le buffer de saisie standard (stdin)
// Utile après un scanf pour éviter que des caractères résiduels restent dans le flux d'entrée
void vider_buffer();

// Demande à l'utilisateur de saisir un entier dans un intervalle [min, max]
// Affiche le message donné en paramètre
// Repose sur scanf et vide ensuite le buffer
int demander_entier(const char* message, int min, int max);

// Variante plus sécurisée de demander_entier
// Gère les erreurs de saisie plus proprement
// Recommandée pour une utilisation dans des boucles ou des menus
int demander_entier_secure(const char* message, int min, int max);

// Demande à l'utilisateur de saisir une chaîne de caractères (ex : nom)
// Stocke la chaîne saisie dans `buffer`, avec taille maximale `taille_max`
// Utilise fgets pour éviter les dépassements de tampon
void demander_chaine(const char* message, char* buffer, int taille_max);

#endif
