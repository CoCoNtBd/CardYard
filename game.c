#include "game.h"
#include "player.h"
#include "cards.h"
#include "display.h"
#include "save.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// 1. Initialisation du jeu


/**
 * Initialise l'état complet du jeu
 * Pointeur vers la structure GameState
 * Nombre de joueurs (2-8)
*/
void init_game(GameState* game, int n_players) {
    // Initialisation aléatoire
    srand(time(NULL));
    
    // Configuration de base
    game->total_players = n_players;
    game->current_player = 0;
    game->game_over = false;
    
    // 1. Création des joueurs
    game->players = (Player*)malloc(n_players * sizeof(Player));
    if(!game->players) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < n_players; i++) {
        char name[20];
        snprintf(name, 20, "Joueur %d", i+1);
        init_player(&game->players[i], name);
    }
    
    // 2. Préparation de la pioche centrale
    init_deck(&game->central_pile);
    generate_initial_cards(&game->central_pile); // Valeurs par défaut (-2 à +12)
    shuffle_deck(&game->central_pile);
    
    // 3. Distribution des cartes personnelles
    const int cards_per_player = 6; // Peut être modifié pour les variantes
    for(int p = 0; p < n_players; p++) {
        for(int c = 0; c < cards_per_player; c++) {
            Card drawn = draw_card(&game->central_pile);
            add_personal_card(&game->players[p], drawn);
        }
    }
}


// 2. Logique principale du jeu


/**
 * Exécute la boucle principale du jeu
*/
void run_game_loop(GameState* game) {
    while(!game->game_over) {
        Player* current = &game->players[game->current_player];
        
        // Affichage de l'état du jeu
        clear_screen();
        show_game_state(game);
        
        // Tour du joueur
        handle_player_turn(current, game);
        
        // Vérification fin de partie
        check_game_end_condition(game);
        
        // Passage au joueur suivant
        game->current_player = (game->current_player + 1) % game->total_players;
    }
    
    // Affichage des scores finaux
    calculate_final_scores(game);
    show_leaderboard(game);
}


// 3. Gestion d'un tour de joueur


/**
 * Gère toutes les actions possibles pendant un tour
*/
void handle_player_turn(Player* player, GameState* game) {
    int choice;
    bool valid_action = false;
    
    while(!valid_action) {
        printf("\n%s, c'est votre tour!\n", player->name);
        printf("1. Piocher carte centrale\n");
        printf("2. Prendre carte défausse\n");
        printf("3. Sauvegarder et quitter\n");
        printf("Choix : ");
        
        choice = get_int_input(1, 3);
        
        switch(choice) {
            case 1: // Pioche centrale
                valid_action = handle_central_pile(player, game);
                break;
                
            case 2: // Défausse
                valid_action = handle_discard_pile(player, game);
                break;
                
            case 3: // Sauvegarde
                save_game(game, "sauvegarde.txt");
                printf("Partie sauvegardée!\n");
                exit(0);
                
            default:
                printf("Choix invalide!\n");
        }
    }
}


// 4. Actions de jeu


/**
 * Gère la pioche centrale
 * return true si action valide effectuée
*/
bool handle_central_pile(Player* player, GameState* game) {
    if(is_deck_empty(&game->central_pile)) {
        printf("La pioche est vide!\n");
        return false;
    }
    
    Card drawn = draw_card(&game->central_pile);
    printf("Carte piochée : ");
    print_card(drawn);
    
    return process_card_swap(player, drawn);
}

/**
 * Gère les défausses
 * return true si action valide effectuée
*/
bool handle_discard_pile(Player* player, GameState* game) {
    int target_player;
    
    printf("Choisir un joueur (1-%d) : ", game->total_players);
    target_player = get_int_input(1, game->total_players) - 1;
    
    Player* target = &game->players[target_player];
    
    if(target->discard_count == 0) {
        printf("Défausse vide!\n");
        return false;
    }
    
    Card taken = target->discard_pile[target->discard_count - 1];
    printf("Carte prise : ");
    print_card(taken);
    
    // Retire la carte de la défausse
    target->discard_count--;
    
    return process_card_swap(player, taken);
}

/**
 * Gère l'échange de carte générique
*/
bool process_card_swap(Player* player, Card new_card) {
    int card_index;
    
    printf("Choisir carte à remplacer (1-%d) : ", player->num_personal_cards);
    card_index = get_int_input(1, player->num_personal_cards) - 1;
    
    if(swap_card(player, card_index, new_card) == 0) {
        return true;
    }
    return false;
}


// 5. Fin de partie


/**
 * Vérifie si un joueur a toutes ses cartes visibles
*/
void check_game_end_condition(GameState* game) {
    for(int i = 0; i < game->total_players; i++) {
        if(has_finished(&game->players[i])) {
            game->game_over = true;
            printf("\n%s a terminé!\n", game->players[i].name);
        }
    }
}

/**
 * Calcule tous les scores finaux
*/
void calculate_final_scores(GameState* game) {
    for(int i = 0; i < game->total_players; i++) {
        game->players[i].score = calculate_score(&game->players[i]);
    }
}


// 6. Nettoyage


/**
 * Libère toute la mémoire allouée
*/
void cleanup_game(GameState* game) {
    for(int i = 0; i < game->total_players; i++) {
        cleanup_player(&game->players[i]);
    }
    free(game->players);
    free_deck(&game->central_pile);
}
