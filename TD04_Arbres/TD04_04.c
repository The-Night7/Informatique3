/* La notation polonaise inversée (NPI) (utilisée par les calculatrices Texas Instrument entre autres) permet d'écrire de façon
 * non ambiguë les formules arithmétiques sans utiliser de parenthèses. Le principe est que les opérandes précèdent toujours
 * leurs opérateurs et peuvent être eux-mêmes des nombres ou des expressions non triviales.
 * Exemples 1 + 2 s'écrit en notation polonaise 1 2+
 * ((1 + 2) ∗ 4) + 3 s'écrit 1 2 + 4 ∗ 3+
 * a
 * a + b
 * s'écrit a a b + /
 * Dans cet exercice, nous abordons comment construire une notation polonaise à l'aide d'arbre binaire. Chaque noeud de
 * cet arbre contiendra une opérande ou un nombre.
 * On considère les structures suivantes :
 * Struture Terme
 * typeTerme : Caractere
 * valeur : Reel
 * Structure Arbre
 * terme : Structure Terme
 * fg, fd : Pointeur sur Structure Arbre
 * Le champs typeTerme survira à définir les opérandes ; il ne pourra prendre que les valeurs suivantes : '+', '-', 'x' , ' /' et
 * '='.
 * Si typeTerme vaut '=' c'est que le noeud permet de stocker un nombre. Si ce n'est pas le cas, le champs valeur vaudra 0.
 * Chaque noeud interne contient un opérateur binaire et son fils à gauche et son fils à droite sont respectivement l'expression
 * à gauche de l'opérande et l'expression à droite de l'expression. Les feuilles sont donc forcément des constantes.
 * 1. Quelle est l'écriture en NPI du calcul suivant ? 5 ∗ ((a + 1) ∗ (b + 1)) / (a + b)
 * 2. Quelle est la valeur de l'expression polonaise inversée suivante : 1 8 2 – 7 4 – * 3 6 + / / ?
 * 3. L'expression ((3 − 4) ∗ 2 + 3) s'écrit sous forme d'arbre comme suit :
 *
 *          (+,0)
 *           / \
 *       (*,0) (=,3)
 *        / \
 *    (-,0) (=,2)
 *     / \
 * (=,3) (=,4)
 *
 * La notation polonaise inverse de ce calcul est 3 4 − 2 ∗ 3 +
 * À quel type de parcours d'arbre correspond la notation polonaise inversée ?
 * 4. A partir des structures définies ci-dessus et des fonctions écrites lors des exercices précédents, construire l'arbre representé ci-dessus.
 * 5. Écrire la procédure void afficherNotationPolonaiseInversee (pArbre a) qui permet d'afficher en notation polonaise
 * inversée l'expression mathématique définie dans l'arbre binaire.
 * 6. Écrire la fonction float eval (pArbre a) qui permet donner le résultat de l'expression mathématique définie dans
 * l'arbre binaire. La tester avec l'arbre puis pour vérifier votre réponse à la question 2.
 */

#include <stdio.h>
#include <stdlib.h>

// Définition des structures
typedef struct Terme {
    char typeTerme;  // '+', '-', 'x', '/' ou '='
    float valeur;    // valeur si typeTerme == '='
} Terme;

typedef struct Arbre {
    Terme terme;
    struct Arbre *fg;
    struct Arbre *fd;
} Arbre;

typedef Arbre* pArbre;

// Fonction pour créer un nouveau nœud
pArbre creerNoeud(char type, float valeur) {
    pArbre nouveau = (pArbre)malloc(sizeof(Arbre));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    nouveau->terme.typeTerme = type;
    nouveau->terme.valeur = (type == '=') ? valeur : 0;
    nouveau->fg = NULL;
    nouveau->fd = NULL;
    return nouveau;
}

// Question 4: Construction de l'arbre ((3 - 4) * 2 + 3)
pArbre construireArbreExemple() {
    // Création des feuilles (nombres)
    pArbre trois1 = creerNoeud('=', 3);
    pArbre quatre = creerNoeud('=', 4);
    pArbre deux = creerNoeud('=', 2);
    pArbre trois2 = creerNoeud('=', 3);

    // Création des opérateurs
    pArbre moins = creerNoeud('-', 0);
    moins->fg = trois1;
    moins->fd = quatre;

    pArbre mult = creerNoeud('*', 0);
    mult->fg = moins;
    mult->fd = deux;

    pArbre plus = creerNoeud('+', 0);
    plus->fg = mult;
    plus->fd = trois2;

    return plus;
}

// Question 5: Affichage en notation polonaise inversée
void afficherNotationPolonaiseInversee(pArbre a) {
    if (a == NULL) return;

    // Parcours infixe gauche
    afficherNotationPolonaiseInversee(a->fg);

    // Parcours infixe droit
    afficherNotationPolonaiseInversee(a->fd);

    // Traitement du nœud courant
    if (a->terme.typeTerme == '=') {
        printf("%.1f ", a->terme.valeur);
    } else {
        printf("%c ", a->terme.typeTerme);
    }
}

// Question 6: Évaluation de l'expression
float eval(pArbre a) {
    if (a == NULL) return 0;

    // Si c'est une feuille (un nombre)
    if (a->terme.typeTerme == '=') {
        return a->terme.valeur;
    }

    // Sinon, c'est un opérateur
    float gauche = eval(a->fg);
    float droite = eval(a->fd);

    switch (a->terme.typeTerme) {
        case '+': return gauche + droite;
        case '-': return gauche - droite;
        case '*': return gauche * droite;
        case 'x': return gauche * droite;  // Autre notation pour la multiplication
        case '/':
            if (droite == 0) {
                printf("Erreur: Division par zéro\n");
                exit(1);
            }
            return gauche / droite;
        default:
            printf("Opérateur non reconnu: %c\n", a->terme.typeTerme);
            exit(1);
    }
}

// Fonction pour évaluer l'expression polonaise inversée de la question 2
float evaluerExpressionQ2() {
    // Expression: 1 8 2 – 7 4 – * 3 6 + / /
    // Construisons l'arbre correspondant

    pArbre un = creerNoeud('=', 1);
    pArbre huit = creerNoeud('=', 8);
    pArbre deux = creerNoeud('=', 2);
    pArbre sept = creerNoeud('=', 7);
    pArbre quatre = creerNoeud('=', 4);
    pArbre trois = creerNoeud('=', 3);
    pArbre six = creerNoeud('=', 6);

    pArbre moins1 = creerNoeud('-', 0);
    moins1->fg = huit;
    moins1->fd = deux;

    pArbre moins2 = creerNoeud('-', 0);
    moins2->fg = sept;
    moins2->fd = quatre;

    pArbre mult = creerNoeud('*', 0);
    mult->fg = moins1;
    mult->fd = moins2;

    pArbre plus = creerNoeud('+', 0);
    plus->fg = trois;
    plus->fd = six;

    pArbre div1 = creerNoeud('/', 0);
    div1->fg = mult;
    div1->fd = plus;

    pArbre div2 = creerNoeud('/', 0);
    div2->fg = un;
    div2->fd = div1;

    return eval(div2);
}

// Fonction principale pour tester
int main() {
    // Construction de l'arbre exemple
    pArbre arbre = construireArbreExemple();

    // Affichage en notation polonaise inversée
    printf("Notation polonaise inversée de ((3 - 4) * 2 + 3): ");
    afficherNotationPolonaiseInversee(arbre);
    printf("\n");

    // Évaluation de l'expression
    printf("Résultat de l'évaluation: %.2f\n", eval(arbre));

    // Évaluation de l'expression de la question 2
    printf("Résultat de l'expression de la question 2: %.2f\n", evaluerExpressionQ2());

    return 0;
}
