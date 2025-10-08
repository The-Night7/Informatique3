CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Répertoire des TDs
TD_DIR = Informatique3
# Trouver tous les fichiers source .c dans le répertoire des TDs et ses sous-répertoires
SOURCES = $(shell find $(TD_DIR) -type f -name "*.c")
# Créer la liste des exécutables (sans extension)
EXECUTABLES = $(patsubst %.c,%,$(SOURCES))

# Règle par défaut
all: $(EXECUTABLES)

# Règle pour compiler chaque fichier source directement en exécutable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Règle pour nettoyer les fichiers générés
clean:
	find $(TD_DIR) -type f -executable -delete

# Aide pour l'utilisation du Makefile
help:
	@echo "Usage:"
	@echo "  make all    - Compile tous les fichiers source .c dans Informatique3"
	@echo "  make clean  - Supprime tous les exécutables"
	@echo "  make help   - Affiche cette aide"
	@echo "  make Informatique3/td1/nom  - Compile uniquement le fichier Informatique3/td1/nom.c"

.PHONY: all clean help
