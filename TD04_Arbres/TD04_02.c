/* 1. Construction de l'arbre :
(a) Déclarer une structure Arbre permettant de gérer un arbre binaire contenant des entiers.
(b) Redéfinir le type pointeur sur arbre en pArbre.
(c) Créer la fonction creerArbre permettant de creer un un arbre. Cette fonction prend en paramètre l'élément à
insérer dans le nœud de l'arbre, initialise ses fils et retoune son adresse.
(d) Écrire la fonction int estVide(pArbre a) qui retourne 1 si a est un arbre vide, 0 sinon.
(e) Écrire la fonction int estFeuille(pArbre a) qui retourne 1 si l'arbre est une feuille, 0 sinon.
(f) Écrire la fonction int element(pArbre a) qui retourne l'élément stocké dans le nœud de a.
(g) Écrire une fonction exitseFilsGauche(pArbre a) qui retourne 1 si l'arbre a un fils gauche, 0 sinon. Faire une
fonction similaire exitseFilsDroit(pArbre a).
(h) Écrire une fonction ajouterFilsGauche(pArbre a, int e) qui créé à l'arbre un fils gauche qui va contenir e.
Faire de même avec ajouterFilsDroit(pArbre a, int e).
(i) A l'aide des fonctions réalisées précédement, construire l'arbre suivant :
2. Parcours de l'arbre :
(a) Écrire une fonction traiter qui affichera le contenu du nœud de l'arbre passé en paramètre.
(b) Écrire une procédure parcoursPrefixe permettant d'afficher tous les éléments d'un arbre par un parcours en
profondeur préfixe.
(c) Vérifier que l'arbre que vous avez construit est correct en affichant son parcours préfixe.
(d) Écrire une procédure parcoursPostfixe permettant d'afficher tous les éléments d'un arbre par un parcours en
profondeur postfixe. Tester la fonction sur l'arbre.
(e) Déclarer une structure permettant de gérér une FILE contenant des pArbre.
(f) Écrire une procédure parcoursLargeur permettant d'afficher tous les éléments d'un arbre par un parcours en
largeur.
3. Modification de l'arbre
(a) Écrire une fonction parbre modifierRacine(pArbre a, int e) qui modifie l'élément stocké dans a par l'élément
e et retourne a.
(b) Écrire une fonction pArbre supprimerFilsGauche(pArbre) qui supprime le fils gauche d'un arbre. Idem avec
supprimerFilsDroit(pArbre). Attention aux fuites mémoire !(voir cours).
(c) Supprimer les nœud 9, 15 et 3 de l'arbre. Quel devrait être son parcours en largeur ? Vérifier.
4. Annalyse de l'arbre
5. Écrire une fonction nmbFeuille qui retourne le nombre de feuilles d'un arbre.
6. Écrire une fonction tailleArbre qui retourne la taille (nombre de nœuds internes) de l'arbre.
7. pas facile ! Écrire une fonction hauteur qui retourne la hauteur d'un arbre. Elle renvera -1 si l'arbre est vide.
*/

#include <stdio.h>
#include <stdlib.h>

// 1.a Déclaration de la structure Arbre
typedef struct Arbre {
    int element;           // Élément stocké dans le nœud
    struct Arbre *gauche;  // Pointeur vers le fils gauche
    struct Arbre *droit;   // Pointeur vers le fils droit
} Arbre;

// 1.b Redéfinition du type pointeur sur arbre
typedef Arbre* pArbre;

// 1.c Fonction pour créer un arbre
pArbre creerArbre(int e) {
    pArbre nouvelArbre = (pArbre)malloc(sizeof(Arbre));
    if (nouvelArbre == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouvelArbre->element = e;
    nouvelArbre->gauche = NULL;
    nouvelArbre->droit = NULL;
    return nouvelArbre;
}

// 1.d Fonction pour vérifier si un arbre est vide
int estVide(pArbre a) {
    return (a == NULL) ? 1 : 0;
}

// 1.e Fonction pour vérifier si un nœud est une feuille
int estFeuille(pArbre a) {
    if (estVide(a)) return 0;  // Un arbre vide n'est pas une feuille
    return (a->gauche == NULL && a->droit == NULL) ? 1 : 0;
}

// 1.f Fonction pour obtenir l'élément stocké dans un nœud
int element(pArbre a) {
    if (estVide(a)) {
        printf("Erreur: tentative d'accès à un arbre vide\n");
        exit(EXIT_FAILURE);
    }
    return a->element;
}

// 1.g Fonction pour vérifier l'existence d'un fils gauche
int existeFilsGauche(pArbre a) {
    if (estVide(a)) return 0;
    return (a->gauche != NULL) ? 1 : 0;
}

// 1.g Fonction pour vérifier l'existence d'un fils droit
int existeFilsDroit(pArbre a) {
    if (estVide(a)) return 0;
    return (a->droit != NULL) ? 1 : 0;
}

// 1.h Fonction pour ajouter un fils gauche
void ajouterFilsGauche(pArbre a, int e) {
    if (estVide(a)) {
        printf("Erreur: impossible d'ajouter un fils à un arbre vide\n");
        return;
    }
    if (existeFilsGauche(a)) {
        printf("Erreur: un fils gauche existe déjà\n");
        return;
    }
    a->gauche = creerArbre(e);
}

// 1.h Fonction pour ajouter un fils droit
void ajouterFilsDroit(pArbre a, int e) {
    if (estVide(a)) {
        printf("Erreur: impossible d'ajouter un fils à un arbre vide\n");
        return;
    }
    if (existeFilsDroit(a)) {
        printf("Erreur: un fils droit existe déjà\n");
        return;
    }
    a->droit = creerArbre(e);
}

// 2.a Fonction pour traiter (afficher) un nœud
void traiter(pArbre a) {
    if (!estVide(a)) {
        printf("%d ", a->element);
    }
}

// 2.b Parcours préfixe (racine, gauche, droit)
void parcoursPrefixe(pArbre a) {
    if (!estVide(a)) {
        traiter(a);                // Traiter la racine
        parcoursPrefixe(a->gauche); // Parcourir le sous-arbre gauche
        parcoursPrefixe(a->droit);  // Parcourir le sous-arbre droit
    }
}

// 2.d Parcours postfixe (gauche, droit, racine)
void parcoursPostfixe(pArbre a) {
    if (!estVide(a)) {
        parcoursPostfixe(a->gauche); // Parcourir le sous-arbre gauche
        parcoursPostfixe(a->droit);  // Parcourir le sous-arbre droit
        traiter(a);                 // Traiter la racine
    }
}

// Parcours infixe (gauche, racine, droit) - bonus
void parcoursInfixe(pArbre a) {
    if (!estVide(a)) {
        parcoursInfixe(a->gauche); // Parcourir le sous-arbre gauche
        traiter(a);               // Traiter la racine
        parcoursInfixe(a->droit);  // Parcourir le sous-arbre droit
    }
}

// 2.e Structure pour gérer une file d'arbres
#define TAILLE_MAX 100

typedef struct {
    pArbre elements[TAILLE_MAX];
    int debut;
    int fin;
    int taille;
} File;

// Initialiser une file vide
void initialiserFile(File *f) {
    f->debut = 0;
    f->fin = -1;
    f->taille = 0;
}

// Vérifier si la file est vide
int fileEstVide(File *f) {
    return (f->taille == 0);
}

// Vérifier si la file est pleine
int fileEstPleine(File *f) {
    return (f->taille == TAILLE_MAX);
}

// Enfiler un élément
void enfiler(File *f, pArbre a) {
    if (fileEstPleine(f)) {
        printf("Erreur: file pleine\n");
        return;
    }
    f->fin = (f->fin + 1) % TAILLE_MAX;
    f->elements[f->fin] = a;
    f->taille++;
}

// Défiler un élément
pArbre defiler(File *f) {
    if (fileEstVide(f)) {
        printf("Erreur: file vide\n");
        return NULL;
    }
    pArbre a = f->elements[f->debut];
    f->debut = (f->debut + 1) % TAILLE_MAX;
    f->taille--;
    return a;
}

// Prototype pour éviter les erreurs de déclaration implicite
pArbre supprimerFilsDroit(pArbre a);

// 2.f Parcours en largeur
void parcoursLargeur(pArbre a) {
    if (estVide(a)) return;

    File file;
    initialiserFile(&file);
    enfiler(&file, a);

    while (!fileEstVide(&file)) {
        pArbre courant = defiler(&file);
        traiter(courant);

        if (existeFilsGauche(courant)) {
            enfiler(&file, courant->gauche);
        }
        if (existeFilsDroit(courant)) {
            enfiler(&file, courant->droit);
        }
    }
}

// 3.a Modifier la racine d'un arbre
pArbre modifierRacine(pArbre a, int e) {
    if (!estVide(a)) {
        a->element = e;
    }
    return a;
}

// 3.b Supprimer le fils gauche d'un arbre
pArbre supprimerFilsGauche(pArbre a) {
    if (estVide(a) || !existeFilsGauche(a)) {
        return a;
    }

    // Libération récursive de la mémoire du sous-arbre gauche
    if (existeFilsGauche(a->gauche)) {
        supprimerFilsGauche(a->gauche);
    }
    if (existeFilsDroit(a->gauche)) {
        supprimerFilsDroit(a->gauche);
    }

    free(a->gauche);
    a->gauche = NULL;
    return a;
}

// 3.b Supprimer le fils droit d'un arbre
pArbre supprimerFilsDroit(pArbre a) {
    if (estVide(a) || !existeFilsDroit(a)) {
        return a;
    }

    // Libération récursive de la mémoire du sous-arbre droit
    if (existeFilsGauche(a->droit)) {
        supprimerFilsGauche(a->droit);
    }
    if (existeFilsDroit(a->droit)) {
        supprimerFilsDroit(a->droit);
    }

    free(a->droit);
    a->droit = NULL;
    return a;
}

// 4. Analyse de l'arbre

// 5. Fonction pour compter le nombre de feuilles
int nmbFeuille(pArbre a) {
    if (estVide(a)) {
        return 0;
    }
    if (estFeuille(a)) {
        return 1;
    }
    return nmbFeuille(a->gauche) + nmbFeuille(a->droit);
}

// 6. Fonction pour calculer la taille de l'arbre (nombre de nœuds)
int tailleArbre(pArbre a) {
    if (estVide(a)) {
        return 0;
    }
    return 1 + tailleArbre(a->gauche) + tailleArbre(a->droit);
}

// 7. Fonction pour calculer la hauteur de l'arbre
int hauteur(pArbre a) {
    if (estVide(a)) {
        return -1;
    }
    int hauteurGauche = hauteur(a->gauche);
    int hauteurDroite = hauteur(a->droit);

    // La hauteur est le maximum des hauteurs des sous-arbres + 1
    return (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite) + 1;
}

// Fonction principale pour tester l'implémentation
int main() {
    // 1.i Construction de l'arbre
    pArbre racine = creerArbre(1);

    // Niveau 1
    ajouterFilsGauche(racine, 2);
    ajouterFilsDroit(racine, 8);

    // Niveau 2 - sous-arbre gauche
    ajouterFilsGauche(racine->gauche, 3);
    ajouterFilsDroit(racine->gauche, 6);

    // Niveau 2 - sous-arbre droit
    ajouterFilsGauche(racine->droit, 9);
    ajouterFilsDroit(racine->droit, 10);

    // Niveau 3
    ajouterFilsGauche(racine->gauche->gauche, 4);
    ajouterFilsDroit(racine->gauche->gauche, 5);
    ajouterFilsDroit(racine->gauche->droit, 7);

    // 2.c Vérification avec parcours préfixe
    printf("Parcours préfixe: ");
    parcoursPrefixe(racine);
    printf("\n");

    // Test du parcours postfixe
    printf("Parcours postfixe: ");
    parcoursPostfixe(racine);
    printf("\n");

    // Test du parcours en largeur
    printf("Parcours en largeur: ");
    parcoursLargeur(racine);
    printf("\n");
    // Analyse de l'arbre
    printf("Nombre de feuilles: %d\n", nmbFeuille(racine));
    printf("Taille de l'arbre: %d\n", tailleArbre(racine));

    printf("Hauteur de l'arbre: %d\n", hauteur(racine));

    // 3.c Suppression des nœuds 9, 15 et 3
    supprimerFilsGauche(racine->droit);  // Supprime 9
    supprimerFilsDroit(racine->droit->droit);  // Supprime 15

    // Pour supprimer 3, on doit d'abord sauvegarder ses fils
    pArbre filsGauche3 = racine->gauche->gauche;
    pArbre filsDroit3 = racine->gauche->droit;

    // Puis remplacer le fils gauche de la racine
    free(racine->gauche);
    racine->gauche = filsGauche3;  // On garde le sous-arbre 1

    // Le parcours en largeur après suppression devrait être: 8, 1, 10, 14
    printf("Parcours en largeur après suppression: ");
    parcoursLargeur(racine);
    printf("\n");

    // Analyse de l'arbre après suppression
    printf("Nombre de feuilles: %d\n", nmbFeuille(racine));
    printf("Taille de l'arbre: %d\n", tailleArbre(racine));

    printf("Hauteur de l'arbre: %d\n", hauteur(racine));

    // Libération de la mémoire
    // On supprime récursivement tous les nœuds
    while (!estVide(racine)) {
        if (existeFilsGauche(racine)) {
            supprimerFilsGauche(racine);
        }
        if (existeFilsDroit(racine)) {
            supprimerFilsDroit(racine);
        }
        pArbre temp = racine;
        racine = NULL;
        free(temp);
    }

    return 0;
}
