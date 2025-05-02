// game.h
#pragma once

#include "player.h"
#include "cards.h"
#include "display.h"
#include "save.h"
#include "utils.h"
#include <stdbool.h>

typedef struct {
    Player* players;          // Tableau dynamique de joueurs
    Deck central_pile;        // Pioche centrale
    int current_player;       // Index du joueur actuel (0-based)
    int total_players;        // Nombre total de joueurs (2-8)
    bool game_over;           // État de fin de partie
} GameState;

// Initialisation/Destruction
void init_game(GameState* game, int n_players);  // Crée une nouvelle partie
void cleanup_game(GameState* game);              // Libère la mémoire

// Flux principal
void run_game_loop(GameState* game);             // Lance la boucle de jeu

// Gestion des tours
void handle_player_turn(Player* player, GameState* game); // Logique d'un tour

// Utilitaires
void calculate_final_scores(GameState* game);    // Calcule tous les scores finaux
bool check_game_end_condition(GameState* game);  // Vérifie si un joueur a gagné

// Sauvegarde
void save_current_game(const GameState* game);   // Sauvegarde l'état actuel
