#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 1. Initialisation (Allocation Mémoire)

void init_player(Player* p, const char* name, int n_cards) {
    // Copie du nom
    strncpy(p->name, name, 19);
    p->name[19] = '\0';

    // Allocation des cartes personnelles
    p->personal_cards = malloc(n_cards * sizeof(Card));
    if (!p->personal_cards) {
        printf("Erreur mémoire !\n");
        exit(1);
    }

    // Initialisation à zéro
    for (int i = 0; i < n_cards; i++) {
        p->personal_cards[i].value = 0;
        p->personal_cards[i].is_visible = 0;
    }
    p->num_personal_cards = n_cards;

    // Allocation défausse (capacité initiale : 10 cartes)
    p->discard_capacity = 10;
    p->discard_pile = malloc(p->discard_capacity * sizeof(Card));
    if (!p->discard_pile) {
        free(p->personal_cards); // Nettoyage partiel
        printf("Erreur mémoire !\n");
        exit(1);
    }
    p->discard_count = 0;
}


// 2. Nettoyage (Libération Mémoire)

void cleanup_player(Player* p) {
    free(p->personal_cards);  // Libère les cartes perso
    free(p->discard_pile);    // Libère la défausse
    // On remet tout à zéro par sécurité
    p->personal_cards = NULL;
    p->discard_pile = NULL;
    p->num_personal_cards = 0;
    p->discard_count = 0;
}


// 3. Échange de carte (Gestion dynamique de la défausse)
-
int swap_card(Player* p, int card_index, Card new_card) {
    // Vérification de l'indice
    if (card_index < 0 || card_index >= p->num_personal_cards) {
        printf("Mauvaise carte !\n");
        return -1;
    }

    // Récupère l'ancienne carte
    Card old_card = p->personal_cards[card_index];

    // Vérifie si la défausse est pleine
    if (p->discard_count >= p->discard_capacity) {
        printf("Défausse pleine !\n");
        return -1;
    }

    // Ajoute à la défausse (face visible)
    old_card.is_visible = 1;
    p->discard_pile[p->discard_count] = old_card;
    p->discard_count++;

    // Met la nouvelle carte (face visible)
    new_card.is_visible = 1;
    p->personal_cards[card_index] = new_card;

    printf("[%s] Échange réussi !\n", p->name);
    return 0;
}
