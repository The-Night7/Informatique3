#Exercice 1 (Lecture et Ecriture de fichiers)
#1. Pour ce TD, dans votre dossier personnel, créer un dossier TD8_UNIX et se placer à l’intérieur.
mkdir "TD8_UNIX"
cd "TD8_UNIX"
#2. Afficher le contenu du fichier les3M.txt de 2 manières : en utilisant les paramètres de la commande cat, puis en utilisant
#la redirection de l’entrée standard.
cat "../../Fichiers_pour_les_TDs/les3M.txt"
#3. Quelle commande permet de compter les lignes/mots d'un fichier ? Afficher le nombre de lignes du fichier les3M.txt en
#utilisant les paramètres de la commande, puis afficher le nombre de mots du fichier les3M.txt en utilisant la redirection
#de l'entrée standard. Mise à part la valeur numérique affichée, quelle différence est visible entre les 2 résultats des
#commandes ?
wc -l "../../Fichiers_pour_les_TDs/les3M.txt"
wc -w < "../../Fichiers_pour_les_TDs/les3M.txt"
# ---- La différence est que lorsqu'on utilise la redirection, le nom du fichier n'est pas affiché dans le résultat
#4. En une seule commande, créer un fichier hoy qui contiendra la date du système
echo $(date +"%Y-%m-%d") > hoy.txt
#5. Créer un fichier vide Dartagnan.txt, ajouter dedans (à l’aide d’une commande) la phrase suivante : Tous pour un, un
#pour tous ! et afficher le contenu du fichier pour vérifier.
echo "Tous pour un, un pour tous !" > Dartagnan.txt
cat Dartagnan.txt
#6. En une seule commande, ajouter le texte suivant à la suite du contenu du fichier Dartagnan.txt : Amaris Afficher
#ensuite le contenu du fichier résultant.
echo "Amaris" >> Dartagnan.txt
cat Dartagnan.txt
#Quelle différence entre les deux ?
cat "../../Fichiers_pour_les_TDs/soccer.csv"
more "../../Fichiers_pour_les_TDs/soccer.csv"
# ---- La différence est que more affiche le contenu page par page, permettant de naviguer avec la barre d'espace, tandis que cat affiche tout le contenu d'un coup
#8. Afficher le contenu du fichier soccer.csv, par groupes successifs de 3 lignes, et ce, à partir de la ligne 15 incluse.
#L'affichage est-il celui attendu ? Modifier la commande pour afficher les lignes correctement ?
tail -n +15 "../../Fichiers_pour_les_TDs/soccer.csv" | head -n 3
# ---- Pour afficher correctement 3 lignes à partir de la ligne 15
#9. Afficher le contenu du fichier soccer.csv en inversant l'ordre des lignes du fichier.
tac "../../Fichiers_pour_les_TDs/soccer.csv"
# ---- On peut aussi utiliser: cat "../../Fichiers_pour_les_TDs/soccer.csv" | rev