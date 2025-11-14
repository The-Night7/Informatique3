# Exercice 2 (Création de fichier)

# 1. Créer un fichier hello.c contenant le code minimal d'un programme en langage C.
# Afficher le type de contenu de ce fichier.
echo '#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}' > hello.c
file hello.c

# 2. Compiler le programme hello.c précédent et afficher le type de contenu de l'exécutable obtenu.
gcc hello.c -o hello
file hello

# 3. Dans votre dossier personnel, créer un fichier appelé mesMusiques. Insérer quelques lignes à
# l'intérieur de ce fichier à l'aide de votre éditeur de texte.
echo "Mes musiques préférées:
1. Bohemian Rhapsody - Queen
2. Stairway to Heaven - Led Zeppelin
3. Imagine - John Lennon
4. Hotel California - Eagles" > mesMusiques

# 4. Afficher le contenu du fichier mesMusiques sur le terminal.
cat mesMusiques

# 5. Afficher le type de contenu du fichier mesMusiques sur le terminal.
file mesMusiques