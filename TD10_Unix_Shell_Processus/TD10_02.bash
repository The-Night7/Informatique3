#!/bin/bash

# ==============================================================================
# EXERCICE 2 - QUESTION 2
# ==============================================================================

echo "Démarrage du script (PID: $$)"

# --- MISE EN PLACE DU TRAP ---
# La commande 'trap' permet d'exécuter une commande quand un signal est reçu.
# Ici, on intercepte SIGTSTP (qui correspond à Ctrl+Z).
trap 'echo " -> Essai de pause (Ctrl+Z) intercepté ! Je continue !"' SIGTSTP

echo "Essayez de me mettre en pause avec Ctrl+Z..."

# Boucle infinie
compteur=1
while true
do
    echo "Tour de boucle $compteur"
    sleep 2
    ((compteur++))
done

# --- REPONSES AUX QUESTIONS ---
# 1. Que se passe-t-il avec Ctrl+Z ?
#    -> Le script affiche le message défini dans le 'trap' et continue l'exécution
#       au lieu de se mettre en état "Stopped".

# 2. Comment faire pour le mettre en pause pour de vrai ?
#    -> Le signal SIGTSTP (envoyé par le terminal) peut être intercepté.
#    -> Le signal SIGSTOP (envoyé par la commande kill) NE PEUT PAS être intercepté.
#    -> Solution : Ouvrir un autre terminal et taper : kill -STOP <PID_DU_SCRIPT>
