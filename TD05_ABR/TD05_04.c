/*
 * Proposer une fonction permettant de vérifier si un arbre binaire est un ABR ou non.
 */

#include <stdbool.h>
#include <limits.h>

// Définition d'un nœud d'arbre binaire
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction auxiliaire pour vérifier si un sous-arbre est un ABR
// avec des bornes minimales et maximales
bool estABRUtil(Node* racine, int min, int max) {
    // Un arbre vide est un ABR
    if (racine == NULL)
        return true;

    // Vérifier que la valeur du nœud est dans les bornes
    if (racine->data <= min || racine->data >= max)
        return false;

    // Vérifier récursivement les sous-arbres gauche et droit
    // Pour le sous-arbre gauche, la valeur maximale est la valeur du nœud actuel
    // Pour le sous-arbre droit, la valeur minimale est la valeur du nœud actuel
    return estABRUtil(racine->left, min, racine->data) &&
           estABRUtil(racine->right, racine->data, max);
}

// Fonction principale pour vérifier si un arbre binaire est un ABR
bool estABR(Node* racine) {
    return estABRUtil(racine, INT_MIN, INT_MAX);
}
