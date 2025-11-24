#Exercice 5 (Redirections entre commandes)
#1. Afficher le contenu détaillé du répertoire /bin mais en faisant en sorte de l'afficher petit à petit, page par page à l'écran.
ls -l /bin | less
#2. Créer un fichier nbBinFiles qui contiendra le nombre d'éléments présents dans le répertoire /bin.
ls -l /bin | wc -l > nbBinFiles

#3. Stocker le contenu du fichier soccer.csv entre les lignes 22 et 27 (incluses) dans le fichier results.txt, en une seule ligne
#de commandes. Ensuite, afficher le contenu du fichier results.txt pour vérifier.
sed -n '22,27p' soccer.csv > results.txt && cat results.txt

#4. Ajouter dans le fichier results.txt, les lignes 3 à 7 du fichier soccer.csv. Vérifier le résultat dans le fichier cible.
sed -n '3,7p' soccer.csv >> results.txt && cat results.txt

#5. Afficher uniquement les noms des joueurs du fichier soccer.csv mais dans un ordre aléatoire.
cut -d',' -f1 soccer.csv | sort -R
#6. Filtrer les noms des joueurs comme dans la question précédente, et vérifier qu'ils sont classés dans l'ordre croissant.
#Quel résultat obtient-on ? Trier les noms par ordre croissant et vérifier à nouveau. Refaire la manipulation avec un tri
#en ordre inverse et une vérification que les données sont bien triées en ordre inverse.
cut -d',' -f1 soccer.csv | sort | sort -c
cut -d',' -f1 soccer.csv | sort | sort -c
cut -d',' -f1 soccer.csv | sort -r | sort -rc
#7. Afficher à l'écran les nom et age des joueurs présents dans le fichier soccer.csv, triés par age croissant d'abord, puis par
#nom décroissant ensuite. Le nom et l'age en sortie seront séparés par le caractère ' :'.
awk -F, '{print $1 " :" $2}' soccer.csv | sort -t: -k2,2n -k1,1r
#8. Quelle différence y a-t-il entre un 'pipe' classique et l'option -exec de la commande find ?
# Un pipe (|) permet de rediriger la sortie standard d'une commande vers l'entrée standard d'une autre commande.
# L'option -exec de find permet d'exécuter une commande sur chaque fichier trouvé par find.
# La différence principale est que -exec traite chaque fichier individuellement, tandis que le pipe transmet l'ensemble des résultats à la fois.