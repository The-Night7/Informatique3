// Exercice 2 (Facteurs d’équilibre d’un AVL) (6 pts)
// Soit la structure d’un arbre binaire de type AVL suivante :
// typedef struct avl {
//     int data; // Valeur entière stockée dans le noeud
//     struct avl* fg; // Pointeur vers le fils gauche
//     struct avl* fd; // Pointeur vers le fils droit
//     int equilibre; // facteur d'équilibre de ce noeud
// } AVL;
// Dans la fonction de rotation simple droite d’un arbre de type AVL il existe 2 lignes de code qui mettent à jour le
// facteur d’équilibre du noeud racine de la rotation, et celui du noeud pivot. Ci-dessous se trouve le code partiel de cette
// fonction, avec ces formules mises en évidence :
// AVL* rotationSimpleDroite(AVL* racine){
//     ...
//     AVL* pivot = ...
//     ...
//     eqRac = racine->equilibre;
//     eqPiv = pivot->equilibre;
//     ...
//     // Mise a jour du facteur d'équilibre de la racine
//     racine->equilibre = eqRac - min(eqPiv, 0) + 1;
//     // Mise a jour du facteur d'équilibre du pivot
//     pivot->equilibre = max( eqRac + 2, eqRac + eqPiv + 2, eqPiv + 1 );
//     ...
//     }
// Démontrer que ces formules effectuent correctement la modification des facteurs d’équilibre de la racine et du pivot pour
// une rotation simple droite, et ceci dans tous les cas de figure.
// Pour cette démonstration vous pouvez utiliser ce qui vous semble le plus pertinent pour la compréhension du lecteur :
// phrases, schémas, ...

// Exercice 2 (Facteurs d'équilibre d'un AVL) (6 pts)
#include <stdio.h>
#include <stdlib.h>

// Structure d'un arbre binaire de type AVL
typedef struct avl {
    int data; // Valeur entière stockée dans le noeud
    struct avl* fg; // Pointeur vers le fils gauche
    struct avl* fd; // Pointeur vers le fils droit
    int equilibre; // facteur d'équilibre de ce noeud
} AVL;

// Fonctions utilitaires
int max(int a, int b) {
    return (a > b) ? a : b;
}

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fonction pour créer un nouveau nœud AVL
AVL* creerNoeud(int data) {
    AVL* nouveauNoeud = (AVL*)malloc(sizeof(AVL));
    if (nouveauNoeud == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveauNoeud->data = data;
    nouveauNoeud->fg = NULL;
    nouveauNoeud->fd = NULL;
    nouveauNoeud->equilibre = 0; // Nœud initialement équilibré
    return nouveauNoeud;
}

// Fonction de rotation simple droite
AVL* rotationSimpleDroite(AVL* racine) {
    // Vérifier si la racine existe et si elle a un fils gauche
    if (racine == NULL || racine->fg == NULL) {
        return racine;
    }

    // Sauvegarde du pivot (fils gauche de la racine)
    AVL* pivot = racine->fg;

    // Sauvegarde des facteurs d'équilibre actuels
    int eqRac = racine->equilibre;
    int eqPiv = pivot->equilibre;

    // Mise à jour des liens entre les nœuds
    racine->fg = pivot->fd;
    pivot->fd = racine;

    // Mise à jour du facteur d'équilibre de la racine selon la formule
    racine->equilibre = eqRac - min(eqPiv, 0) + 1;

    // Mise à jour du facteur d'équilibre du pivot selon la formule
    pivot->equilibre = max3(eqRac + 2, eqRac + eqPiv + 2, eqPiv + 1);

    // Le pivot devient la nouvelle racine
    return pivot;
}

// Fonction pour effectuer une rotation simple gauche
AVL* rotationSimpleGauche(AVL* racine) {
    if (racine == NULL || racine->fd == NULL) {
        return racine;
    }

    AVL* pivot = racine->fd;
    int eqRac = racine->equilibre;
    int eqPiv = pivot->equilibre;

    racine->fd = pivot->fg;
    pivot->fg = racine;

    // Mise à jour du facteur d'équilibre de la racine
    racine->equilibre = eqRac - max(eqPiv, 0) - 1;

    // Mise à jour du facteur d'équilibre du pivot
    pivot->equilibre = min(eqRac - 2, eqRac + eqPiv - 2, eqPiv - 1);

    return pivot;
}

// Fonction pour insérer un nœud dans un AVL (avec rééquilibrage)
AVL* inserer(AVL* racine, int valeur) {
    // Insertion standard dans un ABR
    if (racine == NULL) {
        return creerNoeud(valeur);
    }

    if (valeur < racine->data) {
        racine->fg = inserer(racine->fg, valeur);
        racine->equilibre++; // Augmenter le facteur d'équilibre car côté gauche augmente
    } else if (valeur > racine->data) {
        racine->fd = inserer(racine->fd, valeur);
        racine->equilibre--; // Diminuer le facteur d'équilibre car côté droit augmente
    } else {
        // Valeur déjà dans l'arbre
        return racine;
    }

    // Rééquilibrage de l'arbre si nécessaire
    if (racine->equilibre > 1) {
        // Déséquilibre gauche
        if (racine->fg->equilibre < 0) {
            // Double rotation gauche-droite (cas LR)
            racine->fg = rotationSimpleGauche(racine->fg);
        }
        // Simple rotation droite (cas LL)
        return rotationSimpleDroite(racine);
    } else if (racine->equilibre < -1) {
        // Déséquilibre droit
        if (racine->fd->equilibre > 0) {
            // Double rotation droite-gauche (cas RL)
            racine->fd = rotationSimpleDroite(racine->fd);
        }
        // Simple rotation gauche (cas RR)
        return rotationSimpleGauche(racine);
    }

    return racine;
}

// Fonction pour afficher l'arbre (parcours infixe avec indentation)
void afficherArbre(AVL* racine, int niveau) {
    if (racine != NULL) {
        afficherArbre(racine->fd, niveau + 1);

        for (int i = 0; i < niveau; i++) {
            printf("    ");
        }
        printf("%d (eq:%d)\n", racine->data, racine->equilibre);

        afficherArbre(racine->fg, niveau + 1);
    }
}

// Fonction principale pour tester
int main() {
    AVL* racine = NULL;

    // Test d'insertion et rotation
    racine = inserer(racine, 50);
    racine = inserer(racine, 30);
    racine = inserer(racine, 20); // Devrait déclencher une rotation

    printf("Arbre AVL après insertions:\n");
    afficherArbre(racine, 0);

    // Test direct de rotation
    printf("\nTest direct de rotation simple droite:\n");
    AVL* testRacine = creerNoeud(50);
    testRacine->fg = creerNoeud(30);
    testRacine->fg->fg = creerNoeud(20);
    testRacine->equilibre = 2;  // Déséquilibré à gauche
    testRacine->fg->equilibre = 1;  // Déséquilibré à gauche

    printf("Avant rotation:\n");
    afficherArbre(testRacine, 0);

    testRacine = rotationSimpleDroite(testRacine);

    printf("Après rotation:\n");
    afficherArbre(testRacine, 0);

    return 0;
}