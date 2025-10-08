#include <stdio.h>
#include <stdlib.h>

// 1. Déclaration de la structure PileDyn pour une pile dynamique d'entiers
typedef struct Element {
    int valeur;
    struct Element* suivant;
} Element;

typedef struct {
    Element* sommet;
} PileDyn;

// 2. Fonction pour empiler un entier sur la pile
void empiler(int nb, PileDyn* ppile) {
    Element* nouvel_element = (Element*)malloc(sizeof(Element));
    if (nouvel_element == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    
    nouvel_element->valeur = nb;
    nouvel_element->suivant = ppile->sommet;
    ppile->sommet = nouvel_element;
}

// 4. Procédure pour afficher le contenu d'une pile de manière récursive
void affichePileRecursif(Element* element) {
    if (element == NULL) {
        return;
    }
    
    // Afficher d'abord le reste de la pile (récursion)
    affichePileRecursif(element->suivant);
    
    // Puis afficher l'élément courant
    printf("%d ", element->valeur);
}

void affichePile(PileDyn* ppile) {
    if (ppile->sommet == NULL) {
        printf("Pile vide\n");
        return;
    }
    
    printf("Contenu de la pile (du sommet vers la base): ");
    affichePileRecursif(ppile->sommet);
    printf("\n");
}

// 5. Fonction pour dépiler un élément
int depiler(PileDyn* ppile, int* pnmb) {
    if (ppile->sommet == NULL) {
        printf("Erreur: pile vide\n");
        return 0; // échec
    }
    
    Element* element_a_supprimer = ppile->sommet;
    *pnmb = element_a_supprimer->valeur;
    ppile->sommet = element_a_supprimer->suivant;
    free(element_a_supprimer);
    
    return 1; // succès
}

// Fonction d'initialisation d'une pile
void initialiserPile(PileDyn* ppile) {
    ppile->sommet = NULL;
}

int main() {
    // 3. Déclaration et remplissage de p1 avec les entiers de 1 à 20
    PileDyn p1;
    initialiserPile(&p1);
    
    printf("Empilage des nombres de 1 à 20 dans p1:\n");
    for (int i = 1; i <= 20; i++) {
        empiler(i, &p1);
        printf("Empilé: %d\n", i);
    }
    
    // Le sommet de la pile sera 20 car c'est le dernier élément empilé
    printf("\nLe sommet de la pile p1 est: %d\n\n", p1.sommet->valeur);
    
    // 4. Affichage de p1
    affichePile(&p1);
    
    // 6. Création et remplissage des piles pilePair et pileImpair
    PileDyn pilePair, pileImpair;
    initialiserPile(&pilePair);
    initialiserPile(&pileImpair);
    
    printf("\nSéparation des éléments pairs et impairs de p1:\n");
    int valeur;
    while (depiler(&p1, &valeur)) {
        if (valeur % 2 == 0) {
            // Nombre pair
            empiler(valeur, &pilePair);
            printf("%d est pair, empilé dans pilePair\n", valeur);
        } else {
            // Nombre impair
            empiler(valeur, &pileImpair);
            printf("%d est impair, empilé dans pileImpair\n", valeur);
        }
    }
    
    printf("\nContenu de pilePair:\n");
    affichePile(&pilePair);
    
    printf("\nContenu de pileImpair:\n");
    affichePile(&pileImpair);
    
    // Libération de la mémoire
    while (pilePair.sommet != NULL) {
        depiler(&pilePair, &valeur);
    }
    
    while (pileImpair.sommet != NULL) {
        depiler(&pileImpair, &valeur);
    }
    
    return 0;
}