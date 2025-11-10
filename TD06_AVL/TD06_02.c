/* 1. On rappelle que pour construire un AVL, chaque noeud de l'arbre doit être associé à un facteur d'équilibrage dont la
valeur est :
equilibre = hauteur sous arbre droit - hauteur sous arbre gauche
Modifier la structure Arbre pour inclure ce nouveau champs. */
typedef struct noeud {
    Element elt;
    int equilibre; // facteur d'équilibrage
    struct noeud* gauche;
    struct noeud* droit;
} Noeud, *Arbre;
/* 2. Réécrire la fonction creerArbre(x : Element) pour inclure également ce nouveau champ et l'initialiser à la création
d'un nouveau noeud de l'arbre. */
Arbre creerArbre(Element x) {
    Arbre a = (Arbre)malloc(sizeof(Noeud));
    if (a == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    a->elt = x;
    a->equilibre = 0; // Initialisation du facteur d'équilibrage
    a->gauche = NULL;
    a->droit = NULL;
    return a;
}
/* 3. Les opérations de rééquilibrage s'effectuent à l'aide de « rotations » des sous-arbres (cf cours). Écrire les fonctions
RotationGauche( A : Arbre) permettant de faire la rotation du sous-arbre A avec son fils droit et RotationDroite(
A : Arbre) permettant de faire la rotation du sous-arbre A avec son fils gauche. */
Arbre RotationGauche(Arbre A) {
    Arbre pivot = A->droit;
    A->droit = pivot->gauche;
    pivot->gauche = A;

    // Mise à jour des facteurs d'équilibrage
    A->equilibre = A->equilibre - 1 - (pivot->equilibre > 0 ? pivot->equilibre : 0);
    pivot->equilibre = pivot->equilibre - 1 + (A->equilibre < 0 ? -A->equilibre : 0);

    return pivot;
}

Arbre RotationDroite(Arbre A) {
    Arbre pivot = A->gauche;
    A->gauche = pivot->droit;
    pivot->droit = A;

    // Mise à jour des facteurs d'équilibrage
    A->equilibre = A->equilibre + 1 - (pivot->equilibre < 0 ? -pivot->equilibre : 0);
    pivot->equilibre = pivot->equilibre + 1 + (A->equilibre > 0 ? A->equilibre : 0);

    return pivot;
}
/* 4. Tester ces deux fonctions sur les deux arbres suivants (que vous aurez construit manuellement avec les fonctions
ajouterFilsDroit et ajouterFilsGauche en prennant soin d'indiquer les bonnes valeurs d'élément ET d'équilibre
pour chaque noeud) : */
void testRotations() {
    // Construction du premier arbre pour tester RotationGauche
    Arbre arbre1 = creerArbre(10);
    arbre1->equilibre = 2;

    arbre1->droit = creerArbre(20);
    arbre1->droit->equilibre = 0;

    arbre1->droit->gauche = creerArbre(15);
    arbre1->droit->gauche->equilibre = 0;

    arbre1->droit->droit = creerArbre(30);
    arbre1->droit->droit->equilibre = 0;

    printf("Arbre avant rotation gauche:\n");
    afficherArbre(arbre1);

    arbre1 = RotationGauche(arbre1);

    printf("Arbre après rotation gauche:\n");
    afficherArbre(arbre1);

    // Construction du deuxième arbre pour tester RotationDroite
    Arbre arbre2 = creerArbre(30);
    arbre2->equilibre = -2;

    arbre2->gauche = creerArbre(20);
    arbre2->gauche->equilibre = 0;

    arbre2->gauche->gauche = creerArbre(10);
    arbre2->gauche->gauche->equilibre = 0;

    arbre2->gauche->droit = creerArbre(25);
    arbre2->gauche->droit->equilibre = 0;

    printf("Arbre avant rotation droite:\n");
    afficherArbre(arbre2);

    arbre2 = RotationDroite(arbre2);

    printf("Arbre après rotation droite:\n");
    afficherArbre(arbre2);
}
/* 5. À partir des fonctions précédentes, écrire les fonctions permettant d'effectuer les doubles rotations : DoubleRotationDroite(A
: Arbre) et DoubleRotationGauche(A : Arbre). */
Arbre DoubleRotationDroite(Arbre A) {
    A->gauche = RotationGauche(A->gauche);
    return RotationDroite(A);
}

Arbre DoubleRotationGauche(Arbre A) {
    A->droit = RotationDroite(A->droit);
    return RotationGauche(A);
}
/* 6. Tester une de ces fonctions (celle la plus adaptée !) sur l' arbre suivant (que vous aurez construit manuellement avec
les fonctions ajouterFilsDroit et ajouterFilsGaucheen prennant soin d'indiquer les bonnes valeurs d'élément ET
d'équilibre pour chaque noeud) : */
void testDoubleRotation() {
    // Construction de l'arbre pour tester DoubleRotationGauche
    Arbre arbre = creerArbre(10);
    arbre->equilibre = 2;

    arbre->droit = creerArbre(30);
    arbre->droit->equilibre = -1;

    arbre->droit->gauche = creerArbre(20);
    arbre->droit->gauche->equilibre = 0;

    printf("Arbre avant double rotation gauche:\n");
    afficherArbre(arbre);

    arbre = DoubleRotationGauche(arbre);

    printf("Arbre après double rotation gauche:\n");
    afficherArbre(arbre);
}
/* 7. Écrire la fonction equilibrerAVL( A : Arbre) qui permet d'effectuer la bonne rotation de l'arbre en fonction du
facteur d'équilibrage de A et de ses fils. */
Arbre equilibrerAVL(Arbre A) {
    if (A->equilibre >= 2) { // Déséquilibre à droite
        if (A->droit->equilibre <= -1) {
            // Double rotation gauche
            return DoubleRotationGauche(A);
        } else {
            // Rotation gauche simple
            return RotationGauche(A);
        }
    } else if (A->equilibre <= -2) { // Déséquilibre à gauche
        if (A->gauche->equilibre >= 1) {
            // Double rotation droite
            return DoubleRotationDroite(A);
        } else {
            // Rotation droite simple
            return RotationDroite(A);
        }
    }
    return A; // Arbre déjà équilibré
}
/* 8. Écrire la fonction insertionAVL( A : arbre , e : Element, h: pointeur sur entier) qui insère dans l'arbre un
nouveau noeud contenant l'élément e. L'insertion de l'élément est basée sur le même principe que l'insertion dans un
ABR. Il faut cependant veiller à mettre à jour le facteur d'équilibrage de chaque noeud (dont l'évolution est gérée par
le paramètre h) et à rééquilibrer l'arbre si besoin à l'aide de la fonction equilibrerAVL. */
Arbre insertionAVL(Arbre A, Element e, int* h) {
    if (A == NULL) {
        *h = 1; // La hauteur a augmenté
        return creerArbre(e);
    }

    if (e < A->elt) {
        A->gauche = insertionAVL(A->gauche, e, h);
        if (*h) { // Si la hauteur du sous-arbre gauche a augmenté
            A->equilibre--;
            if (A->equilibre == 0) {
                *h = 0; // L'arbre est équilibré, la hauteur n'a pas changé
            } else if (A->equilibre == -2) {
                A = equilibrerAVL(A);
                *h = 0; // Après rééquilibrage, la hauteur n'a pas changé
            }
        }
    } else if (e > A->elt) {
        A->droit = insertionAVL(A->droit, e, h);
        if (*h) { // Si la hauteur du sous-arbre droit a augmenté
            A->equilibre++;
            if (A->equilibre == 0) {
                *h = 0; // L'arbre est équilibré, la hauteur n'a pas changé
            } else if (A->equilibre == 2) {
                A = equilibrerAVL(A);
                *h = 0; // Après rééquilibrage, la hauteur n'a pas changé
            }
        }
    } else {
        // L'élément existe déjà, pas d'insertion
        *h = 0;
    }

    return A;
}
/* 9. Écrire la fonction suppAVL(A: Arbre, e: Element, h: pointeur sur entier) permettant de supprimer un noeud
contenant l'élément e de l'arbre A. Le raisonnement est le même que pour la question précédente. */
Arbre suppMin(Arbre A, Element* e, int* h) {
    if (A->gauche == NULL) {
        *e = A->elt;
        Arbre temp = A->droit;
        free(A);
        *h = 1; // La hauteur a diminué
        return temp;
    }

    A->gauche = suppMin(A->gauche, e, h);
    if (*h) {
        A->equilibre++;
        if (A->equilibre == 1) {
            *h = 0;
        } else if (A->equilibre == 2) {
            A = equilibrerAVL(A);
            *h = (A->equilibre == 0);
        }
    }

    return A;
}

Arbre suppAVL(Arbre A, Element e, int* h) {
    if (A == NULL) {
        *h = 0;
        return NULL;
    }

    if (e < A->elt) {
        A->gauche = suppAVL(A->gauche, e, h);
        if (*h) {
            A->equilibre++;
            if (A->equilibre == 1) {
                *h = 0;
            } else if (A->equilibre == 2) {
                A = equilibrerAVL(A);
                *h = (A->equilibre == 0);
            }
        }
    } else if (e > A->elt) {
        A->droit = suppAVL(A->droit, e, h);
        if (*h) {
            A->equilibre--;
            if (A->equilibre == -1) {
                *h = 0;
            } else if (A->equilibre == -2) {
                A = equilibrerAVL(A);
                *h = (A->equilibre == 0);
            }
        }
    } else {
        // Noeud à supprimer trouvé
        if (A->gauche == NULL) {
            Arbre temp = A->droit;
            free(A);
            *h = 1;
            return temp;
        } else if (A->droit == NULL) {
            Arbre temp = A->gauche;
            free(A);
            *h = 1;
            return temp;
        } else {
            // Noeud avec deux fils, on remplace par le minimum du sous-arbre droit
            Element min;
            A->droit = suppMin(A->droit, &min, h);
            A->elt = min;
            if (*h) {
                A->equilibre--;
                if (A->equilibre == -1) {
                    *h = 0;
                } else if (A->equilibre == -2) {
                    A = equilibrerAVL(A);
                    *h = (A->equilibre == 0);
                }
            }
        }
    }

    return A;
}
