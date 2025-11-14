# Exercice 5 (Suppression de fichiers/dossiers)
# 1. Supprimer le répertoire myFiles à l’aide de la commande rm. Quel est le résultat ?
echo "rm myFiles => rm: cannot remove 'myFiles': Is a directory"

# 2. Supprimer myFiles à l’aide de la commande rmdir. Quel est le résultat ?
echo "rmdir myFiles => rmdir: failed to remove 'myFiles': Directory not empty"

# 3. Supprimer le dossier myFiles et tout ce qu'il contient avec la commande rm en mode récursif.
rm -r myFiles

# 4. Maintenant que myFiles n’existe plus, relancer la commande précédente. Quel est le résultat ?
echo "rm -r myFiles (bis) => rm: cannot remove 'myFiles': No such file or directory"

# 5. Relancer la commande précédente en faisant en sorte qu'elle n'affiche aucun message d'erreur si la cible n'existe pas.
rm -rf myFiles