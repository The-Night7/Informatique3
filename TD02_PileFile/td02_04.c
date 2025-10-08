/* La plupart des traitements de texte ou de calculs sont capables d'analyser la syntaxe et d'indiquer un problème de
 * parenthésage.
 * Pour vérifier qu'un texte/une expression contient des parenthèses correctes, il ne suffit pas que le nombre de
 * parenthèses ouvrantes soit le même que le nombre de parenthèses fermantes : l'ordre dans lequel on rencontre les
 * parenthèses fermantes doit correspondre à l'ordre dans lequel on a rencontré les parenthèses ouvrantes.
 * Exemple : "Je suis Luffy )le futur roi des pirates( !" a un mauvais parenthésage bien qu'il y ait une parenthèse ouvrante et fermante.
 */

/* 1. Quelle structure (tableau, liste chaînée, pile, file) est la plus adaptée pour vérifier le parenthésage d'une phrase ?
 *    Réponse: Une pile est la structure la plus adaptée car elle permet de stocker les parenthèses ouvrantes
 *    et de les comparer avec les parenthèses fermantes dans l'ordre inverse (LIFO).
 *
 * 2. Déclarer ce type de structure qui contiendra des caractères.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Structure de pile pour stocker les caractères
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Initialiser la pile
void initStack(Stack *s) {
    s->top = -1;
}

// Vérifier si la pile est vide
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Vérifier si la pile est pleine
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Empiler un caractère
void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->data[++(s->top)] = c;
    } else {
        printf("Erreur: Pile pleine\n");
    }
}

// Dépiler un caractère
char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0'; // Retourne un caractère nul si la pile est vide
}

// Regarder le sommet de la pile sans dépiler
char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0';
}

/* 3. Ecrire un programme permettant de vérifier le bon parenthèsage d'une chaîne de caractères. */
int verifierParenthesage(char *chaine) {
    Stack pile;
    initStack(&pile);

    for (int i = 0; i < strlen(chaine); i++) {
        if (chaine[i] == '(') {
            push(&pile, chaine[i]);
        } else if (chaine[i] == ')') {
            if (isEmpty(&pile)) {
                return 0; // Parenthèse fermante sans ouvrante correspondante
            }
            pop(&pile);
        }
    }

    return isEmpty(&pile); // Retourne 1 si toutes les parenthèses sont correctement fermées
}

/* 4. Faire de même pour des phrases pouvant contenir deux types de symboles : les parenthèses "()" et les crochets "[]". */
int verifierParenthesageMultiple(char *chaine) {
    Stack pile;
    initStack(&pile);

    for (int i = 0; i < strlen(chaine); i++) {
        if (chaine[i] == '(' || chaine[i] == '[') {
            push(&pile, chaine[i]);
        } else if (chaine[i] == ')') {
            if (isEmpty(&pile) || peek(&pile) != '(') {
                return 0; // Parenthèse fermante sans ouvrante correspondante ou mauvais type
            }
            pop(&pile);
        } else if (chaine[i] == ']') {
            if (isEmpty(&pile) || peek(&pile) != '[') {
                return 0; // Crochet fermant sans ouvrant correspondant ou mauvais type
            }
            pop(&pile);
        }
    }

    return isEmpty(&pile); // Retourne 1 si tous les symboles sont correctement fermés
}

int main() {
    char expression[MAX_SIZE];

    printf("Entrez une expression mathématique: ");
    fgets(expression, MAX_SIZE, stdin);

    // Supprimer le caractère de nouvelle ligne si présent
    if (expression[strlen(expression) - 1] == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }

    printf("\nTest de parenthésage simple:\n");
    if (verifierParenthesage(expression)) {
        printf("Le parenthésage est correct.\n");
    } else {
        printf("Le parenthésage est incorrect.\n");
    }

    printf("\nTest de parenthésage multiple (parenthèses et crochets):\n");
    if (verifierParenthesageMultiple(expression)) {
        printf("Le parenthésage multiple est correct.\n");
    } else {
        printf("Le parenthésage multiple est incorrect.\n");
    }

    return 0;
}
