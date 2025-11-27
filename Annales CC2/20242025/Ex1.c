// Exercice 1 (Opérations sur des ABR) (6 pts)
// 1. Ecrire la fonction d'insertion d'un élément dans un ABR
// 2. Ecrire une fonction qui prend deux ABR en paramètre et qui va créer et retourner l'adresse d' un troisième arbre
// comportant toutes les valeurs des deux premiers (les éléments peuvent être ajoutés dans n'importe quel ordre tant que
// l'arbre final contient bien toute les valeurs des deux arbres d'origine).

#include <stdio.h>
#include <stdlib.h>  // Ajout pour malloc

// Dans tous les exercices suivants, nous considérons un arbre binaire représenté par la structure suivante en langage C :
typedef struct Arbre {
    int data; // Valeur entière stockée dans le noeud
    struct Arbre* fg; // Pointeur vers le fils gauche
    struct Arbre* fd; // Pointeur vers le fils droit
} Arbre;

// 1. Fonction d'insertion d'un élément dans un ABR
Arbre* inserer(Arbre* racine, int valeur) {
    // Si l'arbre est vide, créer un nouveau nœud
    if (racine == NULL) {
        Arbre* nouveau = (Arbre*)malloc(sizeof(Arbre));
        if (nouveau == NULL) {
            // Gestion d'erreur d'allocation
            return NULL;
        }
        nouveau->data = valeur;
        nouveau->fg = NULL;
        nouveau->fd = NULL;
        return nouveau;
    }

    // Si la valeur est inférieure à la racine, insérer dans le sous-arbre gauche
    if (valeur < racine->data) {
        racine->fg = inserer(racine->fg, valeur);
    }
    // Si la valeur est supérieure à la racine, insérer dans le sous-arbre droit
    else if (valeur > racine->data) {
        racine->fd = inserer(racine->fd, valeur);
    }
    // Si la valeur est égale, ne rien faire (pas de doublons dans un ABR)

    return racine;
}

// Fonction auxiliaire pour parcourir un ABR et insérer tous ses éléments dans un autre ABR en utilisant le parcours infoxe
void insererTousElements(Arbre** destination, Arbre* source) {
    if (source == NULL) {
        return;
    }

    // Parcours infixe pour insérer tous les éléments
    insererTousElements(destination, source->fg);
    *destination = inserer(*destination, source->data);
    insererTousElements(destination, source->fd);
}

// 2. Fonction qui fusionne deux ABR
Arbre* fusionnerABR(Arbre* arbre1, Arbre* arbre2) {
    // Création d'un nouvel arbre vide
    Arbre* resultat = NULL;

    // Insérer tous les éléments du premier arbre
    insererTousElements(&resultat, arbre1);

    // Insérer tous les éléments du deuxième arbre
    insererTousElements(&resultat, arbre2);

    return resultat;
}