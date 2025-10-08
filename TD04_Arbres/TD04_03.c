/* Un arbre binaire est dit filiforme si chaque nœud a au plus un seul fils (qu'il soit gauche ou droit).
 * — A quoi va ressembler un tel arbre ?
 *   Un arbre filiforme ressemble à une liste chaînée, où chaque nœud a au plus un fils.
 *   Il forme une sorte de "fil" ou de chemin unique.
 *
 * — Écrire une fonction permettant de determiner si un arbre est filiforme (plusieurs méthodes sont possibles !).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Structure d'un nœud d'arbre binaire
typedef struct Noeud {
    int valeur;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud;

typedef Noeud* Arbre;

// Fonction pour créer un nouveau nœud
Noeud* nouveauNoeud(int valeur) {
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    noeud->valeur = valeur;
    noeud->gauche = NULL;
    noeud->droite = NULL;
    return noeud;
}

// Fonction pour déterminer si un arbre est filiforme (méthode récursive)
bool estFiliforme(Arbre a) {
    if (a == NULL) return true;

    // Si les deux fils existent, l'arbre n'est pas filiforme
    if (a->gauche != NULL && a->droite != NULL) return false;

    // Vérifier récursivement pour les sous-arbres
    if (a->gauche != NULL) return estFiliforme(a->gauche);
    if (a->droite != NULL) return estFiliforme(a->droite);

    return true;
}

/* — Un arbre est dit peigne gauche si les nœuds n'ont qu'un fils gauche et pas de fils droit.
 * — Écrire une fonction permettant de determiner si un arbre est peigne gauche.
 */

bool estPeigneGauche(Arbre a) {
    if (a == NULL) return true;

    // Si un nœud a un fils droit, ce n'est pas un peigne gauche
    if (a->droite != NULL) return false;

    // Vérifier récursivement pour le sous-arbre gauche
    return estPeigneGauche(a->gauche);
}

/* — Écrire une fonction parbre constrPeigneGauche(int h) qui va créer un arbre peigne gauche de hauteur h en le
 * remplissant avec des valeurs aléatoires entre 0 et 10. L'afficher.
 */

// Fonction pour afficher un arbre (parcours infixe)
void afficherArbre(Arbre a, int niveau) {
    if (a != NULL) {
        afficherArbre(a->droite, niveau + 1);
        for (int i = 0; i < niveau; i++) printf("    ");
        printf("%d\n", a->valeur);
        afficherArbre(a->gauche, niveau + 1);
    }
}

Arbre constrPeigneGauche(int h) {
    if (h <= 0) return NULL;

    // Initialiser le générateur de nombres aléatoires
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }

    // Créer le nœud racine avec une valeur aléatoire
    Arbre racine = nouveauNoeud(rand() % 11); // Valeur entre 0 et 10

    // Construire récursivement le reste du peigne gauche
    Noeud* courant = racine;
    for (int i = 1; i < h; i++) {
        courant->gauche = nouveauNoeud(rand() % 11);
        courant = courant->gauche;
    }

    return racine;
}

// Fonction pour libérer la mémoire d'un arbre
void libererArbre(Arbre a) {
    if (a != NULL) {
        libererArbre(a->gauche);
        libererArbre(a->droite);
        free(a);
    }
}

// Fonction principale pour tester les fonctions
int main() {
    // Test de la fonction constrPeigneGauche
    printf("Construction d'un peigne gauche de hauteur 5:\n");
    Arbre peigneGauche = constrPeigneGauche(5);
    afficherArbre(peigneGauche, 0);

    // Vérification
    printf("\nEst-ce que l'arbre est filiforme? %s\n",
           estFiliforme(peigneGauche) ? "Oui" : "Non");
    printf("Est-ce que l'arbre est un peigne gauche? %s\n",
           estPeigneGauche(peigneGauche) ? "Oui" : "Non");

    // Libération de la mémoire
    libererArbre(peigneGauche);

    return 0;
}
