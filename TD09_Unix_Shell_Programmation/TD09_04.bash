#!/bin/bash

# ==============================================================================
# EXERCICE 4 : TRAITEMENT DES FICHIERS
# ==============================================================================

# --- QUESTION 1 : Commande de base ---
# ls -ail : a (tous), i (inode), l (détails)
# tail -n +2 : supprime la 1ère ligne (le "total X")
# Cette commande est stockée dans une variable pour la Q2.

RAW_DATA=$(ls -ail | tail -n +2)

# --- QUESTION 2 : Problème d'affichage et IFS ---
# Si on fait "for ligne in $RAW_DATA", le shell coupe par défaut sur les ESPACES.
# Constat : L'affichage serait cassé (un mot par ligne).
# Solution : On change l'IFS (Internal Field Separator) pour couper uniquement sur les retours à la ligne.

SAVE_IFS=$IFS
IFS=$'\n'

echo "--- Début de l'analyse ---"

# On boucle sur chaque ligne contenue dans la variable
for ligne in $RAW_DATA
do
    # --- QUESTION 3 & 4 : Filtrage et Variables séparées ---
    # On utilise 'awk' ou 'set' pour découper la ligne courante.
    # Format typique ls -ail :
    # Inode(1) Droits(2) Liens(3) User(4) Group(5) Taille(6) Mois(7) Jour(8) Heure(9) Nom(10)

    # Astuce : on remet l'IFS par défaut temporairement pour découper la ligne en mots
    IFS=$SAVE_IFS
    set -- $ligne # Place chaque mot de la ligne dans $1, $2, $3...

    inode=$1
    droits=$2
    taille=$6
    # Le nom est souvent en $10, mais attention s'il y a des espaces dans la date.
    # Pour simplifier ici, on prend le 10ème argument (nom standard).
    nom=${10}

    # On remet l'IFS à "nouvelle ligne" pour la boucle principale
    IFS=$'\n'

    # --- QUESTION 4 (Type de fichier) ---
    # Le type est le premier caractère des droits (ex: -rw-r--r-- -> type est -)
    # d = directory, - = fichier, l = lien
    type_fichier=${droits:0:1}

    if [ "$type_fichier" == "d" ]; then
        type_lisible="Dossier"
    elif [ "$type_fichier" == "-" ]; then
        type_lisible="Fichier"
    else
        type_lisible="Autre ($type_fichier)"
    fi

    # --- QUESTION 5 : Affichage formalisé ---
    # On ignore les lignes vides ou mal formées si nécessaire
    if [ -n "$nom" ]; then
        echo "Nom: $nom | Type: $type_lisible | Taille: $taille octets | Inode: $inode"
    fi
done

# Restauration de l'IFS global du système (bonne pratique)
IFS=$SAVE_IFS
