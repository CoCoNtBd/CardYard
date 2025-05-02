// player.h
#pragma once 

typedef struct {
    int value;
    int is_visible; // 0 = cachée, 1 = visible
} Card;

typedef struct {
    char name[20];
    Card* personal_cards;    
    Card* discard_pile;      
    int num_personal_cards;  
    int discard_count;       
    int discard_capacity;    
} Player;

void init_player(Player* p, const char* name, int n_cards);
void cleanup_player(Player* p);
int swap_card(Player* p, int card_index, Card new_card);
