# Nom de l'exécutable
TARGET = cardyard

# Liste des fichiers sources
SRCS = main.c cards.c display.c game.c player.c save.c utils.c

# Liste des fichiers objets
OBJS = $(SRCS:.c=.o)

# Drapeaux pour la compilation
CFLAGS = -Wall -g

# Règle par défaut : génère l'exécutable
all: $(TARGET)

# Règle pour générer l'exécutable à partir des objets
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour nettoyer et recompiler tout
fclean: clean
	make all

# Règle pour recompiler (sans nettoyer les fichiers objets)
re: fclean
	make all

# Règle pour compiler les tests (si nécessaire)
# test:
#	$(CC) $(CFLAGS) -o test_program test_program.c
