#include <stdio.h>
#include <stdlib.h>

/*
 * Nous allons simuler le passage de clients d'un supermarché en caisse de paiement. Chaque client sera simulé par un
 * entier contenant le nombre d'articles de son caddy. Le but de cet exercice sera d'afficher l'ensemble des caddys des
 * clients en train de patienter à une caisse.
*/

/* 1. Quelle structure (tableau, liste chaînée, pile, file) semble la plus appropriée pour ce type d'exercice ?
 * La structure la plus adaptée serait alors la file pour ce type d'exercice. */

// 2. Déclarer ce type de structure avec comme type d'élément un entier.
typedef struct Node {
    int articles;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialisation de la file
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Ajouter un client à la file
void enqueue(Queue* queue, int articles) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    newNode->articles = articles;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Retirer un client de la file
int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return -1; // File vide
    }

    Node* temp = queue->front;
    int articles = temp->articles;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return articles;
}

// Vérifier si la file est vide
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}
/* 3. Créer une fonction qui va créer une instance d'un client avec une valeur entière aléatoire entre 1 et 50
 * (simulant le nombre d'articles dans son caddy). */
int createClient() {
    return (rand() % 50) + 1;
}

// 4. Créer une fonction qui va afficher tous les clients dans l'ordre d'arrivée en caisse.
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Aucun client en caisse\n");
        return;
    }

    Node* current = queue->front;
    printf("Clients en caisse: ");
    while (current != NULL) {
        printf("%d ", current->articles);
        current = current->next;
    }
    printf("\n");
}
/* 5. Créer un programme qui va simuler l'arrivée de clients à la caisse :
 * — Ajouter 3 clients en caisse 1
 * — Dans une boucle infinie, au début de chaque tour, on enlève le client le plus proche de la caisse (le prochain à
 * payer ses achats), si il existe
 * — Ensuite il y a 33% de chances d'ajouter de nouveaux clients en caisse
 * — Si on ajoute des clients, suite au point précédent, on en ajoute entre 1 et 3 (de manière aléatoire)
 * — A la fin de la boucle on affiche le client qui a payé ses achats et on affiche en dessous le reste des clients
 * (dans l'ordre d'arrivée à la caisse)
 * — Si il n'y a plus de clients en caisse, on arrête le programme */
int main() {
    srand(time(NULL));

    Queue* caisse = createQueue();

    // Ajouter 3 clients en caisse
    for (int i = 0; i < 3; i++) {
        enqueue(caisse, createClient());
    }

    printf("État initial de la caisse:\n");
    displayQueue(caisse);

    while (!isEmpty(caisse)) {
        // Enlever le client le plus proche de la caisse
        int clientServi = dequeue(caisse);
        printf("\nClient servi: %d articles\n", clientServi);

        // 33% de chances d'ajouter de nouveaux clients
        if (rand() % 3 == 0) {
            int nouveauxClients = (rand() % 3) + 1; // Entre 1 et 3 nouveaux clients
            printf("Arrivée de %d nouveaux clients:\n", nouveauxClients);

            for (int i = 0; i < nouveauxClients; i++) {
                int articles = createClient();
                enqueue(caisse, articles);
                printf("- Nouveau client avec %d articles\n", articles);
            }
        }

        // Afficher l'état actuel de la caisse
        printf("\nÉtat actuel de la caisse:\n");
        displayQueue(caisse);

        // Petite pause pour voir l'évolution
        printf("Appuyez sur Entrée pour continuer...");
        getchar();
    }

    printf("\nPlus de clients en caisse. Fin du programme.\n");

    return 0;
}

/* 6. Proposer un algorithme pour modifier le programme précédent de la façon suivante :
 * — En commençant par les clients les plus proches de la caisse, déterminer ceux qui voudraient changer de caisse si
 * la somme des articles des autres clients situés devant dépasse un certain seuil
 * — Est ce que la structure choisie est appropriée pour ce type de calcul ? Justifier la réponse. */

/*
 * Algorithme proposé:
 * 1. Définir un seuil (par exemple 100 articles)
 * 2. Pour chaque client dans la file:
 *      a. Calculer la somme des articles des clients devant lui
 *      b. Si cette somme dépasse le seuil, marquer ce client comme "voulant changer de caisse"
 *      c. Déplacer ces clients vers une autre caisse
 *
 * La structure de file n'est pas optimale pour ce type de calcul car:
 *      - Pour accéder aux clients au milieu de la file, nous devons parcourir tous les clients précédents
 *      - Pour calculer la somme des articles devant un client, nous devons parcourir la file depuis le début jusqu'à ce client
 *      - Pour retirer un client du milieu de la file, nous devons reconstruire les liens de la liste chaînée
 *
 * Une structure plus appropriée serait une liste doublement chaînée ou un tableau dynamique, qui permettrait:
 *      - Un accès plus facile à n'importe quel client
 *      - Une suppression plus simple d'un client au milieu
 *      - Un calcul plus efficace des sommes cumulatives
 */
