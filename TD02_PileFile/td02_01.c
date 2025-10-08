/* Résolution de l'Exercice 1 : Application du cours
1. Manipulation de la pile
La pile initiale est :
[2, 5, 9, 10, 1, -3]
(-3 étant le sommet de la pile)
Opérations effectuées dans l'ordre donné :


Dépiler : On enlève le sommet de la pile (-3).
État de la pile : [2, 5, 9, 10, 1]


Dépiler : On enlève le sommet (1).
État de la pile : [2, 5, 9, 10]


Empiler 12 : On ajoute 12 au sommet.
État de la pile : [2, 5, 9, 10, 12]


Dépiler : On enlève le sommet (12).
État de la pile : [2, 5, 9, 10]


Empiler 8 : On ajoute 8 au sommet.
État de la pile : [2, 5, 9, 10, 8]


Empiler 7 : On ajoute 7 au sommet.
État final de la pile : [2, 5, 9, 10, 8, 7]


Opérations effectuées dans l'ordre inverse :


Empiler 7 : On ajoute 7 au sommet.
État de la pile : [2, 5, 9, 10, 1, -3, 7]


Empiler 8 : On ajoute 8 au sommet.
État de la pile : [2, 5, 9, 10, 1, -3, 7, 8]


Dépiler : On enlève le sommet (8).
État de la pile : [2, 5, 9, 10, 1, -3, 7]


Empiler 12 : On ajoute 12 au sommet.
État de la pile : [2, 5, 9, 10, 1, -3, 7, 12]


Dépiler : On enlève le sommet (12).
État de la pile : [2, 5, 9, 10, 1, -3, 7]


Dépiler : On enlève le sommet (7).
État final de la pile : [2, 5, 9, 10, 1, -3]



2. Manipulation de la file
La file initiale est :
[2, 5, 9, 10, 1, -3]
(2 étant le premier élément, -3 le dernier)
Opérations effectuées dans l'ordre donné :


Défiler : On enlève le premier élément (2).
État de la file : [5, 9, 10, 1, -3]


Défiler : On enlève le premier élément (5).
État de la file : [9, 10, 1, -3]


Enfiler 12 : On ajoute 12 à la fin.
État de la file : [9, 10, 1, -3, 12]


Défiler : On enlève le premier élément (9).
État de la file : [10, 1, -3, 12]


Enfiler 8 : On ajoute 8 à la fin.
État de la file : [10, 1, -3, 12, 8]


Enfiler 7 : On ajoute 7 à la fin.
État final de la file : [10, 1, -3, 12, 8, 7]


Opérations effectuées dans l'ordre inverse :


Enfiler 7 : On ajoute 7 à la fin.
État de la file : [2, 5, 9, 10, 1, -3, 7]


Enfiler 8 : On ajoute 8 à la fin.
État de la file : [2, 5, 9, 10, 1, -3, 7, 8]


Défiler : On enlève le premier élément (2).
État de la file : [5, 9, 10, 1, -3, 7, 8]


Enfiler 12 : On ajoute 12 à la fin.
État de la file : [5, 9, 10, 1, -3, 7, 8, 12]


Défiler : On enlève le premier élément (5).
État de la file : [9, 10, 1, -3, 7, 8, 12]


Défiler : On enlève le premier élément (9).
État final de la file : [10, 1, -3, 7, 8, 12]



3. Simulation d'une file à l'aide de piles
Pour simuler une file à l’aide de piles :

Utiliser deux piles : une pile d’entrée et une pile de sortie.
Lorsqu’un élément est ajouté à la file, il est empilé dans la pile d’entrée.
Lorsqu’un élément doit être défiler (retiré de la file), on dépile tous les éléments de la pile d’entrée et les empile dans la pile de sortie. Le sommet de la pile de sortie correspond au premier élément de la file.
Une fois l’élément retiré, les autres éléments sont réempilés dans la pile d’entrée.

Cela permet de simuler le comportement FIFO d’une file en utilisant des piles LIFO.