/* 1. Construire un arbre binaire en insérant les éléments dans cet ordre ; 10, 3, 5, 15, 20, 12, 7, 45, 9.
 * 2. Construire un second arbre binaire en insérant les éléments dans l'ordre inverse que précédement. Obtient-on le même
 *    arbre ? Non, on n'obtient pas le même arbre. La structure de l'arbre dépend de l'ordre d'insertion des éléments.
 * 3. Effectuer un parcours infixe sur ces deux arbres. Que remarque-t-on ?
 *    On remarque que malgré des structures différentes, le parcours infixe donne les éléments dans le même ordre
 *    (ordre croissant), car le parcours infixe d'un arbre binaire de recherche produit toujours une séquence triée.
 *
 * 4. Supprimer l'élément 5 puis 12 du premier arbre.
 */
#include <stdio.h>
#include <stdlib.h>

// Structure pour un nœud de l'arbre binaire de recherche
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction pour créer un nouveau nœud
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un nœud dans l'arbre
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Fonction pour trouver le nœud avec la valeur minimale
Node* findMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Fonction pour supprimer un nœud de l'arbre
Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Nœud avec une seule feuille ou pas de feuille
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Nœud avec deux enfants: obtenir le successeur inordre (plus petit dans le sous-arbre droit)
        Node* temp = findMinValueNode(root->right);

        // Copier le contenu du successeur inordre à ce nœud
        root->data = temp->data;

        // Supprimer le successeur inordre
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Fonction pour parcourir l'arbre en ordre infixe
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void printTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }

    // Afficher le sous-arbre droit en premier (niveau supérieur)
    printTree(root->right, level + 1);

    // Afficher le nœud courant avec indentation
    for (int i = 0; i < level; i++) {
        printf("    ");  // Chaque niveau augmente l'indentation
    }
    printf("%d\n", root->data);

    // Afficher le sous-arbre gauche
    printTree(root->left, level + 1);
}

static void printWithPrefix(Node* node, const char* prefix, int isLast) {
    if (!node) return;

    // branche + valeur
    printf("%s%s%d\n", prefix, isLast ? "└── " : "├── ", node->data);

    // Préfixe pour les enfants
    char nextPrefix[1024];
    snprintf(nextPrefix, sizeof(nextPrefix), "%s%s", prefix, isLast ? "    " : "│   ");

    // Lister les enfants (gauche puis droite)
    Node* children[2];
    int count = 0;
    if (node->left)  children[count++] = node->left;
    if (node->right) children[count++] = node->right;

    for (int i = 0; i < count; ++i) {
        int childIsLast = (i == count - 1);
        printWithPrefix(children[i], nextPrefix, childIsLast);
    }
}

void printTreeTopDown(Node* root) {
    if (!root) { puts("(arbre vide)"); return; }
    // Afficher la racine sans préfixe, puis ses enfants
    printf("%d\n", root->data);

    char prefix[1] = {0}; // chaîne vide
    Node* children[2];
    int count = 0;
    if (root->left)  children[count++] = root->left;
    if (root->right) children[count++] = root->right;

    for (int i = 0; i < count; ++i) {
        int childIsLast = (i == count - 1);
        printWithPrefix(children[i], "", childIsLast);
    }
}

int main() {
    Node* root1 = NULL;
    int elements[] = {10, 3, 5, 15, 20, 12, 7, 45, 9};
    int n = sizeof(elements) / sizeof(elements[0]);

    // 1. Construction du premier arbre
    printf("1. Construction du premier arbre:\n");
    for (int i = 0; i < n; i++) {
        root1 = insert(root1, elements[i]);
    }
    printf("Premier arbre:\n");
    printTreeTopDown(root1);

    // 2. Construction du second arbre (ordre inverse)
    Node* root2 = NULL;
    printf("\n2. Construction du second arbre (ordre inverse):\n");
    for (int i = n - 1; i >= 0; i--) {
        root2 = insert(root2, elements[i]);
    }
    printf("Second arbre:\n");
    printTreeTopDown(root2);

    printf("\nLes deux arbres sont différents en structure mais ils représentent le même ensemble de données.\n");

    // 3. Parcours infixe des deux arbres
    printf("\n3. Parcours infixe des deux arbres:\n");
    printf("Parcours infixe du premier arbre: ");
    inorderTraversal(root1);
    printf("\n");

    printf("Parcours infixe du second arbre: ");
    inorderTraversal(root2);
    printf("\n");

    printf("\nRemarque: Les parcours infixes des deux arbres donnent les éléments triés dans le même ordre.\n");

    // 4. Suppression des éléments 5 puis 12 du premier arbre
    printf("\n4. Suppression des éléments 5 puis 12 du premier arbre:\n");
    printf("Arbre avant suppression:\n");
    printTreeTopDown(root1);

    root1 = deleteNode(root1, 5);
    printf("\nAprès suppression de 5:\n");
    printTreeTopDown(root1);

    root1 = deleteNode(root1, 12);
    printf("\nAprès suppression de 12:\n");
    printTreeTopDown(root1);

    // Libération de la mémoire
    // (Une fonction récursive pour libérer tous les nœuds serait nécessaire ici)

    return 0;
}
