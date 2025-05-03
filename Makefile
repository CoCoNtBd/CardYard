# Nom de l'exécutable
EXEC = cardyard

# Tous les fichiers source du projet
SRC = main.c \
      game.c \
      player.c \
      cards.c \
      display.c \
      save.c \
      utils.c

# Fichiers objets générés (.o)
OBJ = $(SRC:.c=.o)

# Options du compilateur
CFLAGS = -Wall -Wextra -std=c99

# Compilateur
CC = gcc

# Règle par défaut : compilation complète
all: $(EXEC)

# Création de l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Supprimer les fichiers objets uniquement
clean:
	rm -f *.o

# Supprimer les objets ET l'exécutable
mrproper: clean
	rm -f $(EXEC)
