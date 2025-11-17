# Exercice 7 (Alias de commandes)

# 1. Qu'est-ce qu'un alias ?

# Un alias est une commande personnalisée qui permet de remplacer une commande ou une séquence de commandes par un mot ou une
# expression plus courte ou plus facile à mémoriser. C'est un raccourci qui permet d'exécuter une commande plus longue ou
# complexe en tapant simplement l'alias défini. Les alias sont particulièrement utiles pour simplifier les commandes fréquemment
# utilisées ou pour créer des versions personnalisées de commandes existantes avec des options prédéfinies.

# 2. Afficher tous les alias actuellement chargés dans la session de votre terminal. Décrire le résultat affiché. Quel est l'impact
# d'un alias sur une commande si les deux ont exactement la même syntaxe ?

# alias egrep='egrep --color=auto'
# alias fgrep='fgrep --color=auto'
# alias grep='grep --color=auto'
# alias l='ls -CF'
# alias la='ls -A'
# alias ll='ls -alF'
# alias ls='ls --color=auto'

# Pour afficher tous les alias actuellement chargés dans la session du terminal, on utilise la commande 'alias' sans argument.
# Le résultat affiche une liste de tous les alias définis dans la session courante, sous la forme "alias nom='commande'".
# Ces alias peuvent inclure des raccourcis prédéfinis par le système (comme 'll' pour 'ls -l') et des alias personnalisés.

# Si un alias a exactement la même syntaxe qu'une commande existante, l'alias a priorité sur la commande originale.
# Cela signifie que lorsque vous tapez cette commande, c'est l'alias qui sera exécuté à la place de la commande d'origine.
# Pour exécuter la commande originale malgré l'existence d'un alias, on peut soit utiliser le chemin complet de la commande,
# soit précéder la commande d'un backslash (\), soit utiliser la commande 'command' suivie du nom de la commande.

# 3. Dans le terminal, entrer la commande suivante : alias cd='ls'. Utiliser la commande cd : que se passe-t-il ?

# Lorsqu'on crée l'alias cd='ls', on redéfinit la commande cd pour qu'elle exécute ls à la place.
# Quand on utilise la commande cd après avoir créé cet alias, au lieu de changer de répertoire,
# la commande liste le contenu du répertoire courant (comme le ferait la commande ls).
# Par exemple, si on tape "cd /etc", au lieu d'aller dans le répertoire /etc,
# la commande va lister le contenu du répertoire /etc.
# Cela peut être déroutant car la commande cd ne remplit plus sa fonction habituelle
# de changement de répertoire.

# 4. Supprimer l'alias cd créé précédemment. Tester à nouveau la commande cd pour voir si le changement est bien pris en compte.

# Pour supprimer l'alias cd, on utilise la commande 'unalias' suivie du nom de l'alias à supprimer.
# unalias cd

# Après avoir supprimé l'alias cd, la commande cd retrouve son comportement normal.
# On peut tester en utilisant cd pour changer de répertoire, par exemple :
cd /tmp
pwd  # Affiche /tmp, confirmant que la commande cd fonctionne normalement à nouveau

# La commande 'unalias' supprime l'alias spécifié de la liste des alias définis dans la session courante.
# Une fois l'alias supprimé, la commande originale (dans ce cas, cd) retrouve son comportement par défaut.

# 5. Définir un alias myDirs qui va afficher tous les sous-répertoires de la racine de votre dossier personnel. Tester l'alias
# créé

# Pour définir un alias myDirs qui affiche tous les sous-répertoires du dossier personnel:
alias myDirs='find $HOME -maxdepth 1 -type d | sort'

# Cet alias utilise la commande find pour rechercher tous les éléments de type dossier (-type d)
# dans le répertoire personnel ($HOME) avec une profondeur maximale de 1 (-maxdepth 1),
# puis trie les résultats. Cela affichera le dossier personnel et tous ses sous-répertoires directs.

# 6. Quitter le terminal, et le réouvrir. Utiliser l'alias précédent : que se passe-t-il ?

# Après avoir quitté et rouvert le terminal, l'alias myDirs n'est plus disponible.
# Si on essaie de l'utiliser, le terminal affichera une erreur du type "myDirs: command not found".
# Cela se produit parce que les alias définis directement dans le terminal ne sont valables
# que pour la session en cours et ne sont pas sauvegardés automatiquement.

# 7. Afficher le contenu du fichier .bashrc qui se trouve à la racine de votre répertoire personnel. Que contient ce fichier ?

# Pour afficher le contenu du fichier .bashrc:
# cat ~/.bashrc

# Le fichier .bashrc contient des configurations pour le shell Bash qui sont chargées à chaque
# ouverture d'un terminal interactif. Il inclut généralement:
# - Des définitions d'alias prédéfinis (comme ll, la, etc.)
# - Des configurations d'environnement (variables d'environnement, PATH, etc.)
# - Des personnalisations de l'invite de commande (PS1)
# - Des fonctions shell utiles
# - Des options de comportement du shell
# Ce fichier est exécuté automatiquement au démarrage de chaque nouveau terminal Bash.

# 8. Avec un éditeur de texte, modifier le fichier .bashrc pour y ajouter l'alias qui affiche les dossiers du répertoire personnel.
# Tester à nouveau l'alias myDirs dans la session actuelle du terminal. Que se passe-t-il ?

# Pour ajouter l'alias myDirs au fichier .bashrc, on peut utiliser un éditeur comme nano:
# nano ~/.bashrc

# À la fin du fichier, on ajoute la ligne:
# alias myDirs='find $HOME -maxdepth 1 -type d | sort'

# Après avoir modifié le fichier .bashrc, l'alias n'est pas immédiatement disponible dans la session
# actuelle du terminal. Si on teste myDirs, on obtiendra toujours l'erreur "command not found".
# Cela est dû au fait que le fichier .bashrc est lu uniquement au démarrage du terminal
# ou lorsqu'on le source explicitement.

# 9. Fermer le terminal et rouvrir une nouvelle session. Tester l'alias myDirs : que se passe-t-il ?

# Après avoir fermé et rouvert le terminal, l'alias myDirs est maintenant disponible et fonctionne
# correctement. Le nouveau terminal a chargé le fichier .bashrc modifié au démarrage,
# ce qui a rendu l'alias disponible.

# Alternativement, au lieu de fermer et rouvrir le terminal, on aurait pu utiliser la commande
# 'source ~/.bashrc' ou '. ~/.bashrc' pour recharger le fichier .bashrc dans la session actuelle.
