#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* Lire attentivement toutes les questions de l'exercice avant de démarrer.
 * Dans cet exercice, toute la gestion des structures doit se faire obligatoirement via des pointeurs. De plus il ne doit y
 * avoir aucun tableau statique : quelles que soient leurs tailles, toutes les zones mémoires (tableaux, structures, ...) doivent
 * être allouées dynamiquement, et libérées lorsqu'elles ne sont plus utilisées.
 * Le but de cet exercice est de développer un programme en C qui gère une playlist musicale. L'utilisateur de l'application
 * confectionne lui-même sa playlist et peut rajouter des musiques à tout moment. Sauf cas particulier, les morceaux seront
 * joués en respectant l'ordre d'ajout de l'utilisateur.
 * 1. Justifier l'utilisation d'une file dynamique comme meilleur choix pour implementer la playlist. */

// Une file dynamique servira à passer les musiques dans l'ordre dans lequel elles ont étés ajoutés et pouvoir en ajouter un nombre indéfini.
// De plus, une file permet d'ajouter efficacement des éléments à la fin et de retirer des éléments au début, ce qui correspond
// parfaitement au comportement d'une playlist où on ajoute des morceaux à la fin et on les joue depuis le début.

/* 2. Déclarer une structure Musique qui devra contenir uniquement les informations suivantes :
 * — titre : le titre de la chanson.
 * — artiste : le nom de l'artiste.
 * — temps : la durée de la chanson en secondes.
 * — fav : une variable indiquant si la musique est dans les favoris de l'utilisateur. */

typedef struct {
    char* titre;
    char* artiste;
    int temps;
    bool fav;
} Musique;

/* 3. Déclarer la ou les structures permettant de gérer au mieux une file de Musique (une playlist) */

typedef struct Chainon {
    Musique* contenu;
    struct Chainon* next;
    struct Chainon* previous;
} Chainon;

typedef struct {
    Chainon* first;
    Chainon* last;
    int nbChansons;  // Pour garder trace du nombre de chansons
} Playlist;
/* 4. Implementer une fonction/procédure dureePlaylist(...) qui va retourner le temps total de lecture (en secondes)
 * d'une playlist passée en paramètre, et va également retourner le nombre de chansons qui constituent cette playlist. */

int dureePlaylist(Playlist* p, int* nbChansons) {
    int duree = 0;
    *nbChansons = 0;
    Chainon* m = p->first;
    while (m != NULL) {
        duree += m->contenu->temps;
        (*nbChansons)++;
        m = m->next;
    }
    return duree;
}

/* 5. Ecrire une procédure ajoutMusique(...) qui prend en paramètre une playlist et une Musique et qui ajoute cette
 * musique à la fin de la playlist. */

void ajoutMusique(Playlist* p, Musique* musique) {
    // Créer un nouveau chainon
    Chainon* nouveau = (Chainon*)malloc(sizeof(Chainon));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }

    // Copier la musique
    nouveau->contenu = musique;
    nouveau->next = NULL;
    nouveau->previous = p->last;

    // Ajouter à la fin de la playlist
    if (p->last == NULL) {
        // Liste vide
        p->first = nouveau;
        p->last = nouveau;
    } else {
        p->last->next = nouveau;
        p->last = nouveau;
    }

    p->nbChansons++;
}

/* 6. Ecrire une fonction jouerMusique(...) qui va retirer de la file la prochaine Musique à jouer, afficher toutes ses
 * informations et la retourner à la fonction appelante. */

Musique* jouerMusique(Playlist* p) {
    if (p->first == NULL) {
        printf("La playlist est vide\n");
        return NULL;
    }

    // Récupérer la première musique
    Chainon* premier = p->first;
    Musique* musique = premier->contenu;

    // Afficher les informations
    printf("Lecture en cours : %s par %s (%d secondes)\n",
           musique->titre, musique->artiste, musique->temps);
    printf("Favori : %s\n", musique->fav ? "Oui" : "Non");

    // Retirer la musique de la playlist
    p->first = premier->next;
    if (p->first == NULL) {
        p->last = NULL;  // La playlist est maintenant vide
    } else {
        p->first->previous = NULL;
    }

    p->nbChansons--;

    // Libérer le chainon (mais pas la musique qui est retournée)
    free(premier);

    return musique;
}
/* 7. Ecrire une procédure aleatoire(...) qui va faire en sorte de mélanger les musiques d'une playlist passée en paramètre.
 * Le mélange des musiques se fera de la manière suivante :
 * — enlever une musique en la défilant simplement de la file.
 * — ajouter cette musique dans une autre liste, aléatoirement soit en début, soit en fin.
 * — Une fois toutes les musiques traitées, la playlist passée en paramètre contient toutes les musiques mélangées. */

void aleatoire(Playlist* p) {
    if (p->first == NULL || p->first == p->last) {
        return;  // Playlist vide ou avec une seule musique
    }

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Créer une nouvelle playlist temporaire
    Playlist temp = {NULL, NULL, 0};

    // Traiter toutes les musiques de la playlist originale
    while (p->first != NULL) {
        // Enlever une musique de la playlist originale
        Musique* musique = jouerMusique(p);

        // Créer un nouveau chainon
        Chainon* nouveau = (Chainon*)malloc(sizeof(Chainon));
        if (nouveau == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            return;
        }

        nouveau->contenu = musique;

        // Ajouter aléatoirement en début ou en fin
        if (rand() % 2 == 0) {
            // Ajouter en début
            nouveau->next = temp.first;
            nouveau->previous = NULL;
            if (temp.first != NULL) {
                temp.first->previous = nouveau;
            } else {
                temp.last = nouveau;
            }
            temp.first = nouveau;
        } else {
            // Ajouter en fin
            nouveau->next = NULL;
            nouveau->previous = temp.last;
            if (temp.last != NULL) {
                temp.last->next = nouveau;
            } else {
                temp.first = nouveau;
            }
            temp.last = nouveau;
        }

        temp.nbChansons++;
    }

    // Remplacer la playlist originale par la playlist mélangée
    *p = temp;
}

/* 8. Ecrire une fonction/procédure changePosition(...) qui prend en paramètre une playlist et une Musique, et qui décale
 * cette musique d'un cran vers la fin de la liste (cette musique échange sa place avec la musique qui suit). */

bool changePosition(Playlist* p, Musique* musique) {
    if (p->first == NULL || p->first == p->last) {
        return false;  // Playlist vide ou avec une seule musique
    }

    // Rechercher la musique dans la playlist
    Chainon* courant = p->first;
    while (courant != NULL && courant->contenu != musique) {
        courant = courant->next;
    }

    // Vérifier si la musique a été trouvée et si elle n'est pas la dernière
    if (courant == NULL || courant->next == NULL) {
        return false;  // Musique non trouvée ou déjà à la fin
    }

    // Échanger avec la musique suivante
    Chainon* suivant = courant->next;

    // Mettre à jour les liens
    if (courant->previous != NULL) {
        courant->previous->next = suivant;
    } else {
        p->first = suivant;  // courant était le premier élément
    }

    if (suivant->next != NULL) {
        suivant->next->previous = courant;
    } else {
        p->last = courant;  // suivant était le dernier élément
    }

    courant->next = suivant->next;
    suivant->previous = courant->previous;
    courant->previous = suivant;
    suivant->next = courant;

    return true;
}

/* 9. Ecrire une fonction/procédure favoris(...) qui prend en paramètre une playlist et qui va conserver uniquement les
 * musiques qui sont marquées comme favorites. Les autres musiques sont retirées de la liste. */

void favoris(Playlist* p) {
    Chainon* courant = p->first;

    while (courant != NULL) {
        Chainon* suivant = courant->next;

        if (!courant->contenu->fav) {
            // Supprimer ce chainon car la musique n'est pas favorite
            if (courant->previous != NULL) {
                courant->previous->next = courant->next;
            } else {
                p->first = courant->next;  // C'était le premier élément
            }

            if (courant->next != NULL) {
                courant->next->previous = courant->previous;
            } else {
                p->last = courant->previous;  // C'était le dernier élément
            }

            // Libérer la mémoire
            free(courant);
            p->nbChansons--;
        }

        courant = suivant;
    }
}
