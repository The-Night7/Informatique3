#Exercice 4 (Filtrage en colonne)
#1. Afficher le contenu du fichier /etc/passwd en ne gardant QUE le nom des utilisateurs.
cut -d: -f1 /etc/passwd

#2. Afficher le contenu du fichier soccer.csv en ne gardant QUE le nom du joueur et sa date de naissance.
cut -d, -f1,4 soccer.csv

#3. Afficher le contenu du fichier soccer.csv en ne conservant que les 4 premiers champs de chaque ligne.
cut -d, -f1-4 soccer.csv

#4. Afficher le contenu du fichier soccer.csv en supprimant les noms de tous les joueurs.
cut -d, -f2- soccer.csv
#5. Afficher le contenu du fichier soccer.csv en ne conservant QUE les noms des joueurs et les pays. L'affichage de sortie
#aura remplacé toutes les virgules par des points-virgules.
cut -d, -f1,3 soccer.csv | tr ',' ';'
