#include <stdio.h>

// exercice 1

typedef struct _node
{
    int valeur;
    int somme_descendants;
    struct _node *fg ,*fd;
} Noeud, *Arbre;

// 1

Arbre insererSomme(Arbre a, int val) {
    if (a == NULL) {
        Arbre n = (Arbre)malloc(sizeof(Noeud));
        if (!n) return NULL; // échec allocation : on remonte NULL
        n->valeur = val;
        n->somme_descendants = 0;
        n->fg = n->fd = NULL;
        return n;
    }

    if (val < a->valeur) {
        Arbre old = a->fg;
        a->fg = insererSomme(a->fg, val);
        if (a->fg != NULL && old != a->fg) {
            // insertion réussie quelque part dans le sous-arbre gauche
            a->somme_descendants += val;
        }
    } else if (val > a->valeur) {
        Arbre old = a->fd;
        a->fd = insererSomme(a->fd, val);
        if (a->fd != NULL && old != a->fd) {
            // insertion réussie quelque part dans le sous-arbre droit
            a->somme_descendants += val;
        }
    } else {
        // val == a->valeur : doublon, on choisit de ne pas insérer
    }

    return a;
}

// 2

int estHarmonise(Arbre a) {
    if (!a) return 1;
    if (!(a->valeur < a->somme_descendants)) return 0;
    return estHarmonise(a->fg) && estHarmonise(a->fd);
}

// 3

/* Oui, il faut le recalculer (au minimum) pour :
 *
 * * le pivot (le nœud qui “monte”, souvent noté y)
 * * l’ancienne racine de la rotation (le nœud qui “descend”, souvent noté x)
 *
 * Justification : une rotation à gauche ne change pas l’ensemble des nœuds dans le sous‑arbre, mais change la répartition
 * des descendants entre x et y (certains nœuds qui étaient descendants de y deviennent descendants de x, via le sous‑arbre
 * T2 = y->fg).
 *
 * Comme somme_descendants dépend de quels nœuds sont descendants, les valeurs deviennent incohérentes si on ne met pas à
 * jour.
 *
 */

