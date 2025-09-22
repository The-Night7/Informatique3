#include <stdio.h>
#include <stdlib.h>

// 1. Structure Chainon
typedef struct Chainon {
    int valeur;
    struct Chainon* suivant;
} Chainon;

// 2. Fonction de création d'un chaînon
Chainon* creationChainon(int a) {
    Chainon* nouveau = (Chainon*)malloc(sizeof(Chainon));
    if (nouveau != NULL) {
        nouveau->valeur = a;
        nouveau->suivant = NULL;
    }
    return nouveau;
}

// 3. Insertion en début de liste
Chainon* insertDebut(Chainon* pliste, int a) {
    Chainon* nouveau = creationChainon(a);
    if (nouveau != NULL) {
        nouveau->suivant = pliste;
        return nouveau;
    }
    return pliste;
}

// 4. Insertion en fin de liste
void insertFin(Chainon** pliste, int a) {
    Chainon* nouveau = creationChainon(a);
    if (nouveau == NULL) return;
    
    if (*pliste == NULL) {
        *pliste = nouveau;
        return;
    }
    
    Chainon* current = *pliste;
    while (current->suivant != NULL) {
        current = current->suivant;
    }
    current->suivant = nouveau;
}

// 5. Afficher les éléments de la Liste Chainée
void afficheListe(Chainon* pliste) {
    if (pliste == NULL) {
        printf("Liste vide\n");
        return;
    }
    
    Chainon* courant = pliste;
    while (courant != NULL) {
        printf("%d", courant->valeur);
        if (courant->suivant != NULL) {
            printf(" -> ");
        }
        courant = courant->suivant;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire et éviter le bourrage papier
void libererListe(Chainon* pliste) {
    while (pliste != NULL) {
        Chainon* temp = pliste;
        pliste = pliste->suivant;
        free(temp);
    }
}

int main() {
    // 6. Initialisation d'un pointeur sur une liste vide
    Chainon* prems = NULL;

    // 7. Programme principal pour les puissances de deux de l'enfer de la mort qui tue genre sérieux c'est quoi ce bordel ????
    int exposant = 1;
    char continuer;
    int puissance = 2; 
    int nb;
    printf("Vous souhaitez afficher jusque quelle puissance de 2 ? (répondre avec un entier représentant l'exposant) ");
    scanf("%d", &nb);

    do {
        puissance = 1 << exposant;
        insertFin(&prems, puissance);
        exposant += 1;
    } while (exposant <= nb);

    printf("=== Liste Chainée des puissances de 2 ===\n"); 

    afficheListe(prems);

    do {
        // Ajouter la puissance de deux actuelle à la fin de la liste
        insertFin(&prems, puissance);
        
        // Afficher la liste
        printf("Liste actuelle : ");
        afficheListe(prems);
        
        // Demander à l'utilisateur s'il veut continuer
        printf("Voulez-vous voir la puissance de deux suivante ? (o/n) : ");
        scanf(" %c", &continuer);
        
        // Calculer la puissance suivante
        puissance *= 2;
        
    } while (continuer == 'o' || continuer == 'O');

    printf("Programme terminé.\n");
    
    // Libérer la mémoire
    libererListe(prems); 
    return 0;
}