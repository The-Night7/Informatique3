/* 1. Déclarer un tableau de taille 15 et le remplir avec des valeurs saisies différentes.
 * 2. Construire un ABR à partir de ce tableau
 * 3. Trier ce tableau en vous basant sur un parcours de l'ABR.
 * 4. bonus : reprendre la question 1 mais les valeurs du tableau sont aléatoires entre 0 et 100 et ne doivent pas avoir de
 * doublons !
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAILLE_TABLEAU 15
#define MAX_VALEUR 100

// Définition de la structure de l'ABR
typedef struct Noeud {
    int valeur;
    struct Noeud *gauche;
    struct Noeud *droite;
} Noeud, *pArbre;

// Fonction pour créer un nouveau nœud
pArbre creerNoeud(int valeur) {
    pArbre nouveauNoeud = (pArbre)malloc(sizeof(Noeud));
    if (nouveauNoeud == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    nouveauNoeud->valeur = valeur;
    nouveauNoeud->gauche = NULL;
    nouveauNoeud->droite = NULL;

    return nouveauNoeud;
}

// Fonction pour insérer un élément dans l'ABR
pArbre insererABR(pArbre racine, int valeur) {
    if (racine == NULL) {
        return creerNoeud(valeur);
    }

    if (valeur < racine->valeur) {
        racine->gauche = insererABR(racine->gauche, valeur);
    } else if (valeur > racine->valeur) {
        racine->droite = insererABR(racine->droite, valeur);
    }
    // Si la valeur existe déjà, on ne fait rien

    return racine;
}

// Fonction pour vérifier si une valeur existe dans le tableau
bool valeurExiste(int tableau[], int taille, int valeur) {
    for (int i = 0; i < taille; i++) {
        if (tableau[i] == valeur) {
            return true;
        }
    }
    return false;
}

// Fonction pour parcourir l'ABR en ordre infixe et remplir le tableau trié
void parcoursInfixe(pArbre racine, int tableau[], int *index) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche, tableau, index);
        tableau[(*index)++] = racine->valeur;
        parcoursInfixe(racine->droite, tableau, index);
    }
}

// Fonction pour libérer la mémoire de l'ABR
void libererArbre(pArbre racine) {
    if (racine != NULL) {
        libererArbre(racine->gauche);
        libererArbre(racine->droite);
        free(racine);
    }
}

// Fonction pour afficher le tableau
void afficherTableau(int tableau[], int taille) {
    printf("[ ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("]\n");
}

int main() {
    int tableau[TAILLE_TABLEAU];
    int choix;

    printf("Choisissez comment remplir le tableau :\n");
    printf("1. Saisie manuelle\n");
    printf("2. Valeurs aléatoires sans doublons\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    // 1. Remplir le tableau
    if (choix == 1) {
        // Méthode 1 : Saisie manuelle
        printf("Veuillez entrer %d valeurs différentes :\n", TAILLE_TABLEAU);
        for (int i = 0; i < TAILLE_TABLEAU; i++) {
            int valeur;
            do {
                printf("Entrez la valeur %d : ", i + 1);
                scanf("%d", &valeur);
                if (valeurExiste(tableau, i, valeur)) {
                    printf("Cette valeur existe déjà. Veuillez en saisir une autre.\n");
                }
            } while (valeurExiste(tableau, i, valeur));

            tableau[i] = valeur;
        }
    } else {
        // Méthode 2 (bonus) : Valeurs aléatoires sans doublons
        srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

        for (int i = 0; i < TAILLE_TABLEAU; i++) {
            int valeur;
            do {
                valeur = rand() % (MAX_VALEUR + 1); // Valeur entre 0 et 100
            } while (valeurExiste(tableau, i, valeur));

            tableau[i] = valeur;
        }
    }

    printf("\nTableau original :\n");
    afficherTableau(tableau, TAILLE_TABLEAU);

    // 2. Construire un ABR à partir du tableau
    pArbre racine = NULL;
    for (int i = 0; i < TAILLE_TABLEAU; i++) {
        racine = insererABR(racine, tableau[i]);
    }

    // 3. Trier le tableau en utilisant un parcours infixe de l'ABR
    int index = 0;
    parcoursInfixe(racine, tableau, &index);

    printf("\nTableau trié via ABR :\n");
    afficherTableau(tableau, TAILLE_TABLEAU);

    // Libérer la mémoire
    libererArbre(racine);

    return 0;
}