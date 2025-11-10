/*
 * Reprendre les questions de l'exercice 1 et construire les AVL demandés grâce aux fonctions écrites dans le TD. A chaque
 * étape (ajout ou suppression), afficher l'arbre avec la fonction affArbreGraphique qui a été fournie.
 */
#include <stdio.h>
#include <stdlib.h>

// Définition du type Element (entier)
typedef int Element;

// Structure de l'arbre AVL avec facteur d'équilibrage
typedef struct noeud {
    Element elt;
    int equilibre;  // facteur d'équilibrage
    struct noeud* gauche;
    struct noeud* droit;
} Noeud, *Arbre;

// Création d'un noeud d'arbre
Arbre creerArbre(Element x) {
    Arbre a = (Arbre)malloc(sizeof(Noeud));
    if (a == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    a->elt = x;
    a->equilibre = 0;  // Initialisation du facteur d'équilibrage
    a->gauche = NULL;
    a->droit = NULL;
    return a;
}

// Rotation gauche d'un arbre
Arbre RotationGauche(Arbre A) {
    Arbre pivot = A->droit;
    A->droit = pivot->gauche;
    pivot->gauche = A;

    // Mise à jour des facteurs d'équilibrage
    A->equilibre = A->equilibre - 1 - (pivot->equilibre > 0 ? pivot->equilibre : 0);
    pivot->equilibre = pivot->equilibre - 1 + (A->equilibre < 0 ? -A->equilibre : 0);

    return pivot;
}

// Rotation droite d'un arbre
Arbre RotationDroite(Arbre A) {
    Arbre pivot = A->gauche;
    A->gauche = pivot->droit;
    pivot->droit = A;

    // Mise à jour des facteurs d'équilibrage
    A->equilibre = A->equilibre + 1 - (pivot->equilibre < 0 ? -pivot->equilibre : 0);
    pivot->equilibre = pivot->equilibre + 1 + (A->equilibre > 0 ? A->equilibre : 0);

    return pivot;
}

// Double rotation droite
Arbre DoubleRotationDroite(Arbre A) {
    A->gauche = RotationGauche(A->gauche);
    return RotationDroite(A);
}

// Double rotation gauche
Arbre DoubleRotationGauche(Arbre A) {
    A->droit = RotationDroite(A->droit);
    return RotationGauche(A);
}

// Équilibrage d'un AVL
Arbre equilibrerAVL(Arbre A) {
    if (A->equilibre >= 2) { // Déséquilibre à droite
        if (A->droit->equilibre <= -1) {
            // Double rotation gauche
            return DoubleRotationGauche(A);
        } else {
            // Rotation gauche simple
            return RotationGauche(A);
        }
    } else if (A->equilibre <= -2) { // Déséquilibre à gauche
        if (A->gauche->equilibre >= 1) {
            // Double rotation droite
            return DoubleRotationDroite(A);
        } else {
            // Rotation droite simple
            return RotationDroite(A);
        }
    }
    return A; // Arbre déjà équilibré
}

// Insertion dans un AVL
Arbre insertionAVL(Arbre A, Element e, int* h) {
    if (A == NULL) {
        *h = 1; // La hauteur a augmenté
        return creerArbre(e);
    }

    if (e < A->elt) {
        A->gauche = insertionAVL(A->gauche, e, h);
        if (*h) { // Si la hauteur du sous-arbre gauche a augmenté
            A->equilibre--;
            if (A->equilibre == 0) {
                *h = 0; // L'arbre est équilibré, la hauteur n'a pas changé
            } else if (A->equilibre == -2) {
                A = equilibrerAVL(A);
                *h = 0; // Après rééquilibrage, la hauteur n'a pas changé
            }
        }
    } else if (e > A->elt) {
        A->droit = insertionAVL(A->droit, e, h);
        if (*h) { // Si la hauteur du sous-arbre droit a augmenté
            A->equilibre++;
            if (A->equilibre == 0) {
                *h = 0; // L'arbre est équilibré, la hauteur n'a pas changé
            } else if (A->equilibre == 2) {
                A = equilibrerAVL(A);
                *h = 0; // Après rééquilibrage, la hauteur n'a pas changé
            }
        }
    } else {
        // L'élément existe déjà, pas d'insertion
        *h = 0;
    }

    return A;
}

// Fonction auxiliaire pour la suppression (trouver et supprimer le minimum d'un sous-arbre)
Arbre suppMin(Arbre A, Element* e, int* h) {
    if (A->gauche == NULL) {
        *e = A->elt;
        Arbre temp = A->droit;
        free(A);
        *h = 1; // La hauteur a diminué
        return temp;
    }

    A->gauche = suppMin(A->gauche, e, h);
    if (*h) {
        A->equilibre++;
        if (A->equilibre == 1) {
            *h = 0;
        } else if (A->equilibre == 2) {
            A = equilibrerAVL(A);
            *h = (A->equilibre == 0);
        }
    }

    return A;
}

// Suppression dans un AVL
Arbre suppAVL(Arbre A, Element e, int* h) {
    if (A == NULL) {
        *h = 0;
        return NULL;
    }

    if (e < A->elt) {
        A->gauche = suppAVL(A->gauche, e, h);
        if (*h) {
            A->equilibre++;
            if (A->equilibre == 1) {
                *h = 0;
            } else if (A->equilibre == 2) {
                A = equilibrerAVL(A);
                *h = (A->equilibre == 0);
            }
        }
    } else if (e > A->elt) {
        A->droit = suppAVL(A->droit, e, h);
        if (*h) {
            A->equilibre--;
            if (A->equilibre == -1) {
                *h = 0;
            } else if (A->equilibre == -2) {
                A = equilibrerAVL(A);
                *h = (A->equilibre == 0);
            }
        }
    } else {
        // Noeud à supprimer trouvé
        if (A->gauche == NULL) {
            Arbre temp = A->droit;
            free(A);
            *h = 1;
            return temp;
        } else if (A->droit == NULL) {
            Arbre temp = A->gauche;
            free(A);
            *h = 1;
            return temp;
        } else {
            // Noeud avec deux fils, on remplace par le minimum du sous-arbre droit
            Element min;
            A->droit = suppMin(A->droit, &min, h);
            A->elt = min;
            if (*h) {
                A->equilibre--;
                if (A->equilibre == -1) {
                    *h = 0;
                } else if (A->equilibre == -2) {
                    A = equilibrerAVL(A);
                    *h = (A->equilibre == 0);
                }
            }
        }
    }

    return A;
}

// Fonction pour afficher l'arbre de façon graphique
void affArbreGraphique(Arbre A, int niveau) {
    int i;
    if (A != NULL) {
        affArbreGraphique(A->droit, niveau + 1);
        for (i = 0; i < niveau; i++)
            printf("    ");
        printf("%d (%d)\n", A->elt, A->equilibre);
        affArbreGraphique(A->gauche, niveau + 1);
    }
}

// Parcours infixe de l'arbre
void parcoursInfixe(Arbre A) {
    if (A != NULL) {
        parcoursInfixe(A->gauche);
        printf("%d ", A->elt);
        parcoursInfixe(A->droit);
    }
}

// Fonction pour libérer la mémoire d'un arbre
void libererArbre(Arbre A) {
    if (A != NULL) {
        libererArbre(A->gauche);
        libererArbre(A->droit);
        free(A);
    }
}

int main() {
    Arbre arbre1 = NULL;
    Arbre arbre2 = NULL;
    int h = 0;

    // 1. Construction du premier AVL (10, 3, 5, 15, 20, 12, 7, 9)
    printf("1. Construction du premier AVL:\n");

    arbre1 = insertionAVL(arbre1, 10, &h);
    printf("Après insertion de 10:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 3, &h);
    printf("Après insertion de 3:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 5, &h);
    printf("Après insertion de 5 (rotation gauche-droite):\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 15, &h);
    printf("Après insertion de 15:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 20, &h);
    printf("Après insertion de 20 (rotation gauche):\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 12, &h);
    printf("Après insertion de 12:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 7, &h);
    printf("Après insertion de 7:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    arbre1 = insertionAVL(arbre1, 9, &h);
    printf("Après insertion de 9:\n");
    affArbreGraphique(arbre1, 0);
    printf("\n");

    // 2. Construction du deuxième AVL (ordre inverse)
    printf("2. Construction du second AVL (ordre inverse):\n");

    arbre2 = insertionAVL(arbre2, 9, &h);
    printf("Après insertion de 9:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 7, &h);
    printf("Après insertion de 7:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 12, &h);
    printf("Après insertion de 12:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 20, &h);
    printf("Après insertion de 20:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 15, &h);
    printf("Après insertion de 15:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 5, &h);
    printf("Après insertion de 5:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 3, &h);
    printf("Après insertion de 3:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    arbre2 = insertionAVL(arbre2, 10, &h);
    printf("Après insertion de 10:\n");
    affArbreGraphique(arbre2, 0);
    printf("\n");

    // 3. Parcours infixe des deux arbres
    printf("3. Parcours infixe des deux arbres:\n");
    printf("Parcours infixe du premier arbre: ");
    parcoursInfixe(arbre1);
    printf("\n");

    printf("Parcours infixe du deuxième arbre: ");
    parcoursInfixe(arbre2);
    printf("\n");

    printf("Remarque: On constate que les parcours infixes des deux arbres donnent les éléments\n");
    printf("dans l'ordre croissant, malgré des structures d'arbres différentes.\n\n");

    // 4. Suppression de 5 puis 12 du premier arbre
    printf("4. Suppressions dans le premier arbre:\n");

    printf("Suppression de 5:\n");
    arbre1 = suppAVL(arbre1, 5, &h);
    affArbreGraphique(arbre1, 0);
    printf("\n");

    printf("Suppression de 12:\n");
    arbre1 = suppAVL(arbre1, 12, &h);
    affArbreGraphique(arbre1, 0);
    printf("\n");

    // Libération de la mémoire
    libererArbre(arbre1);
    libererArbre(arbre2);

    return 0;
}
