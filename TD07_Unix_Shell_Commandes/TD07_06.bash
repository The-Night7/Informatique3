# Exercice 6 (Droits d’accès)

# 1. Un répertoire a les droits suivants : drwx-x-x. Un utilisateur qui n'est pas le propriétaire peut-il afficher le contenu
# du répertoire ? Quelles sont les actions que peut faire cet utilisateur ?

# Pour un répertoire avec les droits drwx-x-x (700):
# - Un utilisateur qui n'est pas le propriétaire NE PEUT PAS afficher le contenu du répertoire car il n'a pas le droit de lecture (r).
# - Les actions qu'un utilisateur non-propriétaire peut faire:
#   * Traverser le répertoire (accéder aux fichiers à l'intérieur s'il connaît leur nom exact) grâce au droit d'exécution (x)
#   * Il ne peut pas lister le contenu (pas de droit r)
#   * Il ne peut pas créer/supprimer des fichiers dans ce répertoire (pas de droit w)


# 2. Créer un dossier Moi, et affecter les droits suivants : drwxr-x-wx. Ces droits sont-ils pertinents pour un fichier ou un
# dossier ? Justifier. Proposer un cas général de droits restrictifs en fonction des utilisateurs. Modifier les droits du dossier
# avec votre proposition.

# Ces droits (drwxr-x-wx) sont plus pertinents pour un dossier que pour un fichier:
# - Pour un dossier: Cela signifie que le propriétaire a tous les droits, le groupe peut lire et exécuter (traverser),
#   et les autres peuvent écrire et exécuter mais pas lire (ils peuvent créer/supprimer des fichiers mais ne peuvent pas lister le contenu).
# - Pour un fichier: Le droit d'exécution sans lecture pour les autres serait étrange car généralement on a besoin de lire un fichier pour l'exécuter.
#
# Ces droits ne sont pas très cohérents car ils permettent aux "autres" d'écrire dans un dossier dont ils ne peuvent pas voir le contenu.
#
# Une proposition plus restrictive et logique serait:
# - drwxr-x--- (750): Le propriétaire a tous les droits, le groupe peut lire et traverser le dossier, les autres n'ont aucun droit.

mkdir "Moi"
chmod 753 "Moi"  # Sets permissions to drwxr-x-wx
