#!/bin/bash

# ==============================================================================
# EXERCICE 2 : PROPRIÉTÉS ET COMPTAGE
# ==============================================================================

# --- QUESTION 3 : Vérification de l'argument ---
# Le script doit être appelé avec un seul argument qui est un répertoire.

# On vérifie si le nombre d'arguments ($#) est différent de 1 (-ne)
if [ $# -ne 1 ]; then
    echo "Erreur : Vous devez fournir exactement un argument."
    echo "Usage : $0 <nom_du_repertoire>"
    exit 1
fi

# On stocke l'argument dans une variable pour la lisibilité
DOSSIER="$1"

# On vérifie si l'argument est bien un répertoire (-d)
if [ ! -d "$DOSSIER" ]; then
    echo "Erreur : '$DOSSIER' n'est pas un répertoire valide."
    exit 1
fi

echo "Analyse du dossier : $DOSSIER"
echo "-----------------------------------"

# --- QUESTION 4 & 5 : Lister exécutables et afficher taille ---
# On boucle sur tous les fichiers contenus dans le dossier ($DOSSIER/*)
for fichier in "$DOSSIER"/*
do
    # Vérification que le fichier existe (cas des dossiers vides)
    if [ -e "$fichier" ]; then

        # Test : est-ce un fichier exécutable ? (-x)
        # Note : Les dossiers sont aussi "exécutables" (traversables).
        # Il faut donc vérifier que ce n'est PAS un dossier (! -d).
        if [ -x "$fichier" ] && [ ! -d "$fichier" ]; then

            # Récupération de la taille.
            # 'stat -c %s' donne la taille en octets (compatible Linux standard).
            # Alternative portable : wc -c < "$fichier"
            taille=$(stat -c %s "$fichier" 2>/dev/null || wc -c < "$fichier")

            echo "Fichier exécutable trouvé : $(basename "$fichier")"
            echo "   -> Taille : $taille octets"
        fi
    fi
done
