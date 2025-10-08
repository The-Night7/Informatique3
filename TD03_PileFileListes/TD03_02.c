/* On souhaite écrire un algorithme qui va pouvoir modéliser le comportement d'un tas de crêpes qui sera trié par un humain
 * (par ordre croissant de diamètre, la plus petite sur le dessus, la plus grande tout en bas du tas).
 * L'humain ne dispose que d'un seul outil pour trier ses crêpes, c'est une spatule qu'il peut insérer entre 2 crêpes (sans les
 * abîmer), et retourner le tas au-dessus de la spatule. Cette opération inverse donc bien la partie supérieure du tas uniquement.
 * Exemple de tri avec une spatule
 *   3
 *   6
 *   2    ____
 *   9 __/
 *   7
 *   4
 * \_5_/
 * En plaçant la spatule entre la crêpe de diamètre 9 (la plus grande) et la crêpe de diamètre 7, on peut inverser l'ordre des
 * crêpes placées au-dessus de la spatule.
 * La crêpe de diamètre le plus grand (9) se retrouve donc au-dessus de la pile comme indiqué ci-dessous :
 *   9
 *   2
 *   6
 *   3
 *   7
 *   4
 * \_5_/
 * Il faut ensuite placer la crêpe 9 tout en bas : pour cela, on réalise la même opération pour tout le tas de crêpes (en plaçant
 * la spatule sous la crêpe de diamètre 5 ici dans l'exemple).
 * Ceci fait nous avons donc, en 2 coups de spatule, la crêpe la plus grande tout en bas, comme indiqué ci-dessous :
 *   5
 *   4
 *   7
 *   3
 *   6
 *   2
 * \_9_/
 * Il ne reste plus qu'à vérifier si le tas de crêpe est correctement trié. Si ce n'est pas le cas, il faut recommencer avec les N-1
 * crêpes supérieures (car la crêpe de diamètre 9 n'a plus besoin d'être touchée, elle est déjà à la bonne place), sinon le tri est
 * terminé.
 *
 * Dans notre algorithme, on définira notre tas de crêpe par une pile d'entiers.
 * 1. Définir une structure Crepe qui contient un entier (le diamètre de la crêpes) et un pointeur vers la crêpe suivante :
 * cette structure nous permet donc d'avoir une liste chainée de crêpes. Définir un également un nouveau type Pcrepe
 * pointeur sur Crepe.
 * 2. Créer une fonction Pcrepe inserFile(Pcrepre tete, Crepe c) qui simule l'insertion d'une crèpe dans une FILE
 * dont la tête est pointée par tete.
 * 3. Créer une fonction Pcrepe suppFile(Pcrepre tete) qui simule le retrait d'une crêpe dans une FILE dont la tête est
 * pointée par tete.
 * 4. Créer une fonction Pcrepe inserPile(Pcrepre tete) qui simule l'insertion d'une crêpe dans une PILE dont la tête
 * est pointée par tete.
 * 5. Créer une fonction Pcrepe suppPile(Pcrepre tete) qui simule le retrait d'une crêpe dans une PILE dont le premier
 * élément est pointé par tete.
 * 6. Créer une fonction int triCrepe(Pcrepre tete) qui retourne 1 si la PILE de crêpes dont la tête est indiquée par
 * tete est triée par ordre croissant, 0 sinon.
 * 7. Créer une fonction Pcrepe invCrepe(Pcrepre tet, int M) qui va inverser les M premiers éléments d'une PILE (on
 * pourra utiliser une FILE temporaire pour cela) et qui retourne la nouvelle tête de la pile.
 * 8. Créer une fonction int indMax(Pcrepe tete) qui retourne l'indice de l'élément le plus grand d'une PILE de crêpe (
 * - 1 si la pile est vide).
 * 9. Créer une fonction Pcrepe spatule(Pcrepre tete, int M) qui va rechercher la crêpe la plus grande parmi les M
 * premiers éléments d'une PILE et qui va inverser ces M éléments. La fonction retourne le pointeur sur la tête de la
 * PILE modifiée.
 * 10. Créer une fonction/procédure qui va utiliser les fonctions précédentes afin de réaliser l'objectif demandé, c'est à dire
 * qu'à partir d'une PILE de crêpes quelconque, on souhaite, une à une dans l'ordre, placer les crêpes les plus grandes
 * tout en bas de la pile. */

#include <stdio.h>
#include <stdlib.h>

// 1. Définition de la structure Crepe et du type Pcrepe
typedef struct Crepe {
    int diametre;
    struct Crepe* suivant;
} Crepe;

typedef Crepe* Pcrepe;

// 2. Insertion d'une crêpe dans une FILE
Pcrepe inserFile(Pcrepe tete, Crepe c) {
    // Création d'une nouvelle crêpe
    Pcrepe nouvelle = (Pcrepe)malloc(sizeof(Crepe));
    if (nouvelle == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }

    nouvelle->diametre = c.diametre;
    nouvelle->suivant = NULL;

    // Si la file est vide, la nouvelle crêpe devient la tête
    if (tete == NULL) {
        return nouvelle;
    }

    // Sinon, on parcourt la file jusqu'à la fin pour ajouter la nouvelle crêpe
    Pcrepe courant = tete;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouvelle;

    return tete;
}

// 3. Suppression d'une crêpe dans une FILE
Pcrepe suppFile(Pcrepe tete) {
    // Si la file est vide, on ne fait rien
    if (tete == NULL) {
        return NULL;
    }

    // On sauvegarde la nouvelle tête de file
    Pcrepe nouvelleTete = tete->suivant;

    // On libère la mémoire de l'ancienne tête
    free(tete);

    return nouvelleTete;
}

// 4. Insertion d'une crêpe dans une PILE
Pcrepe inserPile(Pcrepe tete, Crepe c) {
    // Création d'une nouvelle crêpe
    Pcrepe nouvelle = (Pcrepe)malloc(sizeof(Crepe));
    if (nouvelle == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }

    nouvelle->diametre = c.diametre;

    // La nouvelle crêpe pointe vers l'ancienne tête
    nouvelle->suivant = tete;

    // La nouvelle crêpe devient la nouvelle tête
    return nouvelle;
}

// 5. Suppression d'une crêpe dans une PILE
Pcrepe suppPile(Pcrepe tete) {
    // Si la pile est vide, on ne fait rien
    if (tete == NULL) {
        return NULL;
    }

    // On sauvegarde la nouvelle tête de pile
    Pcrepe nouvelleTete = tete->suivant;

    // On libère la mémoire de l'ancienne tête
    free(tete);

    return nouvelleTete;
}

// 6. Vérification si la PILE est triée par ordre croissant
int triCrepe(Pcrepe tete) {
    // Si la pile est vide ou contient un seul élément, elle est triée
    if (tete == NULL || tete->suivant == NULL) {
        return 1;
    }

    // On parcourt la pile pour vérifier que chaque crêpe est plus petite que celle en dessous
    Pcrepe courant = tete;
    while (courant->suivant != NULL) {
        // Si la crêpe actuelle est plus grande que la suivante, la pile n'est pas triée
        if (courant->diametre > courant->suivant->diametre) {
            return 0;
        }
        courant = courant->suivant;
    }

    // Si on a parcouru toute la pile sans problème, elle est triée
    return 1;
}

// 7. Inversion des M premiers éléments d'une PILE
Pcrepe invCrepe(Pcrepe tete, int M) {
    // Si la pile est vide ou M <= 1, pas besoin d'inversion
    if (tete == NULL || M <= 1) {
        return tete;
    }

    // On utilise une file temporaire pour stocker les M premiers éléments
    Pcrepe file = NULL;
    Pcrepe courant = tete;
    int compteur = 0;

    // On transfère les M premiers éléments de la pile vers la file
    while (courant != NULL && compteur < M) {
        Crepe c = {courant->diametre, NULL};
        file = inserFile(file, c);
        courant = courant->suivant;
        compteur++;
    }

    // On reconstruit la pile avec les éléments inversés
    Pcrepe nouvelleTete = courant; // Le reste de la pile qui n'a pas été modifié

    // On vide la file pour reconstruire le début de la pile (inversé)
    while (file != NULL) {
        Crepe c = {file->diametre, NULL};
        nouvelleTete = inserPile(nouvelleTete, c);
        file = suppFile(file);
    }

    return nouvelleTete;
}

// 8. Recherche de l'indice de l'élément le plus grand parmi les M premiers
int indMax(Pcrepe tete) {
    // Si la pile est vide, on retourne -1
    if (tete == NULL) {
        return -1;
    }

    int maxDiametre = tete->diametre;
    int maxIndice = 0;
    int indiceActuel = 0;

    // On parcourt la pile pour trouver l'élément le plus grand
    Pcrepe courant = tete;
    while (courant != NULL) {
        if (courant->diametre > maxDiametre) {
            maxDiametre = courant->diametre;
            maxIndice = indiceActuel;
        }
        courant = courant->suivant;
        indiceActuel++;
    }

    return maxIndice;
}

// 9. Application de la spatule pour inverser les M premiers éléments
Pcrepe spatule(Pcrepe tete, int M) {
    // Si la pile est vide ou M <= 1, pas besoin d'inversion
    if (tete == NULL || M <= 1) {
        return tete;
    }

    // On cherche l'indice de la plus grande crêpe parmi les M premiers éléments
    int maxIndice = -1;
    int maxDiametre = -1;
    Pcrepe courant = tete;

    for (int i = 0; i < M && courant != NULL; i++) {
        if (courant->diametre > maxDiametre) {
            maxDiametre = courant->diametre;
            maxIndice = i;
        }
        courant = courant->suivant;
    }

    // Si la plus grande crêpe est déjà en haut, pas besoin d'inversion
    if (maxIndice == 0) {
        return tete;
    }

    // Sinon, on inverse les éléments jusqu'à la plus grande crêpe
    tete = invCrepe(tete, maxIndice + 1);

    return tete;
}

// 10. Fonction principale pour trier les crêpes
void triCrepes(Pcrepe* tete) {
    int nbCrepes = 0;
    Pcrepe courant = *tete;

    // On compte le nombre de crêpes
    while (courant != NULL) {
        nbCrepes++;
        courant = courant->suivant;
    }

    // On trie les crêpes une par une
    for (int i = nbCrepes; i > 0; i--) {
        // On place la plus grande crêpe parmi les i premières en haut de la pile
        *tete = spatule(*tete, i);

        // Puis on la place à sa position finale en bas de la pile (inversion complète)
        *tete = invCrepe(*tete, i);
    }
}

// Fonction pour afficher le tas de crêpes
void afficherCrepes(Pcrepe tete) {
    printf("Tas de crêpes (du haut vers le bas):\n");
    while (tete != NULL) {
        printf("%d\n", tete->diametre);
        tete = tete->suivant;
    }
    printf("\n");
}

// Fonction pour créer un tas de crêpes à partir d'un tableau
Pcrepe creerTasCrepes(int diametres[], int taille) {
    Pcrepe tete = NULL;

    // On parcourt le tableau de la fin vers le début pour empiler les crêpes
    for (int i = taille - 1; i >= 0; i--) {
        Crepe c = {diametres[i], NULL};
        tete = inserPile(tete, c);
    }

    return tete;
}

// Fonction principale pour tester
int main()
{
    int diametres[] = {3, 6, 2, 9, 7, 4, 5};
    int taille = sizeof(diametres) / sizeof(diametres[0]);

    Pcrepe tasCrepes = creerTasCrepes(diametres, taille);

    printf("Tas de crêpes initial:\n");
    afficherCrepes(tasCrepes);

    printf("Tri en cours...\n");
    triCrepes(&tasCrepes);

    printf("Tas de crêpes trié:\n");
    afficherCrepes(tasCrepes);

    // Vérification du tri
    if (triCrepe(tasCrepes)) {
        printf("Le tas est correctement trié!\n");
    } else {
        printf("Erreur: le tas n'est pas trié correctement.\n");
    }

    // Libération de la mémoire
    while (tasCrepes != NULL) {
        tasCrepes = suppPile(tasCrepes);
    }

    return 0;
}