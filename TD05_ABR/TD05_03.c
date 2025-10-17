/* 1. Modifier la fonction de recherche recherche(pArbre a, int e) pour qu'elle retourne le nombre de noeuds qui auront
 * été parcourus lors de cette recherche. Si un élément n'appartient pas à l'arbre, on affichera que l'élément recherché
 * n'existe pas mais on retournera tout de même le nombre de noeuds visités.
 * 2. Proposer une modification de la fonction permettant le parcours Préfixe de l'arbre pour que cette dernière serve à
 * rechercher si un élément existe dans l'arbre en parcourant l'arbre et en s'arrêtant lorsque l'élément est trouvé. Comme
 * pour la question précédente, la fonction doit afficher le nombre de noeuds parcourus.
 * 3. Aficher le nombre de noeuds parcourus pour les deux fonctions lors de la recherche des éléments suivants : 10, 20, 22.
 */

// 1. Fonction de recherche modifiée pour compter les noeuds parcourus
int recherche(pArbre a, int e) {
    int noeudsParcourus = 0;

    if (a == NULL) {
        printf("L'élément %d n'existe pas dans l'arbre.\n", e);
        return noeudsParcourus;
    }

    noeudsParcourus++;  // On compte le noeud courant

    if (a->elmt == e) {
        printf("L'élément %d a été trouvé.\n", e);
        return noeudsParcourus;
    } else if (e < a->elmt) {
        return noeudsParcourus + recherche(a->fg, e);
    } else {
        return noeudsParcourus + recherche(a->fd, e);
    }
}

// 2. Fonction de parcours préfixe modifiée pour rechercher un élément
int recherchePrefixe(pArbre a, int e) {
    static int noeudsParcourus = 0;
    static int trouve = 0;

    // Si on commence une nouvelle recherche
    if (a != NULL && noeudsParcourus == 0) {
        trouve = 0;  // Réinitialiser le drapeau de recherche
    }

    // Si l'arbre est vide ou si on a déjà trouvé l'élément
    if (a == NULL || trouve) {
        return noeudsParcourus;
    }

    noeudsParcourus++;  // On compte le noeud courant

    // Vérifier le noeud courant
    if (a->elmt == e) {
        trouve = 1;
        printf("L'élément %d a été trouvé en parcours préfixe.\n", e);
        return noeudsParcourus;
    }

    // Parcourir le sous-arbre gauche
    recherchePrefixe(a->fg, e);

    // Si l'élément n'a pas été trouvé dans le sous-arbre gauche, parcourir le sous-arbre droit
    if (!trouve) {
        recherchePrefixe(a->fd, e);
    }

    // Si c'est la fin de la recherche et qu'on n'a pas trouvé l'élément
    if (noeudsParcourus > 0 && !trouve) {
        printf("L'élément %d n'existe pas dans l'arbre (parcours préfixe).\n", e);
        int resultat = noeudsParcourus;
        noeudsParcourus = 0;  // Réinitialiser pour la prochaine recherche
        return resultat;
    }

    return noeudsParcourus;
}

// 3. Fonction pour tester les deux méthodes de recherche
void testerRecherches(pArbre a) {
    int elements[] = {10, 20, 22};
    int nbElements = 3;

    printf("\n--- Test des fonctions de recherche ---\n");

    for (int i = 0; i < nbElements; i++) {
        int e = elements[i];
        printf("\nRecherche de l'élément %d:\n", e);

        // Recherche classique
        int noeudsClassique = recherche(a, e);
        printf("Recherche classique: %d noeuds parcourus\n", noeudsClassique);

        // Recherche par parcours préfixe
        int noeudsPrefixe = recherchePrefixe(a, e);
        printf("Recherche préfixe: %d noeuds parcourus\n", noeudsPrefixe);
    }
}
