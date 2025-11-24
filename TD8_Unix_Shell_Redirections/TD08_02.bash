#Exercice 2 (Tris de lignes)
#1. Trier le contenu du fichier soccer.csv pour afficher les joueurs par ordre alphabétique
sort -t, -k1,1 soccer.csv

#2. Trier le contenu du fichier soccer.csv pour afficher les noms des pays par ordre décroissant.
sort -t, -k3,3r soccer.csv

#3. Trier le contenu du fichier soccer.csv pour afficher les joueurs par poids, par ordre numérique décroissant (attention :
#on ne veut pas le résultat par ordre lexicographique). Que remarquez-vous concernant la dernière ligne affichée ?
sort -t, -k5,5nr soccer.csv

#4. reprendre la question précédente et stocker le résultat dans un fichier soccer_weight.csv. Afficher le contenu du fichier
#soccer_weight.csv.
sort -t, -k5,5nr soccer.csv > soccer_weight.csv
cat soccer_weight.csv
