/* Soit l'arbre suivant :
 *                          1
 *                     /    |    \
 *                   2      4     6
 *                 / | \   / \   / \
 *                7  8  9 10 12 13 14
 *                  / \       / / \ \
                   15 16    17 18 19 20

 * 1. Donner :
 * — l'ordre de l'arbre : 3 (car un nœud peut avoir au maximum 3 enfants)
 *
 * — le degrés du nœud 4 : 2 (car il a 2 enfants : 10 et 12)
 *   le degrés du nœud 2 : 3 (car il a 3 enfants : 7, 8 et 9)
 *
 * — le nombre de feuilles : 9 (les nœuds 7, 15, 16, 9, 10, 12, 17, 18, 19, 20)
 *
 * — la hauteur de l'arbre : 3 (du nœud 1 jusqu'aux feuilles les plus profondes comme 15, 16, 17, 18, 19, 20)
 *
 * 2. Quel est le parcours en longueur préfixe de cet arbre ?
 *    Parcours en profondeur préfixe : 1, 2, 7, 8, 15, 16, 9, 4, 10, 12, 6, 13, 17, 14, 18, 19, 20
 *
 * 3. Quel est le parcours en largeur de cet arbre ?
 *    Parcours en largeur : 1, 2, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20
 */
