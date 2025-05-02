#include <stdio.h>
#include "game.h"
#include "player.h"
#include "cards.h"

void afficher_plateau(const Jeu* jeu) {
  

  printf("\n============== PLATEAU DE JEU ==============\n");

  // nom des joueurs
  printf("JOUEURS :      ");
  for (int i = 0; i < jeu->nb_joueurs; i++) {
    printf("%s", jeu->joueurs[i].nom);
    }
    printf("\n");

  // cartes
  int nb_cartes = jeu->joueurs[0].nb_cartes; 

  for (int ligne = 0; ligne < nb_cartes; ligne++) {
    printf("Carte %d :      ", ligne + 1);
      for (int joueur = 0; joueur < jeu->nb_joueurs; joueur++) {
          Carte c = jeu->joueurs[joueur].cartes[ligne];
            if (c.visible)
                printf("[ %2d ]        ", c.valeur);
            else
                printf("[ ?? ]        ");
        }
        printf("\n");
    }

  // défausse
  printf("Défausse :     ");
  for (int i = 0; i < jeu->nb_joueurs; i++) {
    Joueur* j = &jeu->joueurs[i];
    if (j->nb_defausse > 0) {
        Carte top = j->defausse[j->nb_defausse - 1];
         printf("[ %2d ]        ", top.valeur);
    } else {
         printf("[    ]        ");
    }
    }
   printf("\n");

    // pioche
  printf("\nPioche : ");
  if (jeu->nb_pioche > 0) {
     printf("[ ? ] (%d cartes)\n", jeu->nb_pioche);
  } else {
       printf("[ Vide ]\n");
    }

  printf("Tour :  %d  Joueur : %s\n", jeu->tour_actuel + 1, jeu->joueurs[jeu->tour_actuel].nom);
  printf("============================================\n");
}

void afficher_joueur(const Joueur* joueur, int index) {
    printf("\n=== Joueur %d : %s===\n", index + 1, joueur->nom);

    //cartes personnelles
    printf("Cartes :\n");
    for (int i = 0; i < joueur->nb_cartes; ++i) {
        const Carte* c = &joueur->cartes[i];
        if (c->visible)
            printf("  [%2d] (visible)\n", c->valeur);
        else
            printf("  [??] (cachée)\n");
    }

    // défausse 
    printf("Défausse : ");
    if (joueur->nb_defausse > 0) {
        const Carte* top = &joueur->defausse[joueur->nb_defausse - 1];
        printf("[%2d] (%d carte%s)\n", top->valeur, joueur->nb_defausse,
               joueur->nb_defausse > 1 ? "s" : "");
    } else {
        printf("[vide]\n");
    }
}


void afficher_pioche(const Carte* pioche, int taille) {
    printf("\n=== Pioche centrale ===\n");

    if (taille > 0) {
        printf("[ ? ] (il reste %d carte%s)\n", taille, taille > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }
}


void afficher_defausse(const Carte* defausse, int taille) {
    printf("\n=== Défausse du joueur ===\n");

    if (taille > 0) {
        const Carte* top = &defausse[taille - 1]; 
        printf("[ %2d ] (%d carte%s)\n", top->valeur, taille, taille > 1 ? "s" : "");
    } else {
        printf("[ Vide ]\n");
    }
}



