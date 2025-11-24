#Exercice 3 (Filtrage en ligne)
#1. Afficher seulement la première ligne du fichier soccer.csv.
head -n 1 soccer.csv

#2. Afficher les 100 premières lignes du fichier soccer.csv.
head -n 100 soccer.csv
#3. Afficher toutes les lignes du fichier soccer.csv à l'exception de la dernière.
head -n -1 soccer.csv
#4. Afficher toutes les lignes du fichier soccer.csv à l'exception des 70 dernières.
head -n -70 soccer.csv

#5. Afficher seulement la dernière ligne du fichier soccer.csv.
tail -n 1 soccer.csv

#6. Afficher les 5 dernières lignes du fichier soccer.csv.
tail -n 5 soccer.csv
#7. Afficher toutes les lignes du fichier soccer.csv à l'exception de la première.
tail -n +2 soccer.csv
#8. Afficher toutes les lignes du fichier soccer.csv à l'exception des 100 premières.
tail -n +101 soccer.csv

#9. Créer un fichier data.csv qui contient les lignes 12 à 14 inclus ainsi que les lignes 33 à 36 inclus du fichier soccer.csv. Il
#ne faut utiliser QUE les commandes head, tail, cat et les redirections de la sortie standard vers un fichier. Il est autorisé
#de créer des fichiers intermédiaires mais il faudra les supprimer à la fin des opérations.
head -n 14 soccer.csv | tail -n 3 > temp1.csv
head -n 36 soccer.csv | tail -n 4 > temp2.csv
cat temp1.csv temp2.csv > data.csv
rm temp1.csv temp2.csv
