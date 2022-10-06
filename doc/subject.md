# Projet de C : Annuaire et tri de données

### Introduction

L'objectif du projet cette année est de mettre en place un gestionnaire de données du type `Prénom, Nom, Code Postal;`. La première partie définit une structure données qui n'est autre qu'une liste chaînée dans laquelle ces informations seront stockées. La deuxième partie lit se concentre sur la lecture des données depuis un fichier et de structuration intelligente au chargement. La troisième partie utilise une structure de données plus optimisée, une liste chaînée de listes chaînées. La quatrième partie définit plusieurs requêtes sur la structure de données. 

Un squelette du projet vous est proposé et contient :

- une structure de projet C à respecter avec son `makefile` dédié
- `list.h`, le header contenant la première structure ainsi que les signatures des fonctions à créer
- `list.c`, le fichier à compléter avec vos fonctions
- `main.c`, le fichier qui permet de s'interfacer avec vos fonctions (et d'y écrire vos tests !)
- `data`, le dossier dans lequel plusieurs bases de données vous sont proposées, à noter que nous testerons votre projet avec des bases de données différentes mais équivalentes



### Première partie : Structure de données

Les structure de données `list` et `cell`  vous sont données et permettent de définir une liste chaînées de personnes à partir de leurs informations : nom, prénom et code postal (ou `fname`, `lname` et `zip`).

(1) Écrire une fonction `make_cell` qui crée une cellule à partir des informations de ses champs.

(2) Écrire une fonction `print_cell` capable d'afficher le contenu d'une cellule sous la forme `[prénom, nom, code postal]`.

(3) Écrire une fonction `print_list` capable d'afficher le contenu d'une liste sous la forme `{[prénom 1, nom 1, code postal 1], [prénom 2, ...] ...}`.

(4) A partir de celles-ci, écrire une fonction `push` dont la signature vous est donnée qui ajoute une cellule en tête de liste.

(5) Écrire une fonction `pop` dont la signature vous est donnée qui enlève la cellule en tête de liste et renvoie le pointeur vers sa valeur.

### Deuxième partie : Lecture de données

Il faut maintenant lire les données depuis un fichier et les ajouter dynamiquement dans votre structure. Les fichiers présents dans le répertoire `data` peuvent vous servir de tests pour vos fonctions.

(1) Écrire une fonction `make_cell_from_line` qui crée une cellule à partir d'une ligne de données.

(2) Écrire une fonction `load_file` qui ajoute toutes les données d'un fichier dans votre liste.

(3) Écrire une fonction `compare_cells` qui compare deux cellules selon leur nom de famille (puis prénom si égaux) par ordre alphabétique.

(4) Écrire une fonction `insert` qui ajoute une nouvelle donnée au bon endroit (selon l'ordre défini ci-dessus) dans la structure de données. Modifier votre fonction `load_file` pour utiliser cette nouvelle fonctionnalité.

### Troisième partie : Structure de données optimisée

Nous allons maintenant utiliser une liste chaînée de liste chaînées, la première représentant les premières lettres des noms de famille, pour accélérer l'accès aux données et l'ajout d'une nouvelle donnée.

(1) Définir votre structure et votre nouveau type de cellule.

(2) Définir les fonctions  `load_file`,  `insert` et `compare_cells` dédiées à votre nouveau type de données. 

(3) En utilisant les fichiers les plus volumineux, mesurer le temps de création total des deux structures de données.

(4) Réécrire les données dans un nouveau format qui stocke écrit un fichier binaire composé de :

```
<caractere><nombres de cellules dans la structure>
<structure>
<structure>
...
<caractere><nombres de cellules dans la structure>
<structure>
<structure>
...
```



