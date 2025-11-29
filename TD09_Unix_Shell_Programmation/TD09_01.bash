#!/bin/bash

# ==============================================================================
# EXERCICE 1 : PREMIERS PAS
# ==============================================================================

# --- QUESTION 1 : Correction du snippet ---
# Le code original utilisait des apostrophes simples (quotes) au lieu de backticks `
# ou de la syntaxe $().
# Correction :
# for i in $(seq 1 10)
# do
#    echo "Rock n roll"
# done

# --- QUESTION 2 : Analyse du script ---
# i1=`ls -a`      -> Les backticks exécutent la commande `ls -a`.
#                    La variable i1 contient le RÉSULTAT de la commande (la liste des fichiers).
# i2="grep ..."   -> Les guillemets définissent une chaîne de caractères simple.
#                    La variable i2 contient le TEXTE de la commande, elle n'est pas exécutée.
# echo $i1        -> Affiche la liste des fichiers du dossier.
# echo $i2        -> Affiche littéralement : grep -R ’tutu’ ∼

# --- QUESTION 3 : Script d'arguments ---
# Consigne : Afficher nom, nombre d'args, PID, et valeur de chaque argument.

echo "=== DÉBUT DU SCRIPT ==="

# 1. Afficher son nom
# $0 contient le nom du script tel qu'il a été appelé
echo "Nom du script : $0"

# 2. Afficher le nombre d'arguments
# $# contient le nombre total d'arguments passés
echo "Nombre d'arguments : $#"

# 3. Le numéro du processus courant (PID)
# $$ contient le PID du shell actuel
echo "PID du processus : $$"

# 4. La valeur de chaque argument
# $@ contient la liste de tous les arguments
# On utilise une boucle pour les parcourir un par un
echo "--- Liste des arguments ---"
compteur=1
for arg in "$@"
do
    echo "Argument $compteur : $arg"
    ((compteur++))
done

echo "=== FIN DU SCRIPT ==="
