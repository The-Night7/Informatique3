#include <stdio.h>
#include <stdlib.h>

typedef struct Chainon {
    int valeur;
    struct Chainon* suivant;
} Chainon;

Chainon* creationChainon(int a) {
    Chainon* nouveau = (Chainon*)malloc(sizeof(Chainon));
    if (nouveau != NULL) {
        nouveau->valeur = a;
        nouveau->suivant = NULL;
    }
    return nouveau;
}

Chainon* insertion(Chainon* pliste, int a) {
    Chainon* nouveau = creationChainon(a);
    if (nouveau == NULL) return pliste;
    
    // Si la liste est vide ou si la valeur est plus petite que le premier élément
    if (pliste == NULL || a < pliste->valeur) {
        nouveau->suivant = pliste;
        return nouveau;
    }
    
    // Chercher la position d'insertion
    Chainon* current = pliste;
    while (current->suivant != NULL && current->suivant->valeur < a) {
        current = current->suivant;
    }
    
    // Insérer le nouveau chaînon
    nouveau->suivant = current->suivant;
    current->suivant = nouveau;
    
    return pliste;
}

void afficheListe(Chainon* pliste) {
    if (pliste == NULL) {
        printf("Liste vide\n");
        return;
    }
    
    Chainon* current = pliste;
    while (current != NULL) {
        printf("%d", current->valeur);
        if (current->suivant != NULL) {
            printf(" <= ");
        }
        current = current->suivant;
    }
    printf("\n");
}

void libererListe(Chainon* pliste) {
    while (pliste != NULL) {
        Chainon* temp = pliste;
        pliste = pliste->suivant;
        free(temp);
    }
}

int main() {
    Chainon* liste = NULL;
    int valeur;
    char continuer;
    
    printf("=== Insertion dans une liste triée dans l'ordre croissant ===\n");
    
    do {
        printf("Entrez une valeur à insérer : ");
        scanf("%d", &valeur);
        
        liste = insertion(liste, valeur);
        
        printf("Liste triée : ");
        afficheListe(liste);
        
        printf("Voulez-vous ajouter un autre élément ? (o/n) : ");
        scanf(" %c", &continuer);
        
    } while (continuer == 'o' || continuer == 'O');
    
    libererListe(liste);
    return 0;
}