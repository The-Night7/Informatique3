#!/bin/bash

# ==============================================================================
# EXERCICE 5 : COMPARAISON DE FICHIERS
# ==============================================================================

# --- CONSIGNE 1 : Vérification des paramètres ---
# Il faut obligatoirement 2 arguments.

if [ $# -ne 2 ]; then
    echo "Usage: $0 <fichier1> <fichier2>" >&2
    exit 2
fi

F1="$1"
F2="$2"

# Vérification que ce sont bien des fichiers
if [ ! -f "$F1" ] || [ ! -f "$F2" ]; then
    echo "Erreur : L'un des arguments n'est pas un fichier valide." >&2
    exit 2
fi

# --- CONSIGNE 2 : Calcul de signature (Hash) ---
# On utilise md5sum (ou sha1sum).
# md5sum renvoie "HASH  nom_fichier". On utilise 'cut' pour ne garder que le hash.

hash1=$(md5sum "$F1" | cut -d' ' -f1)
hash2=$(md5sum "$F2" | cut -d' ' -f1)

# Comparaison des chaînes de caractères
if [ "$hash1" == "$hash2" ]; then
    echo "Les fichiers sont identiques."
    exit 0
else
    # Message d'erreur sur la sortie standard d'erreur
    echo "Erreur : Les fichiers sont différents." >&2
    echo "Hash 1: $hash1" >&2
    echo "Hash 2: $hash2" >&2
    exit 1
fi

# --- CONSIGNE 3 : Existe-t-il un moyen plus simple ? ---
# OUI.
# Unix possède des commandes dédiées à la comparaison :
# 1. 'diff' : Affiche les différences ligne par ligne.
#    Usage : diff fichier1 fichier2
# 2. 'cmp' : Compare octet par octet (plus rapide pour les binaires).
#    Usage : cmp -s fichier1 fichier2 (ne retourne rien, juste un code de sortie 0 ou 1)
#
# Dans un script, on écrirait simplement :
# if cmp -s "$1" "$2"; then
#    echo "Pareil"
# else
#    echo "Différent"
# fi
