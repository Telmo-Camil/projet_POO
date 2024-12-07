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

***
# Introduction 
## Contexte
Le but du projet est de réaliser une simulation du Jeu de la vie de John Conway. Il s’agit d’un jeu où une grille 2D contenant des cellules évoluent selon des règles prédéfinies, passant d’un état vivant à mort ou inversement, en fonction de leur voisinage. Notre mission sera de faire en sorte d’inclure deux modes que l’utilisateur choisira : un mode console qui génère les états des cellules sur plusieurs itérations, et un mode graphique utilisant SFML pour une visualisation interactive. 

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

## Iostream 
Permet d’interagir avec l’utilisateur via la console (entrées/sorties).

## Standard STL
La STL (Standard Template Library) est une bibliothèque incluse avec le langage C++ qui fournit des outils génériques comme des conteneurs, des algorithmes, et des itérateurs pour manipuler des données de manière efficace et réutilisable.

* ### Conteneur
Classes fournies par la STL pour stocker, organiser et manipuler des collections d'éléments de manière efficace.

* ### Itérateurs
Objet qui permet de parcourir les éléments d’une collection de manière séquentielle, similaire à un pointeur, tout en respectant l’encapsulation des données.

## Graphique SFML
La SFML (Simple and Fast Multimedia Library) est une bibliothèque graphique dédiée au développement multimédia en C++. Elle permet de gérer facilement les interfaces graphiques, les animations, rendant le développement de simulations ou jeux plus accessible.
***
# Architecture MVC
*Concept expliqué dans le Livrable Conception.* \
Ce modèle va nous aider à mettre en place le test unitaire.

## Test Unitaire
> **Dans l'énoncé, on nous demande d'intégrer à notre programme une fonction de test unitaire capable de vérifier la validité de la grille calculée à une itération t.**

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
Nous avons décidé de rajouter l'extension des cellules obstacles, dont les conditions étaient : "L’état des cellules obstacles n’évolue pas au cours de l’exécution. Ces dernières possèdent un état vivant ou mort. Modifiez votre code, sans altérer le fonctionnement de base." \
Pour plus de simplicité, nous présenterons toutes les méthodes à la fois dans chaque classe. \
\
*Le concept de classes est plus détaillé dans l'autre Livrable* \
\
> **Fichiers Headers (.h) :** C'est là que seront réalisées les déclarations initiales des classes, fonctions et variables, permettant leur utilisation dans d'autres fichiers sans révéler leur implémentation. \

> **Fichiers Sources (.cpp) :** Ils utilisent les définitions des fonctions et classes mises en place dans les fichiers headers. \

> **Inclusions** : Dans notre programme, nous allons devoir importer le contenu de fichiers extérieurs (les headers) ou de bibliothèques pour utiliser leurs fonctionnalités ou classes. Si une librairie est intégrée dans un fichier inclus, il n'est pas nécessaire de la réinclure car elle est déjà disponible. \
\

## Cellule
- **Private** (Accessible uniquement dans cette classe) :
  - `bool vivant` : Renvoyant 1 ou `True` si la cellule est vivante, et 0 ou `False` si elle est morte.
  - `bool prochainEtat` :  Variable qui stocke l'état futur de la cellule, `True` (vivante) ou `False` (morte).
  - `TypeCellule type` : Type de la cellule

- **Public** (Accessible depuis d'autres classes) :
  - `enum TypeCellule { NORMALE, OBSTACLE }` : Va permettre de mettre en place deux types de cellules, des normales, et des obstacles.  
  - `bool estVivante()` : Renvoie une cellule vivante.
  - `bool estObstacle()` : Renvoie une cellule de type `OBSTACLE`.
  - `bool obstacleVivante()` : Renvoie une cellule de type `OBSTACLE` et vivante (elle ne pourra pas mourir).
  - `void definirProchainEtat()` : Définit le prochain état de la cellule en fonction de son type.
  - `void appliquerProchainEtat()` : Applique ce nouvel état (si elle n'est pas un obstacle).

***
## Grille
- **Private** :
  - `int largeur` : Largeur de la grille en nombre de cellules.
  - `int hauteur` : Hauteur de la grille en nombre de cellules.
  - `std::vector<std::vector<Cellule>> cellules` : Grille bidimensionnelle stockant les cellules.

- **Public** :
  - `Grille(int l, int h)` : Initialise la grille avec les dimensions `l` (largeur) et `h` (hauteur).
  - `bool chargerDepuisFichier(const std::string &chemin)` : Charge l'état initial de la grille depuis un fichier texte.
  - `void mettreAJour()` : Met à jour chaque cellule de la grille en fonction des règles du jeu.
  - `void afficherConsole()` : Affiche l'état de la grille dans la console.
  - `int obtenirLargeur()` : Renvoie la largeur de la grille. 
  - `int obtenirHauteur()` : Renvoie la hauteur de la grille.
  => Pour ces deux méthodes, nous en avons besoin puisque la largeur et la hauteur sont en privé et donc inaccessibles depuis d'autres classes. Ici, grâce à ces méthodes, on n'a plus ce problème-là.  
  - `const Cellule &obtenirCellule(int x, int y)` : Renvoie une référence constante à une cellule (pour la lecture).
  - `Cellule &obtenirCellule(int x, int y)` : Renvoie une référence modifiable à une cellule.

---

## Interface
- **Public** :
  - `void renderGrid(RenderWindow &window, const Grille &grille, int tailleCellule)` : Affiche graphiquement la grille sur une fenêtre SFML donnée. Les couleurs dépendent de l'état des cellules (vivante, morte, obstacle).

---

## ModeSimulation
- **Private** s:
  - `bool modeGraphique` : Indique si le mode graphique est activé (`true`) ou non (`false`).
  - `int maxIterations` : Nombre maximum d'itérations pour la simulation.
  - `static ModeSimulation *instance` : Singleton pour garantir qu'il n'y a qu'une seule instance de cette classe.
  - `ModeSimulation(bool graphique, int iterations)` : Constructeur privé (utilisé pour le Singleton).
  - `void lancerConsole(Grille &grille, const std::string &dossierSortie)` : Gère le mode console en sauvegardant chaque itération dans un dossier regroupant un fichier texte par itération.
  - `void lancerGraphique(Grille &grille)` : Gère le mode graphique et affiche chaque itération sur une interface SFML.
  - `void creerDossierIncremente(const std::string &baseNom, std::string &nouveauNom)` : Crée un nouveau dossier unique pour sauvegarder les résultats à chaque exécution.
  - `void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille)` : Écrit l'état actuel de la grille dans les fichiers textes.

- **Public** :
  - `static ModeSimulation *getInstance(bool graphique, int iterations)` : Fournit l'instance unique Singleton de la classe.
  - `void lancer(Grille &grille, const std::string &nomFichierEntree)` : Détermine et lance le mode console ou graphique en fonction de `modeGraphique`.

***
## Main

## Main

- **Inclusions** :
  - `#include "Grille.h"` : Donne accès à la classe `Grille` pour gérer la grille.
  - `#include "ModeSimulation.h"` : Donne accès aux modes de simulation (console ou graphique).
  - `#include <iostream>` : Permet d’interagir avec l’utilisateur via la console (entrées/sorties).

- **Variables** :
  - `string fichierEntree = "etat_initial.txt";` : Spécifie le nom du fichier texte qui contient l’état initial de la grille.

- **Initialisation de la grille** :
  - `Grille grille(0, 0);` : Crée une instance de la classe `Grille` avec des dimensions initiales de `0x0`.
  - `grille.chargerDepuisFichier(fichierEntree)` : Charge la configuration de la grille à partir du fichier `etat_initial.txt`. Si le chargement échoue, un message d’erreur est affiché, et le programme se termine.

- **Interaction avec l’utilisateur** :
  - `int choixMode` : Variable pour stocker le choix de l’utilisateur entre les deux modes :
    - `1` : Mode console.
    - `2` : Mode graphique.
  - `int maxIterations` : Variable pour stocker le nombre maximum d’itérations que l’utilisateur souhaite exécuter.

- **Sélection du mode** :
  - **Mode console** :
    - Appel de `ModeSimulation::getInstance(false, maxIterations)->lancer(grille, fichierEntree);`.
    - Passe `false` pour indiquer qu’il s’agit du mode console.
    - Passe la grille et le nom du fichier pour gérer la simulation et créer les fichiers de sortie.

  - **Mode graphique** :
    - Affiche un message à l’utilisateur l’informant qu’il peut ajuster la vitesse des itérations avec les flèches haut et bas.
    - Appel de `ModeSimulation::getInstance(true, maxIterations)->lancer(grille, fichierEntree);`.
    - Passe `true` pour indiquer qu’il s’agit du mode graphique.

  - **Choix invalide** :
    - Si l’utilisateur entre un choix invalide, un message d’erreur est affiché, et le programme se termine.


***
# Makefile

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
Ici, cela génère l'exécutable en appelant la règle suivante.

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
 
















