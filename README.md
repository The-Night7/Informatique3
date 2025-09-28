# 📚 Informatique 3 - TDs Pré-ING2

> **CY Tech - Semestre 1 2023/2024**  
> Collection complète des travaux dirigés en structures de données et programmation système

---

## 🎯 Vue d'ensemble

Ce dépôt contient l'ensemble des **10 TDs** du cours d'Informatique 3, couvrant les structures de données fondamentales et la programmation système Unix. Chaque TD est accompagné d'exercices pratiques et d'implémentations en langage C.

## 📋 Table des matières

### 🔗 **Structures de données**

|   TD   | Sujet                                                                   | Concepts clés                                          | Difficulté |
|:------:|-------------------------------------------------------------------------|--------------------------------------------------------|:----------:|
| **01** | [Listes chaînées](TD01_ListesChainees/Info3_TD01_ListesChainees.pdf)    | Allocation dynamique, pointeurs, insertion/suppression |     ⭐⭐     |
| **02** | [Piles et Files (1)](TD02_PileFile/Info3_TD02_PileFile.pdf)             | LIFO/FIFO, implémentation dynamique                    |     ⭐⭐     |
| **03** | [Piles et Files (2)](TD03_PileFileListes/Info3_TD03_PileFileListes.pdf) | Listes doublement chaînées, tri de crêpes              |    ⭐⭐⭐     |
| **04** | [Arbres](TD04_Arbres/Info3_TD04_Arbres.pdf)                             | Arbres binaires, parcours, notation polonaise          |    ⭐⭐⭐     |
| **05** | [Arbres Binaires de Recherche](TD05_ABR/Info3_TD05_ABR.pdf)             | ABR, insertion/suppression, recherche                  |    ⭐⭐⭐     |
| **06** | [Arbres AVL](TD06_AVL/Info3_TD06_AVL.pdf)                               | Auto-équilibrage, rotations, facteur d'équilibrage     |    ⭐⭐⭐⭐    |

### 🐧 **Programmation système Unix**

| TD | Sujet                                                                                         | Concepts clés | Difficulté |
|:--:|-----------------------------------------------------------------------------------------------|---------------|:----------:|
| **07** | [Commandes Unix](TD07_Unix_Shell_Commandes/Info3_TD07_Unix_Shell_Commandes.pdf)               | Navigation, fichiers, permissions, alias | ⭐⭐ |
| **08** | [Redirections et Filtrage](TD8_Unix_Shell_Redirections/Info3_TD8_Unix_Shell_Redirections.pdf) | Pipes, redirections, filtres (grep, cut, sort) | ⭐⭐⭐ |
| **09** | [Programmation Shell](TD09_Unix_Shell_Programmation/Info3_TD09_Unix_Shell_Programmation.pdf)  | Scripts bash, variables, structures de contrôle | ⭐⭐⭐ |
| **10** | [Processus](TD10_Unix_Shell_Processus/Info3_TD10_Unix_Shell_Processus.pdf)                    | Gestion des processus, signaux, jobs | ⭐⭐⭐ |

## 🛠️ Compilation et exécution

### Pour les TDs C (01-06)
```bash
# Compilation
gcc -o nom_executable nom_programme.c

# Exécution
./nom_executable
```

### Pour les TDs Unix (07-10)
```bash
# Rendre un script exécutable
chmod +x script.sh

# Exécution
./script.sh
```

## 📁 Structure du dépôt

```
Info3-TDs/
├── TD01_ListesChainees/
│   ├── exercice1.c
│   ├── exercice2.c
│   └── ...
├── TD02_PileFile/
│   ├── pile_dynamique.c
│   ├── file_simulation.c
│   └── ...
├── TD07_Unix_Commandes/
│   ├── navigation.sh
│   ├── permissions.sh
│   └── ...
└── ...
```

## 🎓 Exercices phares

### 🏆 **Incontournables**
- **TD01 Ex1** : Liste des puissances de deux
- **TD02 Ex3** : Simulation de clients en supermarché
- **TD03 Ex2** : Algorithme de tri de crêpes 🥞
- **TD04 Ex4** : Notation polonaise inversée
- **TD05 Ex2** : Construction d'un ABR complet
- **TD06 Ex2** : Implémentation AVL avec rotations

### 🔥 **Défis avancés**
- **TD03** : Tri de crêpes avec spatule
- **TD04** : Évaluation d'expressions arithmétiques
- **TD06** : Double rotations AVL
- **TD09** : Scripts de traitement de fichiers

## 💡 Conseils pratiques

### 🎯 **Pour réussir les TDs**
- **Structures de données** : Dessinez vos structures avant de coder
- **Pointeurs** : Vérifiez toujours les allocations/libérations mémoire
- **Unix** : Testez chaque commande étape par étape
- **Shell** : Utilisez `echo` pour déboguer vos scripts

### ⚠️ **Pièges courants**
- Fuites mémoire dans les listes chaînées
- Gestion des cas limites (listes vides, arbres vides)
- Oubli des facteurs d'équilibrage dans les AVL
- Permissions insuffisantes sur les scripts Unix

## 🔧 Outils recommandés

- **IDE/Éditeur** : VS Code, CLion, ou vim
- **Débogueur** : gdb pour le C
- **Vérification mémoire** : valgrind
- **Terminal** : bash ou zsh

## 📖 Ressources complémentaires

- [Cours magistral Informatique 3](https://cours.cyu.fr/course/view.php?id=376#module-5355)
- [Documentation GCC](https://gcc.gnu.org/onlinedocs/)
- [Guide Bash](https://www.gnu.org/software/bash/manual/)
- [Référence Unix/Linux](https://man7.org/linux/man-pages/)

## 🤝 Contribution

Les améliorations et corrections sont les bienvenues ! N'hésitez pas à :
- Signaler des erreurs
- Proposer des optimisations
- Ajouter des commentaires explicatifs

---

<div align="center">

**🎓 Bon courage pour vos TDs ! 🎓**

*"La programmation est un art, les structures de données en sont les pinceaux"*

[![Made with ❤️](https://img.shields.io/badge/Made%20with-❤️-red.svg)](https://github.com)
[![CY Tech](https://img.shields.io/badge/CY%20Tech-Pré--ING2-blue.svg)](https://cytech.cyu.fr)

</div>