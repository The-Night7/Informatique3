# Exercice 3 (Copie et déplacement)

# 1. Effectuer une copie du fichier mesMusiques vers le fichier myMusic.
cat mesMusiques > myMusic

# 2. Afficher la taille des 2 fichiers et comparer.
ls -lh mesMusiques myMusic 2>/dev/null || echo "Le fichier original n'existe plus après le déplacement."

# 3. Renommer le fichier myMusic en mySongs.
mv myMusic mySongs

# 4. Quelle différence entre les commandes mv myMusic mySongs et cp myMusic mySongs ?
# La commande `mv myMusic mySongs` déplace le fichier `myMusic` en le renommant en `mySongs`, tandis que la commande `cp myMusic mySongs` crée une copie du fichier `myMusic` sous le nom `mySongs`.