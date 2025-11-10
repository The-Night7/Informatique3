/* 1. Construire un AVL en insérant les éléments dans cet ordre : 10, 3, 5, 15, 20, 12, 7, 9.
 *
 * Insertion de 10 : Arbre = 10
 * Insertion de 3 : Arbre = 10(3,-)
 * Insertion de 5 : Arbre déséquilibré, rotation gauche-droite
 *                  Après rotation : 5(3,10)
 * Insertion de 15 : Arbre = 5(3,10(-, 15))
 * Insertion de 20 : Arbre déséquilibré, rotation gauche
 *                   Après rotation : 5(3, 15(10, 20))
 * Insertion de 12 : Arbre = 5(3, 15(10(-, 12), 20))
 * Insertion de 7 : Arbre = 5(3(-, 7), 15(10(-, 12), 20))
 * Insertion de 9 : Arbre = 5(3(-, 7(-, 9)), 15(10(-, 12), 20))
 *
 * 2. Construire un second AVL en insérant les éléments dans l'ordre inverse que précédemment.
 *
 * Insertion de 9, 7, 12, 20, 15, 5, 3, 10
 * Arbre final = 9(7(5(3,-), -), 15(12, 20))
 *
 * 3. Effectuer un parcours infixe sur ces deux arbres. Que remarque-t-on ?
 *
 * Parcours infixe du premier arbre : 3, 5, 7, 9, 10, 12, 15, 20
 * Parcours infixe du second arbre : 3, 5, 7, 9, 12, 15, 20
 *
 * On remarque que les parcours infixes des deux arbres donnent les éléments dans l'ordre croissant,
 * malgré des structures d'arbres différentes. C'est une propriété fondamentale des arbres binaires
 * de recherche (dont les AVL font partie) : le parcours infixe donne toujours les éléments dans l'ordre.
 *
 * 4. Supprimer l'élément 5 puis 12 du premier arbre. Redessiner l'arbre obtenu après chacune des suppressions.
 *
 * Suppression de 5 :
 * - 5 est remplacé par son successeur infixe (7)
 * - Après rééquilibrage : 7(3, 15(10(-, 12), 20))
 *
 * Suppression de 12 :
 * - 12 est une feuille, on la supprime simplement
 * - Après rééquilibrage : 7(3, 15(10, 20))
 */