#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10  // Nombre de notes par étudiant
#define MAX_NOM 50

// 1. Structure Etudiant
typedef struct {
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    int groupe;
    int notes[N];
} Etudiant;

// 2. Structure pour la liste dynamique
typedef struct ChainonEtudiant {
    Etudiant etudiant;
    struct ChainonEtudiant* suivant;
} ChainonEtudiant;

typedef ChainonEtudiant* LstEtudiants;

// 3. Fonction pour saisir un étudiant et l'ajouter à la fin
void saisirEtudiant(LstEtudiants* lst) {
    ChainonEtudiant* nouveau = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    
    printf("Nom de l'étudiant : ");
    scanf("%s", nouveau->etudiant.nom);
    
    printf("Prénom de l'étudiant : ");
    scanf("%s", nouveau->etudiant.prenom);
    
    printf("Groupe de l'étudiant : ");
    scanf("%d", &nouveau->etudiant.groupe);
    
    // Générer des notes aléatoires entre 0 et 20
    printf("Génération de %d notes aléatoires...\n", N);
    for (int i = 0; i < N; i++) {
        nouveau->etudiant.notes[i] = rand() % 21; // 0 à 20
    }
    
    nouveau->suivant = NULL;
    
    // Ajouter à la fin de la liste
    if (*lst == NULL) {
        *lst = nouveau;
    } else {
        ChainonEtudiant* courant = *lst;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
    
    printf("Étudiant ajouté avec succès!\n");
}

// 4. Procédure pour lister les étudiants d'un groupe
void listeParGroupe(LstEtudiants lst, int groupe) {
    printf("=== Étudiants du groupe %d ===\n", groupe);
    ChainonEtudiant* courant = lst;
    int trouve = 0;
    
    while (courant != NULL) {
        if (courant->etudiant.groupe == groupe) {
            printf("- %s %s\n", courant->etudiant.prenom, courant->etudiant.nom);
            trouve = 1;
        }
        courant = courant->suivant;
    }
    
    if (!trouve) {
        printf("Aucun étudiant trouvé dans le groupe %d\n", groupe);
    }
}

// 5. Fonction pour calculer la moyenne d'un tableau
double moyTab(int* tab) {
    int somme = 0;
    for (int i = 0; i < N; i++) {
        somme += tab[i];
    }
    return (double)somme / N;
}

// 6. Fonction pour trouver un étudiant par nom et prénom
Etudiant* trouveEtudiant(char* nom, char* prenom, LstEtudiants lst) {
    ChainonEtudiant* courant = lst;
    
    while (courant != NULL) {
        if (strcmp(courant->etudiant.nom, nom) == 0 && 
            strcmp(courant->etudiant.prenom, prenom) == 0) {
            return &(courant->etudiant);
        }
        courant = courant->suivant;
    }
    
    return NULL;
}

// 7. Calculer la moyenne de "Spiruline Barnabus"
void moyenneSpirulina(LstEtudiants lst) {
    Etudiant* etudiant = trouveEtudiant("Barnabus", "Spiruline", lst);
    
    if (etudiant == NULL) {
        printf("Erreur : Aucun élève nommé Spiruline Barnabus n'existe.\n");
    } else {
        double moyenne = moyTab(etudiant->notes);
        printf("Moyenne de Spiruline Barnabus : %.2f\n", moyenne);
    }
}

// 8. Calculer la moyenne de toute la promotion
double moyennePromotion(LstEtudiants lst) {
    if (lst == NULL) return 0.0;
    
    double sommeMoyennes = 0.0;
    int nbEtudiants = 0;
    ChainonEtudiant* courant = lst;
    
    while (courant != NULL) {
        sommeMoyennes += moyTab(courant->etudiant.notes);
        nbEtudiants++;
        courant = courant->suivant;
    }
    
    return nbEtudiants > 0 ? sommeMoyennes / nbEtudiants : 0.0;
}

// 9. Trouver l'étudiant avec la plus mauvaise moyenne
void plusMauvaiseMoyenne(LstEtudiants lst) {
    if (lst == NULL) {
        printf("Aucun étudiant dans la liste.\n");
        return;
    }
    
    ChainonEtudiant* courant = lst;
    ChainonEtudiant* plusMauvais = lst;
    double moyenneMin = moyTab(lst->etudiant.notes);
    
    while (courant != NULL) {
        double moyenneCourante = moyTab(courant->etudiant.notes);
        if (moyenneCourante < moyenneMin) {
            moyenneMin = moyenneCourante;
            plusMauvais = courant;
        }
        courant = courant->suivant;
    }
    
    printf("Étudiant avec la plus mauvaise moyenne : %s %s (%.2f)\n",
           plusMauvais->etudiant.prenom, plusMauvais->etudiant.nom, moyenneMin);
}

void afficherEtudiant(Etudiant* etudiant) {
    printf("Nom: %s %s, Groupe: %d\n", etudiant->prenom, etudiant->nom, etudiant->groupe);
    printf("Notes: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", etudiant->notes[i]);
    }
    printf("(Moyenne: %.2f)\n", moyTab(etudiant->notes));
}

void libererListe(LstEtudiants lst) {
    while (lst != NULL) {
        ChainonEtudiant* temp = lst;
        lst = lst->suivant;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    LstEtudiants liste = NULL;
    int choix;
    
    printf("=== Gestion des étudiants ===\n");
    
    // Ajouter quelques étudiants de test
    printf("Ajout d'étudiants de test...\n");
    
    // Créer manuellement quelques étudiants pour les tests
    // Créer manuellement quelques étudiants
    ChainonEtudiant* etudiant1 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant1->etudiant.nom, "Barnabus");
    strcpy(etudiant1->etudiant.prenom, "Spiruline");
    etudiant1->etudiant.groupe = 1;
    for (int i = 0; i < N; i++) {
        etudiant1->etudiant.notes[i] = rand() % 21;
    }
    etudiant1->suivant = NULL;
    liste = etudiant1;
    
    ChainonEtudiant* etudiant2 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant2->etudiant.nom, "Dupont");
    strcpy(etudiant2->etudiant.prenom, "Jean");
    etudiant2->etudiant.groupe = 2;
    for (int i = 0; i < N; i++) {
        etudiant2->etudiant.notes[i] = rand() % 21;
    }
    etudiant2->suivant = NULL;
    etudiant1->suivant = etudiant2;

    ChainonEtudiant* etudiant3 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant3->etudiant.nom, "Bensaid");
    strcpy(etudiant3->etudiant.prenom, "Yassine");
    etudiant3->etudiant.groupe = 2;
    for (int i = 0; i < N; i++) {
        etudiant3->etudiant.notes[i] = rand() % 21;
    }
    etudiant3->suivant = NULL;
    etudiant2->suivant = etudiant3;
    
    ChainonEtudiant* etudiant4 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant4->etudiant.nom, "Bensaid");
    strcpy(etudiant4->etudiant.prenom, "Myriam");
    etudiant4->etudiant.groupe = 3;
    for (int i = 0; i < N; i++) {
        etudiant4->etudiant.notes[i] = rand() % 21;
    }
    etudiant4->suivant = NULL;
    etudiant3->suivant = etudiant4;
    
    ChainonEtudiant* etudiant5 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant5->etudiant.nom, "Bensaid");
    strcpy(etudiant5->etudiant.prenom, "Nahil");
    etudiant5->etudiant.groupe = 3;
    for (int i = 0; i < N; i++) {
        etudiant5->etudiant.notes[i] = rand() % 21;
    }
    etudiant5->suivant = NULL;
    etudiant4->suivant = etudiant5;
    
    ChainonEtudiant* etudiant6 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant6->etudiant.nom, "Bensaid");
    strcpy(etudiant6->etudiant.prenom, "Mehdi");
    etudiant6->etudiant.groupe = 1;
    for (int i = 0; i < N; i++) {
        etudiant6->etudiant.notes[i] = rand() % 21;
    }
    etudiant6->suivant = NULL;
    etudiant5->suivant = etudiant6;
    
    ChainonEtudiant* etudiant7 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant7->etudiant.nom, "Bensaid");
    strcpy(etudiant7->etudiant.prenom, "Otmane");
    etudiant7->etudiant.groupe = 2;
    for (int i = 0; i < N; i++) {
        etudiant7->etudiant.notes[i] = rand() % 21;
    }
    etudiant7->suivant = NULL;
    etudiant6->suivant = etudiant7;
    
    ChainonEtudiant* etudiant8 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant8->etudiant.nom, "Ouarghi");
    strcpy(etudiant8->etudiant.prenom, "Sheryne");
    etudiant8->etudiant.groupe = 3;
    for (int i = 0; i < N; i++) {
        etudiant8->etudiant.notes[i] = rand() % 21;
    }
    etudiant8->suivant = NULL;
    etudiant7->suivant = etudiant8;
    
    ChainonEtudiant* etudiant9 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant9->etudiant.nom, "Bertal");
    strcpy(etudiant9->etudiant.prenom, "Lina");
    etudiant9->etudiant.groupe = 1;
    for (int i = 0; i < N; i++) {
        etudiant9->etudiant.notes[i] = rand() % 21;
    }
    etudiant9->suivant = NULL;
    etudiant8->suivant = etudiant9;
    
    ChainonEtudiant* etudiant10 = (ChainonEtudiant*)malloc(sizeof(ChainonEtudiant));
    strcpy(etudiant10->etudiant.nom, "d'Hordain");
    strcpy(etudiant10->etudiant.prenom, "Corentin");
    etudiant10->etudiant.groupe = 2;
    for (int i = 0; i < N; i++) {
        etudiant10->etudiant.notes[i] = rand() % 21;
    }
    etudiant10->suivant = NULL;
    etudiant9->suivant = etudiant10;
    
    do {
        printf("\n=== Menu ===\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Lister les étudiants d'un groupe\n");
        printf("3. Moyenne de Spiruline Barnabus\n");
        printf("4. Moyenne de la promotion\n");
        printf("5. Plus mauvaise moyenne\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                saisirEtudiant(&liste);
                break;
            case 2: {
                int groupe;
                printf("Numéro du groupe : ");
                scanf("%d", &groupe);
                listeParGroupe(liste, groupe);
                break;
            }
            case 3:
                moyenneSpirulina(liste);
                break;
            case 4:
                printf("Moyenne de la promotion : %.2f\n", moyennePromotion(liste));
                break;
            case 5:
                plusMauvaiseMoyenne(liste);
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
    
    libererListe(liste);
    return 0;
}