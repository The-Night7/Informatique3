/*
 * Proposer une ou plusieurs fonctions qui permettent de construire un ABR à partir
 * d'un arbre binaire simple.
 */

// Structure de noeud d'arbre binaire
typedef struct Noeud {
    int valeur;
    struct Noeud* gauche;
    struct Noeud* droite;
} Noeud;

// Fonction pour créer un nouveau noeud
Noeud* creerNoeud(int valeur) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud) {
        nouveauNoeud->valeur = valeur;
        nouveauNoeud->gauche = NULL;
        nouveauNoeud->droite = NULL;
    }
    return nouveauNoeud;
}

// Fonction pour insérer une valeur dans un ABR
Noeud* insererDansABR(Noeud* racine, int valeur) {
    if (racine == NULL) {
        return creerNoeud(valeur);
    }

    if (valeur < racine->valeur) {
        racine->gauche = insererDansABR(racine->gauche, valeur);
    } else if (valeur > racine->valeur) {
        racine->droite = insererDansABR(racine->droite, valeur);
    }

    return racine;
}

// Fonction pour parcourir un arbre binaire en ordre infixe et stocker les valeurs
void parcoursInfixe(Noeud* racine, int* tableau, int* index) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche, tableau, index);
        tableau[(*index)++] = racine->valeur;
        parcoursInfixe(racine->droite, tableau, index);
    }
}

// Fonction pour libérer la mémoire d'un arbre
void libererArbre(Noeud* racine) {
    if (racine != NULL) {
        libererArbre(racine->gauche);
        libererArbre(racine->droite);
        free(racine);
    }
}

// Fonction principale pour convertir un arbre binaire en ABR
Noeud* convertirEnABR(Noeud* arbreBinaire) {
    // Étape 1: Compter le nombre de noeuds dans l'arbre
    int nombreNoeuds = 0;
    compterNoeuds(arbreBinaire, &nombreNoeuds);

    // Étape 2: Allouer un tableau pour stocker les valeurs
    int* valeurs = (int*)malloc(nombreNoeuds * sizeof(int));
    if (!valeurs) return NULL;

    // Étape 3: Parcourir l'arbre et stocker les valeurs dans le tableau
    int index = 0;
    parcoursInfixe(arbreBinaire, valeurs, &index);

    // Étape 4: Trier le tableau (tri à bulles simple)
    trierTableau(valeurs, nombreNoeuds);

    // Étape 5: Construire un nouvel ABR à partir du tableau trié
    Noeud* abr = NULL;
    for (int i = 0; i < nombreNoeuds; i++) {
        abr = insererDansABR(abr, valeurs[i]);
    }

    // Libérer la mémoire du tableau
    free(valeurs);

    return abr;
}

// Fonction auxiliaire pour compter les noeuds
void compterNoeuds(Noeud* racine, int* compte) {
    if (racine != NULL) {
        (*compte)++;
        compterNoeuds(racine->gauche, compte);
        compterNoeuds(racine->droite, compte);
    }
}

// Fonction pour trier un tableau (tri à bulles)
void trierTableau(int* tableau, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tableau[j] > tableau[j + 1]) {
                int temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;
            }
        }
    }
}
