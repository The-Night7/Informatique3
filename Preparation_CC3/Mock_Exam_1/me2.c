#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   Exercice 2 — Structures
   ========================= */

typedef struct {
    int id;
    float poids;
    int estPrioritaire; /* 0 ou 1 */
} Colis;

typedef struct _maillon {
    Colis *c;               /* alloué dynamiquement */
    struct _maillon *suiv;  /* pointeur vers le prochain */
} Maillon;

typedef struct {
    Maillon *tete;
    Maillon *queue;
} File;

/* =========================
   Helpers (robustesse)
   ========================= */

void initFile(File *f) {
    if (!f) return;
    f->tete = NULL;
    f->queue = NULL;
}

int fileVide(const File *f) {
    return (!f || f->tete == NULL);
}

static void afficherColis(const Colis *c) {
    if (!c) return;
    printf("Colis{id=%d, poids=%.2f, prioritaire=%s}\n",
           c->id, c->poids, c->estPrioritaire ? "OUI" : "NON");
}

/* Libère toute la file + tous les colis */
void libererFile(File *f) {
    if (!f) return;
    Maillon *cur = f->tete;
    while (cur) {
        Maillon *nxt = cur->suiv;
        free(cur->c);
        free(cur);
        cur = nxt;
    }
    f->tete = f->queue = NULL;
}

/* =========================
   2) Enfilage intelligent
   =========================

   Règles :
   - Non prioritaire : fin de file (queue)
   - Prioritaire : juste après le dernier prioritaire existant,
     ou en tête si aucun prioritaire.

   Contraintes :
   - mémoire dynamique
   - robustesse : tests malloc / pointeurs
*/

void enfilerColis(File *f, Colis c) {
    if (!f) return;

    /* Allocation du colis */
    Colis *pc = (Colis *)malloc(sizeof(Colis));
    if (!pc) {
        fprintf(stderr, "Erreur: malloc Colis a échoué\n");
        return;
    }
    *pc = c;

    /* Allocation du maillon */
    Maillon *m = (Maillon *)malloc(sizeof(Maillon));
    if (!m) {
        fprintf(stderr, "Erreur: malloc Maillon a échoué\n");
        free(pc);
        return;
    }
    m->c = pc;
    m->suiv = NULL;

    /* Cas file vide */
    if (f->tete == NULL) {
        f->tete = f->queue = m;
        return;
    }

    if (!c.estPrioritaire) {
        /* Ajout en fin */
        f->queue->suiv = m;
        f->queue = m;
        return;
    }

    /* Cas prioritaire : insertion après le dernier prioritaire */
    Maillon *prev = NULL;
    Maillon *cur = f->tete;
    Maillon *dernierPrio = NULL;

    while (cur) {
        if (cur->c && cur->c->estPrioritaire) {
            dernierPrio = cur;
        } else {
            /* dès qu'on rencontre un non-prio après des prios,
               on peut continuer mais ce n'est pas nécessaire */
        }
        cur = cur->suiv;
    }

    if (dernierPrio == NULL) {
        /* Aucun prioritaire -> insertion en tête */
        m->suiv = f->tete;
        f->tete = m;
        return;
    }

    /* Insertion juste après dernierPrio */
    m->suiv = dernierPrio->suiv;
    dernierPrio->suiv = m;

    /* Si on insère après la queue, mettre à jour la queue */
    if (f->queue == dernierPrio) {
        f->queue = m;
    }
}

/* =========================
   3) Traitement et libération
   =========================

   traiterColis :
   - retire le premier colis
   - affiche ses infos
   - retourne son adresse (Colis*)

   Remarques :
   - le maillon est libéré ici
   - le colis (Colis*) est retourné : c'est à l'appelant de free()
*/

Colis* traiterColis(File *f) {
    if (!f || f->tete == NULL) {
        fprintf(stderr, "Erreur: file vide, aucun colis à traiter\n");
        return NULL;
    }

    Maillon *m = f->tete;
    Colis *pc = m->c;

    /* Retrait du maillon */
    f->tete = m->suiv;
    if (f->tete == NULL) {
        /* la file devient vide */
        f->queue = NULL;
    }

    /* Affichage */
    afficherColis(pc);

    /* Libération du maillon (pas du colis) */
    free(m);

    return pc; /* l'appelant devra faire free(pc) */
}

/* =========================
   Petit main de démonstration (optionnel)
   =========================
   Compile:
     gcc -Wall -Wextra -O2 ex2.c -o ex2
*/

int main(void) {
    File f;
    initFile(&f);

    Colis a = { .id = 1, .poids = 2.5f, .estPrioritaire = 0 };
    Colis b = { .id = 2, .poids = 1.2f, .estPrioritaire = 1 };
    Colis c = { .id = 3, .poids = 3.1f, .estPrioritaire = 1 };
    Colis d = { .id = 4, .poids = 0.7f, .estPrioritaire = 0 };
    Colis e = { .id = 5, .poids = 9.9f, .estPrioritaire = 1 };

    enfilerColis(&f, a); /* [1] */
    enfilerColis(&f, b); /* [2,1] */
    enfilerColis(&f, c); /* [2,3,1] */
    enfilerColis(&f, d); /* [2,3,1,4] */
    enfilerColis(&f, e); /* [2,3,5,1,4] */

    Colis *x = traiterColis(&f); /* traite 2 */
    free(x);
    x = traiterColis(&f);        /* traite 3 */
    free(x);

    libererFile(&f); /* libère le reste */
    return 0;
}