#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// 1. Créer une liste de 10 éléments aléatoires entre 0 et 5
Chainon* creerListeAleatoire() {
    Chainon* liste = NULL;
    srand(time(NULL));
    
    for (int i = 0; i < 10; i++) {
        int valeur = rand() % 6; // 0 à 5 inclus
        insertFin(&liste, valeur);
    }
    
    return liste;
}

// 2a. Supprimer le premier chaînon avec la valeur donnée
Chainon* supprimerPremier(Chainon* pliste, int valeur) {
    if (pliste == NULL) return NULL;
    
    // Si c'est le premier élément
    if (pliste->valeur == valeur) {
        Chainon* temp = pliste;
        pliste = pliste->suivant;
        free(temp);
        return pliste;
    }
    
    // Chercher dans le reste de la liste
    Chainon* current = pliste;
    while (current->suivant != NULL && current->suivant->valeur != valeur) {
        current = current->suivant;
    }
    
    // Si trouvé, supprimer
    if (current->suivant != NULL) {
        Chainon* temp = current->suivant;
        current->suivant = temp->suivant;
        free(temp);
    } else {
        printf("Valeur absente de la liste.");
    }
    
    return pliste;
}

// 2b. Supprimer tous les chaînons avec la valeur donnée
Chainon* supprimerTous(Chainon* pliste, int valeur) {
    // Supprimer tous les éléments en début de liste
    while (pliste != NULL && pliste->valeur == valeur) {
        Chainon* temp = pliste;
        pliste = pliste->suivant;
        free(temp);
    }
    
    if (pliste == NULL) return NULL;
    
    // Supprimer dans le reste de la liste
    Chainon* current = pliste;
    while (current->suivant != NULL) {
        if (current->suivant->valeur == valeur) {
            Chainon* temp = current->suivant;
            current->suivant = temp->suivant;
            free(temp);
        } else {
            current = current->suivant;
        }
    }
    
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
            printf(" -> ");
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
    printf("=== Suppression de chaînons ===\n");
    
    // 1. Créer une liste aléatoire
    Chainon* liste = creerListeAleatoire();
    printf("Liste initiale : ");
    afficheListe(liste);
    
    // Test suppression du premier
    int valeur = 3;
    printf("\nSuppression du premier %d :\n", valeur);
    liste = supprimerPremier(liste, valeur);
    afficheListe(liste);
    
    // Recréer la liste pour le test suivant
    libererListe(liste);
    liste = creerListeAleatoire();
    printf("\nNouvelle liste : ");
    afficheListe(liste);
    
    // Test suppression de tous
    printf("\nSuppression de tous les %d :\n", valeur);
    liste = supprimerTous(liste, valeur);
    afficheListe(liste);
    
    libererListe(liste);
    return 0;
}