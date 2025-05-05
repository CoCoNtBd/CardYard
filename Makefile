# Nom de l'exécutable final
EXEC = cardyard

# Liste des fichiers sources
SRC = main.c game.c cards.c player.c save.c display.c utils.c

# Liste des headers (pour les dépendances)
HEADERS = game.h cards.h player.h save.h display.h utils.h

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Object files
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(EXEC)

# Lier les objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation de chaque fichier .c en .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers compilés
clean:
	rm -f *.o $(EXEC)

# Nettoyage + suppression de sauvegardes éventuelles
mrproper: clean
	rm -f *~ *.bak

# Exécution rapide
run: $(EXEC)
	./$(EXEC)
