void initialiserJeuCartes(Carte jeu[], int *taille) {
    int index = 0;
    for (int i = 0; i < 5; i++) {
        jeu[index].value = -2;
        jeu[index].visible = 0; 
        index++;
    }
    for (int i = 0; i < 10; i++) {
        jeu[index].value = -1;
        jeu[index].visible = 0;
        index++;
    }
    *taille = index; 
}
void echangerCartes(Carte *cartePioche, Carte *cartePerso) {
    Carte temp = *cartePioche;  
    *cartePioche = *cartePerso; 
    *cartePerso = temp;         
    cartePerso->visible = 1;   
void calculerScore(Joueur *j) {
    j->score = 0; 
    for (int i = 0; i < j->nbCartes; i++) {
        j->score += j->cartesPersonnelles[i].value;
    }
}
}
int demander_valeur() {
    int valeur;

    printf("entrer une valeur : ");
    scanf("%d", &valeur);
    if (valeur != 1) {
        printf( "Erreur\n");
    }

    return valeur;
}

void affiche_carte(int carte[]){
    for(int i=0; i<nombre de carte; i++){
    printf("[ %d ]", carte[i]);
    }
}

void melangerCartes(int cartes[], int nombre de carte) {
    for (int i = nombre de carte - 1; i > 0; i--) {
        
        int j = rand() % (i + 1);

        Carte temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}
