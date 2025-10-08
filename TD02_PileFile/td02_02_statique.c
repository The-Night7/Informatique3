#include <stdio.h>

#define TAILLE_MAX 100

// 7. Implémentation avec une pile statique
typedef struct {
    int elements[TAILLE_MAX];
    int sommet; // indice du sommet de la pile
} PileStatique;

// Initialisation d'une pile statique
void initialiserPileStatique(PileStatique* ppile) {
    ppile->sommet = -1; // pile vide
}

// Fonction pour empiler un entier sur la pile statique
int empilerStatique(int nb, PileStatique* ppile) {
    if (ppile->sommet >= TAILLE_MAX - 1) {
        printf("Erreur: pile pleine\n");
        return 0; // échec
    }
    
    ppile->sommet++;
    ppile->elements[ppile->sommet] = nb;
    return 1; // succès
}

// Procédure pour afficher le contenu d'une pile statique de manière récursive
void affichePileStatiqueRecursif(PileStatique* ppile, int index) {
    if (index < 0) {
        return;
    }
    
    // Afficher d'abord le reste de la pile (récursion)
    affichePileStatiqueRecursif(ppile, index - 1);
    
    // Puis afficher l'élément courant
    printf("%d ", ppile->elements[index]);
}

void affichePileStatique(PileStatique* ppile) {
    if (ppile->sommet == -1) {
        printf("Pile vide\n");
        return;
    }
    
    printf("Contenu de la pile (de la base vers le sommet): ");
    affichePileStatiqueRecursif(ppile, ppile->sommet);
    printf("\n");
}

// Fonction pour dépiler un élément d'une pile statique
int depilerStatique(PileStatique* ppile, int* pnmb) {
    if (ppile->sommet == -1) {
        printf("Erreur: pile vide\n");
        return 0; // échec
    }
    
    *pnmb = ppile->elements[ppile->sommet];
    ppile->sommet--;
    return 1; // succès
}

int main() {
    // Déclaration et remplissage de p1 avec les entiers de 1 à 20
    PileStatique p1;
    initialiserPileStatique(&p1);
    
    printf("Empilage des nombres de 1 à 20 dans p1:\n");
    for (int i = 1; i <= 20; i++) {
        empilerStatique(i, &p1);
        printf("Empilé: %d\n", i);
    }
    
    // Le sommet de la pile sera 20 car c'est le dernier élément empilé
    printf("\nLe sommet de la pile p1 est: %d\n\n", p1.elements[p1.sommet]);
    
    // Affichage de p1
    affichePileStatique(&p1);
    
    // Création et remplissage des piles pilePair et pileImpair
    PileStatique pilePair, pileImpair;
    initialiserPileStatique(&pilePair);
    initialiserPileStatique(&pileImpair);
    
    printf("\nSéparation des éléments pairs et impairs de p1:\n");
    int valeur;
    while (depilerStatique(&p1, &valeur)) {
        if (valeur % 2 == 0) {
            // Nombre pair
            empilerStatique(valeur, &pilePair);
            printf("%d est pair, empilé dans pilePair\n", valeur);
        } else {
            // Nombre impair
            empilerStatique(valeur, &pileImpair);
            printf("%d est impair, empilé dans pileImpair\n", valeur);
        }
    }
    
    printf("\nContenu de pilePair:\n");
    affichePileStatique(&pilePair);
    
    printf("\nContenu de pileImpair:\n");
    affichePileStatique(&pileImpair);
    
    return 0;
}