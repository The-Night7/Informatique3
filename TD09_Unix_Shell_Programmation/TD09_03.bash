#!/bin/bash

# ==============================================================================
# EXERCICE 3 : TRAITEMENT DES NOTES
# ==============================================================================

# --- QUESTION 2 : Vérifications initiales ---

# Vérifier qu'un paramètre est passé
if [ $# -eq 0 ]; then
    # --- QUESTION 3 : Message sur la sortie d'erreur standard (>&2) ---
    echo "Erreur : Aucun fichier fourni." >&2
    # --- QUESTION 4 : Code d'erreur spécifique ---
    exit 1
fi

FICHIER="$1"

# Vérifier que le fichier existe et est un fichier régulier (-f)
if [ ! -f "$FICHIER" ]; then
    echo "Erreur : Le fichier '$FICHIER' n'existe pas ou n'est pas un fichier standard." >&2
    exit 2
fi

# Vérifier le nombre de lignes (compatibilité)
# On attend au moins 3 lignes (2 lignes d'en-tête + au moins 1 note)
nb_lignes=$(wc -l < "$FICHIER")

if [ "$nb_lignes" -lt 3 ]; then
    echo "Erreur : Le fichier ne contient pas assez de données (min 3 lignes)." >&2
    exit 3
fi

# --- TRAITEMENT ET TRI ---
# 1. 'head -n 2' : Affiche les 2 premières lignes (l'en-tête) telles quelles.
# 2. 'tail -n +3' : Prend le contenu à partir de la ligne 3 (les données).
# 3. 'sort' : Trie les données.
#    -t:  -> Définit le séparateur de champ comme étant ":"
#    -k2  -> Trie sur le 2ème champ (la note)
#    -r   -> Tri inverse (Reverse), du plus grand au plus petit
#    -n   -> Tri numérique (pour que 10 soit > 2, sinon en alphabétique 2 > 10)

echo "=== RÉSULTAT DU TRI ==="
head -n 2 "$FICHIER"
tail -n +3 "$FICHIER" | sort -t: -k2 -rn

# Si tout va bien, on retourne 0
exit 0
