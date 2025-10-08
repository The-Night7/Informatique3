/* On rappelle que les Chainons des listes doublement chaînées possèdent un pointeur vers le Chainon suivant et un pointeur
 * vers le Chainon précédent. Il est donc possible de parcourir une telle liste dans les deux sens.
 * 1. Déclarer une structure de liste doublement chaînée permettant de stocker des mots de 20 caractères maximum.
 * 2. Écrire une fonction compareMot(char *mot1, char* mot2 ) qui retourne 1 si mot1 est avant mot2 dans l'ordre alphabétique et 0 sinon.
 * 3. Écrire une fonction insertListe(char *mot1, liste *pliste ) qui ajoute à la liste doublement chaînée pointée par
 * pliste de mots classés dans l'ordre alphabetique un nouveau Chainon contenant mot1.
 * 4. Écrire une procédure affiche(liste *pliste ) qui affiche dans l'ordre les mots contenus dans la liste.
 * 5. Écrire une procédure afficheInv(liste *pliste ) qui affiche dans l'ordre inverse les mots contenus dans la liste.
 * 6. Déclarer un nouvelle liste et la remplir avec une vingtaine de mots. Afficher cette liste de mots dans l'ordre alphabétique
 * et anti-alphabétique. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Déclaration de la structure de liste doublement chaînée
typedef struct Chainon {
    char mot[21]; // 20 caractères maximum + le caractère nul '\0'
    struct Chainon *suivant;
    struct Chainon *precedent;
} Chainon;

typedef struct {
    Chainon *premier;
    Chainon *dernier;
} liste;

// 2. Fonction qui compare deux mots alphabétiquement
int compareMot(char *mot1, char *mot2) {
    // Retourne 1 si mot1 est avant mot2 dans l'ordre alphabétique, 0 sinon
    return (strcmp(mot1, mot2) < 0) ? 1 : 0;
}

// 3. Fonction pour insérer un mot dans la liste de manière ordonnée
void insertListe(char *mot1, liste *pliste) {
    // Création du nouveau chainon
    Chainon *nouveau = (Chainon *)malloc(sizeof(Chainon));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    // Copie du mot dans le nouveau chainon
    strncpy(nouveau->mot, mot1, 20);
    nouveau->mot[20] = '\0'; // Assure que la chaîne est terminée

    // Si la liste est vide
    if (pliste->premier == NULL) {
        nouveau->suivant = NULL;
        nouveau->precedent = NULL;
        pliste->premier = nouveau;
        pliste->dernier = nouveau;
        return;
    }

    // Parcours de la liste pour trouver la position d'insertion
    Chainon *courant = pliste->premier;

    // Si le nouveau mot doit être inséré en tête de liste
    if (compareMot(mot1, courant->mot)) {
        nouveau->suivant = courant;
        nouveau->precedent = NULL;
        courant->precedent = nouveau;
        pliste->premier = nouveau;
        return;
    }

    // Recherche de la position d'insertion
    while (courant->suivant != NULL && !compareMot(mot1, courant->suivant->mot)) {
        courant = courant->suivant;
    }

    // Insertion en milieu ou fin de liste
    nouveau->suivant = courant->suivant;
    nouveau->precedent = courant;

    if (courant->suivant != NULL) {
        courant->suivant->precedent = nouveau;
    } else {
        // Si on insère en fin de liste
        pliste->dernier = nouveau;
    }

    courant->suivant = nouveau;
}

// 4. Procédure pour afficher la liste dans l'ordre
void affiche(liste *pliste) {
    printf("Liste dans l'ordre alphabétique:\n");
    Chainon *courant = pliste->premier;
    while (courant != NULL) {
        printf("%s\n", courant->mot);
        courant = courant->suivant;
    }
    printf("\n");
}

// 5. Procédure pour afficher la liste dans l'ordre inverse
void afficheInv(liste *pliste) {
    printf("Liste dans l'ordre anti-alphabétique:\n");
    Chainon *courant = pliste->dernier;
    while (courant != NULL) {
        printf("%s\n", courant->mot);
        courant = courant->precedent;
    }
    printf("\n");
}

// Fonction pour initialiser une liste vide
void initialiserListe(liste *pliste) {
    pliste->premier = NULL;
    pliste->dernier = NULL;
}

// Fonction pour libérer la mémoire allouée à la liste
void libererListe(liste *pliste) {
    Chainon *courant = pliste->premier;
    Chainon *suivant;

    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }

    pliste->premier = NULL;
    pliste->dernier = NULL;
}

int main() {
    // 6. Déclaration et remplissage d'une liste avec une vingtaine de mots
    liste maListe;
    initialiserListe(&maListe);

    // Insertion de 20 mots (je l'avoue je les ais générés par IA)
    insertListe("pomme", &maListe);
    insertListe("banane", &maListe);
    insertListe("orange", &maListe);
    insertListe("fraise", &maListe);
    insertListe("citron", &maListe);
    insertListe("kiwi", &maListe);
    insertListe("ananas", &maListe);
    insertListe("mangue", &maListe);
    insertListe("poire", &maListe);
    insertListe("cerise", &maListe);
    insertListe("abricot", &maListe);
    insertListe("peche", &maListe);
    insertListe("prune", &maListe);
    insertListe("raisin", &maListe);
    insertListe("melon", &maListe);
    insertListe("pasteque", &maListe);
    insertListe("framboise", &maListe);
    insertListe("myrtille", &maListe);
    insertListe("cassis", &maListe);
    insertListe("groseille", &maListe);

    // Affichage de la liste dans l'ordre alphabétique
    affiche(&maListe);

    // Affichage de la liste dans l'ordre anti-alphabétique
    afficheInv(&maListe);

    // Libération de la mémoire
    libererListe(&maListe);

    return 0;
}
