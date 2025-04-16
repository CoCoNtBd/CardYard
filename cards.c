
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
