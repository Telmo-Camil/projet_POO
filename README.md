# Livrable 1 : Programme
TRUONG CANH Zoé ;
CAMILO-MIRANDA Telmo

***Lien GitHub :*** https://github.com/Telmo-Camil/projet_POO

***
# Sommaire
1. Introduction
2. Bibliothèques
3. Architecture MVC
4. Paradigme Objet
5. Design Pattern
6. Programme
7. 

***
# Introduction 
## Contexte
Le but du projet est de réaliser une simulation du Jeu de la vie de John Conway. Il s’agit d’un jeu où une grille 2D contenant des cellules évoluent selon des règles prédéfinies, passant d’un état vivant à mort ou inversement, en fonction de leur voisinage : une cellule morte possédant exactement trois voisines vivantes change d’état ; et une cellule vivante possédant deux ou trois voisines du même type reste ainsi, sinon elle meurt.\
Notre mission sera de faire en sorte d’inclure deux modes que l’utilisateur choisira : un mode console qui génère les états des cellules sur plusieurs itérations, et un mode graphique utilisant SFML pour une visualisation interactive. 

## Livrable
* S’appuyer sur la bibliothèque standard C++ STL.
* Utilisation de la bibliothèque graphique SFML pour le développement de votre interface graphique.
* Le programme implémenté de manière efficace

## Note de Départ
À présent que la structure de notre programme a été mise en place, nous allons pouvoir expliquer la partie programme du Jeu de la Vie. Nous allons suivre les étapes initialisées dans le Livrable 1 afin de terminer l’objectif de notre projet.

## Comment allons-nous procéder ?
À l’aide des diagrammes mis en œuvre lors du Livrable précédent, nous savons de quelle manière est architecturé notre algorithme. Nous avons déjà la composition des classes grâce au diagramme correspondant, mais également à quelles fonctions le programme doit répondre avec les autres diagrammes.
***
# Bibliothèques 
## Définition
**Les bibliothèques sont des ensembles de codes préexistants et réutilisables, qui lorsqu’on les intègre à un programme, donnent accès aux instructions qu’elles mettent en place.**

## iostream 
Permet d’interagir avec l’utilisateur via la console (entrées/sorties).

## Standard STL
La STL (Standard Template Library) est une bibliothèque incluse avec le langage C++ qui fournit des outils génériques comme des conteneurs, des algorithmes, et des itérateurs pour manipuler des données de manière efficace et réutilisable.

## Vector
Nous avons choisi d'utiliser la bibliothèque `<vector>` au lieu des tableaux fournis par la STL car ces derniers sont limités en termes de flexibilité et de gestion dynamique de la taille. Les vecteurs vont permettre une gestion dynamique de la mémoire et des dimensions, ce qui selon nous était bien plus adapté pour manipuler une grille de cellules dont les dimensions peuvent varier. 

## fstream
La bibliothèque `<fstream>` permet de gérer les fichiers de manière à permettre l'enregistrement et le chargement des données de la grille depuis ou vers des fichiers.txt. Nous avons utilisé cette bibliothèque notamment pour ouvrir et lire les données du fichier que nous allons fournir, donc le fichier <`etat_initial.txt`> afin de définir la grille.

## string
La bibliothèque <`string`> permet de manipuler des chaînes de caractères en C++. Les chaînes de caractères de cette bibliothèque permettent d'avoir une approche plus flexible et sécurisée. Elles permettent également de gérer automatiquement la mémoire associée aux chaînes de caractères et d'adapter automatiquement la taille de la chaîne au contenu.

## cstdlib
La bibliothèque <`cstdlib`> permet de fournir des fonctions générales pour la gestion de l'environnement d'exécution et des processus mais aussi pour la manipulation de la mémoire. Elle peut être utilisé notamment pour vérifier si un dossier existe et si ce n'est pas le cas de le créer.

## Graphique SFML
La SFML (Simple and Fast Multimedia Library) est une bibliothèque graphique dédiée au développement multimédia en C++. Elle permet de gérer facilement les interfaces graphiques, les animations, rendant le développement de simulations ou jeux plus accessible.
***
# Architecture MVC
*Concept expliqué dans le Livrable Conception.* \

# Paradigme Objet 
> **Ce processus correspond à l'approche que nous utiliserons pour structurer et organiser le code et exprimer les solutions aux problèmes posés par notre projet.**

## Impératif
**Ce type de paradigme spécifie les étapes que le programme doit suivre pour atteindre un résultat.**

## Déclaratif
**Celui-ci met l’accent sur le résultat souhaité plutôt que sur les étapes pour y parvenir.** \
\
Dans notre cas, nous utilisons le paradigme impératif. En effet, c'est à lui que correspond la POO (expliquée plus en détail dans l'autre Livrable), puisqu'elle est asée sur les objets qui contiennent des données (attributs) et des fonctions (méthodes).

***
# Programme
\
Nous avons rajouté des commentaires au-dessus des fonctions et sur certaines lignes dans le programme afin de les expliquer. Ici, nous détaillerons un peu plus ce qui ne sera pas explicable sous forme de commentaires. \
* Extensions rajoutées :
  * Cellules obstacles, dont les conditions étaient : "L’état des cellules obstacles n’évolue pas au cours de l’exécution. Ces dernières possèdent un état vivant ou mort. Modifiez votre code, sans altérer le fonctionnement de base."
  * Grille torique : "Les cellules placées aux extrémités de la grille sont adjacentes ; en d’autres termes les cellules en colonne 0 sont voisines des cellules en colonne N−1, avec N le nombre de colonnes. Le principe est similaire en ligne.
Pour plus de simplicité, nous présenterons toutes les méthodes à la fois dans chaque classe. \
*Le concept de classes est plus détaillé dans l'autre Livrable* 

> * **Fichiers Headers (.h) :** C'est là que seront réalisées les déclarations initiales des classes, fonctions et variables, permettant leur utilisation dans d'autres fichiers sans révéler leur implémentation. 
> * **Fichiers Sources (.cpp) :** Ils utilisent les définitions des fonctions et classes mises en place dans les fichiers headers. 
> * **Inclusions** : Dans notre programme, nous allons devoir importer le contenu de fichiers extérieurs (les headers) ou de bibliothèques pour utiliser leurs fonctionnalités ou classes. Si une librairie est intégrée dans un fichier inclus, il n'est pas nécessaire de la réinclure car elle est déjà disponible. 


## Cellule

- **Private** (Accessible uniquement dans cette classe) :
  - `bool vivant` : Indique si la cellule est vivante (`true`) ou morte (`false`).
  - `bool prochainEtat` : Stocke l'état futur de la cellule (`true` ou `false`).
  - `TypeCellule type` : Définit si la cellule est de type `NORMALE` ou `OBSTACLE`.

- **Public** (Accessible depuis d'autres classes) :
  - `enum TypeCellule { NORMALE, OBSTACLE }` : Enumération définissant deux types possibles pour les cellules.
  - `Cellule(bool etatInitial = false, TypeCellule type = NORMALE)` : Constructeur pour initialiser une cellule avec son état et son type.
  - `bool estVivante() const` : Renvoie `true` si la cellule est vivante.
  - `bool estObstacle() const` : Renvoie `true` si la cellule est un obstacle.
  - `bool obstacleVivante() const` : Renvoie `true` si la cellule est un obstacle vivant (un obstacle ne peut pas mourir).
  - `void definirProchainEtat(bool etat)` : Définit l'état futur de la cellule, sauf si elle est un obstacle.
  - `void appliquerProchainEtat()` : Applique l'état futur à la cellule, sauf si elle est un obstacle.

---

## Grille

- **Private** :
  - `int largeur` : Largeur de la grille (en nombre de cellules).
  - `int hauteur` : Hauteur de la grille (en nombre de cellules).
  - `std::vector<std::vector<Cellule>> cellules` : Représentation bidimensionnelle de la grille, chaque élément étant une cellule.

  - `int compterVoisinsVivants(int x, int y) const` : Méthode pour compter le nombre de cellules vivantes autour d'une cellule donnée (gestion torique des bords incluse).

- **Public** :
  - `Grille(int l, int h)` : Constructeur pour initialiser une grille avec les dimensions spécifiées (`l` pour la largeur, `h` pour la hauteur).
  - `bool chargerDepuisFichier(const std::string &chemin)` : Charge l'état initial de la grille à partir d'un fichier texte spécifié.
  - `void sauvegarderDansFichier(std::ofstream &fichier) const` : Sauvegarde l'état actuel de la grille dans un fichier texte.
  - `void mettreAJour()` : Met à jour l'état de toutes les cellules de la grille en appliquant les règles du jeu.
  - `void afficherConsole() const` : Affiche l'état actuel de la grille dans la console.
  - `int getLargeur() const` : Renvoie la largeur de la grille.
  - `int getHauteur() const` : Renvoie la hauteur de la grille.
  - `const Cellule &obtenirCellule(int x, int y) const` : Renvoie une référence constante à une cellule donnée pour consultation.
  - `Cellule &obtenirCellule(int x, int y)` : Renvoie une référence modifiable à une cellule donnée.

---

## Interface

- **Public** :
  - `void renderGrid(sf::RenderWindow &window, const Grille &grille, int tailleCellule)` : Fonction pour afficher graphiquement une grille dans une fenêtre SFML donnée. Chaque cellule est affichée sous forme de rectangle dont la couleur dépend de son état (`vivante`, `morte`, ou `obstacle`).

---

## ModeSimulation

- **Private** :
  - `bool modeGraphique` : Variable booléenne indiquant si le mode graphique est activé (`true`) ou non (`false`).
  - `int maxIterations` : Nombre maximal d'itérations que doit exécuter la simulation.
  - `static ModeSimulation *instance` : Singleton pour garantir qu'une seule instance de la classe est créée.
  - `ModeSimulation(bool graphique, int iterations)` : Constructeur privé, utilisé uniquement pour le Singleton.
  - `void lancerConsole(Grille &grille, const std::string &dossierSortie)` : Lance la simulation en mode console et enregistre les états de la grille dans des fichiers texte dans un dossier.
  - `void lancerGraphique(Grille &grille)` : Lance la simulation en mode graphique et affiche les états successifs de la grille dans une fenêtre SFML.

- **Public** :
  - `static ModeSimulation *getInstance(bool graphique, int iterations)` : Fournit une instance unique de la classe en utilisant le pattern Singleton.
  - `void lancer(Grille &grille, const std::string &fichierInitial)` : Lance la simulation en fonction du mode choisi (console ou graphique).

---

## Main

- **Inclusions** :
  - `#include "Grille.h"` : Fournit l'accès à la classe `Grille` pour la gestion de la grille et des cellules.
  - `#include "ModeSimulation.h"` : Fournit l'accès aux modes de simulation (console ou graphique).
  - `#include <iostream>` : Permet d’interagir avec l’utilisateur via des entrées et sorties standard dans la console.

- **Variables** :
  - `string fichierEntree = "etat_initial.txt";` : Spécifie le fichier texte contenant l'état initial de la grille.

- **Initialisation de la grille** :
  - `Grille grille(0, 0);` : Crée une instance de la classe `Grille` avec des dimensions initiales de `0x0`.
  - `grille.chargerDepuisFichier(fichierEntree)` : Charge la configuration initiale de la grille à partir du fichier texte spécifié. Si le chargement échoue, un message d'erreur est affiché, et le programme se termine.

- **Interaction avec l’utilisateur** :
  - `int choixMode` : Permet à l’utilisateur de choisir le mode de fonctionnement :
    - `1` : Mode console.
    - `2` : Mode graphique.

- **Nombre d’itérations** :
  - `int maxIterations` : Nombre maximal d’itérations saisies par l’utilisateur.

- **Sélection du mode** :
  - Appel de `ModeSimulation::getInstance(choixMode == 2, maxIterations)->lancer(grille, fichierEntree);`.
    - Si `choixMode == 2` : Lance le mode graphique.
    - Sinon : Lance le mode console.

***
# Design Pattern
> **Ce sont des patrons de conception qui vont apporter des solutions standardisées pour résoudre des problèmes courants dans le développement d'un programme. 

Nous avons utilisé le Singleton, qui assure qu’une classe n’a qu’une seule instance et fournit un point d’accès global à cette instance. 


| **Critère** | **Pourquoi le Singleton ?** |
| --- | --- |
| **Garantie d'une seule instance** | Nous voulions qu’il n’y ait qu’une seule instance de `ModeSimulation`, qu'elle soit graphique ou console. |
| **Partage global** | L’instance de `ModeSimulation` est accessible partout via `getInstance`, ce qui évite de passer cette instance partout. |
| **Gestion centralisée de l'état** | Le Singleton simplifie le suivi de l’état (mode graphique/console, nombre d’itérations) dans un point unique. |
| **Contrôle sur l’accès** | Avec `getInstance`, nous contrôlons quand et comment l’instance de `ModeSimulation` est créée et utilisée. |
| **Prévention de doublons** | En interdisant la création directe de plusieurs instances, nous évitons des conflits liés à des modes de simulation multiples. |
***
# Makefile

Un makefile va permettre de compiler et exécuter notre programme beaucoup plus rapidement. Il va tout d'abord convertir les les fichiers source en fichiers objets (.o), tout en recompilant seulement les parties du code qui ont été modifiées, ce qui accélère le processus. Avec seulement trois commandes, il permet de :
  * `make` : Compiler le programme.
  * `make clean` : Supprimer les fichiers objets et autres fichiers temporaires pour "nettoyer" le projet.
  * `make run` : Compiler et exécuter directement le programme.

  Voici son explication détaillée :

### 1. Compilation
```makefile
CXX = clang++
```
Définit le compilateur à utiliser, ici `clang++`.

```makefile
CXXFLAGS = -g -Wmost -Werror
```
- `-g` : Ajoute les informations de débogage.
- `-Wmost` : Active la plupart des avertissements pour le compilateur.
- `-Werror` : Traite tous les avertissements comme des erreurs.

```makefile
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
```
Liste des bibliothèques SFML nécessaires pour lier le programme : affichage graphique, gestion des fenêtres, audio, réseau et système.

### 2. Sources et Objets
```makefile
SRCS = main.cpp Interface.cpp Grille.cpp Cellule.cpp ModeSimulation.cpp
```
Définit la liste des fichiers source à compiler.

```makefile
OBJS = $(SRCS:.cpp=.o)
```
Remplace l'extension `.cpp` des fichiers listés dans `SRCS` par `.o` pour créer la liste des fichiers objets.

```makefile
TARGET = main
```
 `main ` sera le nom de l'exécutable final.

### 3. Règles du Makefile
```makefile
all: $(TARGET)
```
Ici, on génère l'exécutable en appelant la règle suivante.

```makefile
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)
```
- Crée l'exécutable `main` :
  - Utilise `clang++` pour lier tous les fichiers objets spécifiés dans `$(OBJS)`.
  - Ajoute les bibliothèques SFML (`$(LDFLAGS)`).
  - Sauvegarde l'exécutable sous le nom `main`.

```makefile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
```
  - `$<` : Représente le fichier source `.cpp` (C++) en cours de compilation.
  - `$@` : Représente le fichier objet `.o` (fichier intermédiaire compilant chaque fichier source individuellement pour ensuite les regrouper).

### 4. Nettoyage
```makefile
clean:
	rm -f $(OBJS) $(TARGET)
```
 Supprime tous les fichiers objets (`$(OBJS)`) et l'exécutable final (`$(TARGET)`).
 ***
 
















