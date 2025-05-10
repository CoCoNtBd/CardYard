# CardYard

CardYard est un jeu de cartes écrit en langage C. C'est un jeu multijoueur où chaque joueur doit optimiser ses cartes afin d'obtenir le score les plus bas.Pour cela ils peuvent interagir avec la pioche ou les defausses visible.

## Table des matières
1. [Description](#description)
2. [Installation](#installation)
3. [Utilisation](#utilisation)

## Description

CardYard possède un mécanisme de jeu simple : chaque joueur reçoit un nombre de cartes cachées et, à chaque tour, il a le choix de piocher ou de prendre une carte visible dans la défausse d'un joueur. Le but est que la somme des cartes du joueur soit la plus basse à la fin de la partie.
Une fois qu'un joueur a révélé toutes ses cartes, le tour se finit. Le gagnant est celui avec la somme la moins élevée.


### Fonctionnalités principales

- Jeu en terminal avec affichage graphique ASCII des cartes
- Défausses visibles par joueur
- Pioche mélangée aléatoirement
- Choix entre une pioche par défaut ou personnalisée
- Sauvegarde et chargement de parties
- Calcul automatique des scores finaux et affichage du gagnant

### Prérequis

- `gcc` pour compiler le projet
- Un terminal compatible ANSI (pour les couleurs)
- Un OS Linux ou Mac (ou Windows avec WSL)

---

## Installation

1. Clonez le dépôt :

```bash
git clone https://github.com/votre-utilisateur/cardyard.git
cd cardyard
```
## Utilisation

### Compilation :

```bash
make
```
### Lancer le jeu :

```bash
./cardyard
```
### exemple d'une partie 

1. Nouvelle partie
2. Charger une partie
3. Quitter

Choix : 1
Nombre de joueurs : 3
Valeurs des cartes : Par défaut
Nom joueur 1 : Alice
Nom joueur 2 : Bob
Nom joueur 3 : Carol

### Exemple de suavegarde :

Nom du fichier de sauvegarde : partie1.save
Sauvegarde réussie !

### Relancer une partie sauvegarder :

./cardyard
Choix : 2
Nom du fichier de sauvegarde : partie1.save




