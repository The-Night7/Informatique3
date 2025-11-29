/*
EXERCICE 2 - QUESTION 1
   Compilation : gcc TD10_01.c -o sig
   Exécution   : ./sig
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Fonction handler : sera exécutée quand le signal est reçu */
void gestionnaire_signal(int sig) {
    printf("\nAh ah ! J'ai intercepté le signal %d (SIGINT/Ctrl+C).\n", sig);
    printf("Je refuse de m'arrêter !\n");
    // On ne met pas exit() ici, donc le programme continue.
}

int main() {
    /*
       Association du signal SIGINT (Ctrl+C) à la fonction 'gestionnaire_signal'.
       Désormais, faire Ctrl+C ne tuera plus le programme.
    */
    signal(SIGINT, gestionnaire_signal);

    printf("Programme lancé (PID: %d).\n", getpid());
    printf("Essayez de me tuer avec Ctrl+C...\n");

    /* Boucle infinie pour garder le programme en vie */
    while(1) {
        printf("Je tourne...\n");
        sleep(2);
    }

    return 0;
}

/*
   REPONSES AUX QUESTIONS :
   1. Que se passe-t-il avec Ctrl+C ?
      -> Le programme affiche le message du gestionnaire et continue de tourner.

   2. Comment le stopper définitivement ?
      -> Méthode 1 : Utiliser le signal SIGQUIT (Ctrl + \) qui est plus fort que Ctrl+C par défaut.
      -> Méthode 2 : Ouvrir un autre terminal et utiliser SIGKILL : kill -9 <PID>
*/
