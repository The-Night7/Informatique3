/* Les versions pseudo-code des fonctions demandées aux question 2,3 et 5 sont dans le cours.
 * 1. Définir la structure permettant de construire un arbre binaire contenant des entiers.
 * 2. Écrire la fonction recherche(pArbre a, int e) indiquant si l'élément e appartient à l'ABR pointé par a.
 * 3. Écrire la fonction recursive insertABR(parbre a, int e) permettant d'inserer l'élément e dans l'ABR. Attention,
 * l'insertion doit respecter les règles des ABR!
 * 4. Écrire une version itérative de la fonction d'insertion écrite précédement.
 * 5. Écrire les fonctions nécessaires à la suppression d'un élément dans un ABR.
 * 6. Creer un ABR et insérer les éléments suivants dans cet ordre : 10, 3, 5, 15, 20, 12, 7, 45, 9. Afficher l'arbre et vérifier
 * qu'il s'agit bien d'un ABR.
 * 7. Vérifier si les élément 13 et 12 appartiennent à l'arbre.
 * 8. Supprimer l'élement 15 et vérifier que l'arbre et toujours un ABR.
 */

#include <stdio.h>
#include <stdlib.h>

/* 1. Définition de la structure d'un noeud d'arbre binaire */
typedef struct noeud {
    int valeur;
    struct noeud *gauche;
    struct noeud *droite;
} Noeud, *pArbre;

/* 2. Fonction de recherche dans un ABR */
int recherche(pArbre a, int e) {
    // Si l'arbre est vide, l'élément n'est pas trouvé
    if (a == NULL) {
        return 0;
    }
    // Si l'élément est trouvé à la racine
    if (a->valeur == e) {
        return 1;
    }
    // Sinon, on cherche dans le sous-arbre approprié
    if (e < a->valeur) {
        return recherche(a->gauche, e);
    } else {
        return recherche(a->droite, e);
    }
}

/* 3. Fonction récursive d'insertion dans un ABR */
pArbre insertABR(pArbre a, int e) {
    // Si l'arbre est vide, on crée un nouveau noeud
    if (a == NULL) {
        pArbre nouveau = (pArbre)malloc(sizeof(Noeud));
        nouveau->valeur = e;
        nouveau->gauche = NULL;
        nouveau->droite = NULL;
        return nouveau;
    }

    // Si l'élément est déjà présent, on ne fait rien
    if (a->valeur == e) {
        return a;
    }

    // Sinon, on insère dans le sous-arbre approprié
    if (e < a->valeur) {
        a->gauche = insertABR(a->gauche, e);
    } else {
        a->droite = insertABR(a->droite, e);
    }

    return a;
}

/* 4. Fonction itérative d'insertion dans un ABR */
pArbre insertABR_iteratif(pArbre a, int e) {
    // Création du nouveau nœud
    pArbre nouveau = (pArbre)malloc(sizeof(Noeud));
    nouveau->valeur = e;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;

    // Si l'arbre est vide, le nouveau nœud devient la racine
    if (a == NULL) {
        return nouveau;
    }

    pArbre courant = a;
    pArbre parent = NULL;

    // Recherche de la position d'insertion
    while (courant != NULL) {
        parent = courant;

        // Si l'élément est déjà présent, on libère le nouveau nœud et on retourne l'arbre inchangé
        if (e == courant->valeur) {
            free(nouveau);
            return a;
        }

        if (e < courant->valeur) {
            courant = courant->gauche;
        } else {
            courant = courant->droite;
        }
    }

    // Insertion du nouveau nœud
    if (e < parent->valeur) {
        parent->gauche = nouveau;
    } else {
        parent->droite = nouveau;
    }

    return a;
}

/* 5. Fonctions nécessaires à la suppression d'un élément dans un ABR */

// Fonction auxiliaire pour trouver le successeur (plus petit élément du sous-arbre droit)
pArbre trouverMin(pArbre a) {
    pArbre courant = a;

    // On descend le plus à gauche possible
    while (courant && courant->gauche != NULL) {
        courant = courant->gauche;
    }

    return courant;
}

// Fonction de suppression d'un élément dans un ABR
pArbre supprimerABR(pArbre a, int e) {
    // Si l'arbre est vide, rien à supprimer
    if (a == NULL) {
        return a;
    }

    // Recherche du nœud à supprimer
    if (e < a->valeur) {
        a->gauche = supprimerABR(a->gauche, e);
    } else if (e > a->valeur) {
        a->droite = supprimerABR(a->droite, e);
    } else {
        // Cas 1: Nœud feuille (sans enfant)
        if (a->gauche == NULL && a->droite == NULL) {
            free(a);
            return NULL;
        }
        // Cas 2: Nœud avec un seul enfant
        else if (a->gauche == NULL) {
            pArbre temp = a->droite;
            free(a);
            return temp;
        } else if (a->droite == NULL) {
            pArbre temp = a->gauche;
            free(a);
            return temp;
        }
        // Cas 3: Nœud avec deux enfants
        else {
            // Trouver le successeur (plus petit élément du sous-arbre droit)
            pArbre successeur = trouverMin(a->droite);

            // Copier la valeur du successeur dans le nœud actuel
            a->valeur = successeur->valeur;

            // Supprimer le successeur
            a->droite = supprimerABR(a->droite, successeur->valeur);
        }
    }

    return a;
}

// Fonction pour afficher l'arbre (parcours infixe)
void afficherInfixe(pArbre a) {
    if (a != NULL) {
        afficherInfixe(a->gauche);
        printf("%d ", a->valeur);
        afficherInfixe(a->droite);
    }
}

// Fonction pour vérifier si un arbre est un ABR
int estABR(pArbre a, int *min, int *max) {
    // Un arbre vide est un ABR
    if (a == NULL) {
        return 1;
    }

    // Vérifie si la valeur du nœud actuel respecte les contraintes
    if ((min != NULL && a->valeur <= *min) || (max != NULL && a->valeur >= *max)) {
        return 0;
    }

    // Vérifie récursivement les sous-arbres
    return estABR(a->gauche, min, &(a->valeur)) && estABR(a->droite, &(a->valeur), max);
}

// Fonction principale pour vérifier si un arbre est un ABR
int verifierABR(pArbre a) {
    return estABR(a, NULL, NULL);
}

int main() {
    // 6. Création d'un ABR et insertion des éléments
    pArbre arbre = NULL;
    int elements[] = {10, 3, 5, 15, 20, 12, 7, 45, 9};
    int nbElements = sizeof(elements) / sizeof(elements[0]);

    printf("6. Création de l'ABR avec les éléments: ");
    for (int i = 0; i < nbElements; i++) {
        printf("%d ", elements[i]);
        arbre = insertABR(arbre, elements[i]);
    }
    printf("\n");

    printf("Affichage de l'arbre (parcours infixe): ");
    afficherInfixe(arbre);
    printf("\n");

    printf("Est-ce un ABR? %s\n", verifierABR(arbre) ? "Oui" : "Non");

    // 7. Vérification de l'appartenance des éléments 13 et 12
    printf("\n7. Vérification d'appartenance:\n");
    printf("13 appartient à l'arbre? %s\n", recherche(arbre, 13) ? "Oui" : "Non");
    printf("12 appartient à l'arbre? %s\n", recherche(arbre, 12) ? "Oui" : "Non");

    // 8. Suppression de l'élément 15
    printf("\n8. Suppression de l'élément 15:\n");
    arbre = supprimerABR(arbre, 15);

    printf("Affichage de l'arbre après suppression (parcours infixe): ");
    afficherInfixe(arbre);
    printf("\n");

    printf("Est-ce toujours un ABR? %s\n", verifierABR(arbre) ? "Oui" : "Non");

    return 0;
}
