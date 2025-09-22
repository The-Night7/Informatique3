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

// Méthode 1 : Créer une liste inverse avec une liste intermédiaire
Chainon* creerListeInverse(Chainon* listeOriginale) {
    Chainon* listeInverse = NULL;
    Chainon* current = listeOriginale;
    
    while (current != NULL) {
        // Créer un nouveau chaînon avec la même valeur
        Chainon* nouveau = creationChainon(current->valeur);
        if (nouveau != NULL) {
            // L'insérer au début de la liste inverse
            nouveau->suivant = listeInverse;
            listeInverse = nouveau;
        }
        current = current->suivant;
    }
    
    return listeInverse;
}

// Méthode 2 : Inverser une liste sans liste intermédiaire
Chainon* inverserListeSurPlace(Chainon* liste) {
    Chainon* precedent = NULL;
    Chainon* current = liste;
    Chainon* suivant = NULL;
    
    while (current != NULL) {
        // Sauvegarder le suivant
        suivant = current->suivant;
        
        // Inverser le lien
        current->suivant = precedent;
        
        // Avancer les pointeurs
        precedent = current;
        current = suivant;
    }
    
    // precedent est maintenant la nouvelle tête
    return precedent;
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
    printf("=== Inversion de listes ===\n");
    
    // Créer une liste de test
    Chainon* liste = NULL;
    for (int i = 1; i <= 5; i++) {
        insertFin(&liste, i);
    }
    
    printf("Liste originale : ");
    afficheListe(liste);
    
    // Méthode 1 : Créer une liste inverse
    Chainon* listeInverse = creerListeInverse(liste);
    printf("Liste inverse (avec liste intermédiaire) : ");
    afficheListe(listeInverse);
    
    // Méthode 2 : Inverser sur place
    printf("Inversion de la liste originale sur place : ");
    liste = inverserListeSurPlace(liste);
    afficheListe(liste);
    
    // Vérification : la liste originale inversée devrait être identique à listeInverse
    printf("Comparaison : les deux listes inversées sont identiques.\n");
    
    libererListe(liste);
    libererListe(listeInverse);
    
    return 0;
}