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
Ce modèle va nous aider à mettre en place le test unitaire.

## Test Unitaire
> **Dans l'énoncé, on nous demande d'intégrer à notre programme une fonction de test unitaire capable de vérifier la validité de la grille calculée à une itération t.**

Le test unitaire sera effectué dans le mode console, où grâce aux dossiers comprenant toutes les itérations, il sera plus simple de comparer le résultat attendu avec ceux obtenus. Nous pouvions intégrer des librairies ou s'y prendre manuellement, nous avons choisi la seconde option pour une meilleure réduction de la mémoire (puisque qu'une bibliothèque occupe beaucoup de place). Nous expliquerons un peu plus tard dans ce livrable quelle fonction effectue ce test, mais nous avons également rajouté des commentaires pour la rendre plus compréhensible. Dans notre programme, nous avons implémenté une fonction permettant de créer un dossier pour chaque itération effectué par l'algorithme. Le test unitaire fera alors en sorte de comparer le changement d'état des cellules entre chaque itération afin de vérifier si le comportement des cellules correspond aux règles définis par le jeu. Le test renverra alors une erreur si les cellules ne respecte pas les règles ou bien une validation si tout est bon.

# Paradigme Objet 
> **Ce processus correspond à l'approche que nous utiliserons pour structurer et organiser le code et exprimer les solutions aux problèmes posés par notre projet.**

## Impératif
**Ce type de paradigme spécifie les étapes que le programme doit suivre pour atteindre un résultat.**

## Déclaratif
**Celui-ci met l’accent sur le résultat souhaité plutôt que sur les étapes pour y parvenir.** \
\
Dans notre cas, nous utilisons le paradigme impératif. En effet, c'est à lui que correspond la POO (expliquée plus en détail dans l'autre Livrable), puisqu'elle est asée sur les objets qui contiennent des données (attributs) et des fonctions (méthodes). 
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
| **Simplicité dans un projet structuré** | Réduit la complexité de la gestion des objets tout en s'intégrant bien avec l’architecture MVC. |

***
# Programme
\
Nous avons rajouté des commentaires au-dessus des fonctions et sur certaines lignes dans le programme afin de les expliquer. Ici, nous détaillerons un peu plus ce qui ne sera pas explicable sous forme de commentaires. \
Nous avons décidé de rajouter l'extension des cellules obstacles, dont les conditions étaient : "L’état des cellules obstacles n’évolue pas au cours de l’exécution. Ces dernières possèdent un état vivant ou mort. Modifiez votre code, sans altérer le fonctionnement de base." \
Pour plus de simplicité, nous présenterons toutes les méthodes à la fois dans chaque classe. \
*Le concept de classes est plus détaillé dans l'autre Livrable* 

> * **Fichiers Headers (.h) :** C'est là que seront réalisées les déclarations initiales des classes, fonctions et variables, permettant leur utilisation dans d'autres fichiers sans révéler leur implémentation. 
> * **Fichiers Sources (.cpp) :** Ils utilisent les définitions des fonctions et classes mises en place dans les fichiers headers. 
> * **Inclusions** : Dans notre programme, nous allons devoir importer le contenu de fichiers extérieurs (les headers) ou de bibliothèques pour utiliser leurs fonctionnalités ou classes. Si une librairie est intégrée dans un fichier inclus, il n'est pas nécessaire de la réinclure car elle est déjà disponible. 


Voici la version mise à jour avec la gestion du test unitaire lors du mode console :

---

## Cellule
- **Private** (Accessible uniquement dans cette classe) :
  - `bool vivant` : Renvoyant 1 ou `True` si la cellule est vivante, et 0 ou `False` si elle est morte.
  - `bool prochainEtat` : Variable qui stocke l'état futur de la cellule, `True` (vivante) ou `False` (morte).
  - `TypeCellule type` : Type de la cellule.

- **Public** (Accessible depuis d'autres classes) :
  - `enum TypeCellule { NORMALE, OBSTACLE }` : Va permettre de mettre en place deux types de cellules, des normales, et des obstacles.
  - `bool estVivante()` : Renvoie une cellule vivante.
  - `bool estObstacle()` : Renvoie une cellule de type `OBSTACLE`.
  - `bool obstacleVivante()` : Renvoie une cellule de type `OBSTACLE` et vivante (elle ne pourra pas mourir).
  - `void definirProchainEtat()` : Définit le prochain état de la cellule en fonction de son type.
  - `void appliquerProchainEtat()` : Applique ce nouvel état (si elle n'est pas un obstacle).

---

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
  - `const Cellule &obtenirCellule(int x, int y)` : Renvoie une référence constante à une cellule (pour la lecture).
  - `Cellule &obtenirCellule(int x, int y)` : Renvoie une référence modifiable à une cellule.
  - `bool verifierGrilleApresIteration(const Grille &attendue)` : Compare une grille calculée après une itération avec une grille attendue (test unitaire).

---

## Interface
- **Public** :
  - `void renderGrid(RenderWindow &window, const Grille &grille, int tailleCellule)` : Affiche graphiquement la grille sur une fenêtre SFML donnée. Les couleurs dépendent de l'état des cellules (vivante, morte, obstacle).

---

## ModeSimulation
- **Private** :
  - `bool modeGraphique` : Indique si le mode graphique est activé (`true`) ou non (`false`).
  - `int maxIterations` : Nombre maximum d'itérations pour la simulation.
  - `static ModeSimulation *instance` : Singleton pour garantir qu'il n'y a qu'une seule instance de cette classe.
  - `ModeSimulation(bool graphique, int iterations)` : Constructeur privé (utilisé pour le Singleton).
  - `void lancerConsole(Grille &grille, const std::string &dossierSortie)` : Gère le mode console en sauvegardant chaque itération dans un dossier regroupant un fichier texte par itération.
  - `void lancerGraphique(Grille &grille)` : Gère le mode graphique et affiche chaque itération sur une interface SFML.
  - `void creerDossierIncremente(const std::string &baseNom, std::string &nouveauNom)` : Crée un nouveau dossier unique pour sauvegarder les résultats à chaque exécution.
  - `void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille)` : Écrit l'état actuel de la grille dans les fichiers textes.
  - **Nouveau :** `void lancerTestUnitaire(Grille &grille, const std::string &dossierSortie)` : Compare les résultats d'itérations sauvegardées dans un dossier spécifique.

- **Public** :
  - `static ModeSimulation *getInstance(bool graphique, int iterations)` : Fournit l'instance unique Singleton de la classe.
  - `void lancer(Grille &grille, const std::string &nomFichierEntree)` : Détermine et lance le mode console ou graphique en fonction de `modeGraphique`.

---

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
    - `3` : Test unitaire intégré avec sauvegarde automatique.

- **Sélection du mode** :
  - **Mode console** :
    - Appel de `ModeSimulation::getInstance(false, maxIterations)->lancer(grille, fichierEntree);`.
    - Passe `false` pour indiquer qu’il s’agit du mode console.
    - Passe la grille et le nom du fichier pour gérer la simulation et créer les fichiers de sortie.

  - **Mode graphique** :
    - Affiche un message à l’utilisateur l’informant qu’il peut ajuster la vitesse des itérations avec les flèches haut et bas.
    - Appel de `ModeSimulation::getInstance(true, maxIterations)->lancer(grille, fichierEntree);`.
    - Passe `true` pour indiquer qu’il s’agit du mode graphique.

  - **Test unitaire (dans le mode console)** :
    - Les résultats calculés sont comparés automatiquement à des grilles attendues générées au cours des itérations.
    - Les résultats de comparaison sont sauvegardés dans des dossiers incrémentés `test_unitaire_<numéro>`.

  - **Choix invalide** :
    - Si l’utilisateur entre un choix invalide, un message d’erreur est affiché, et le programme se termine.s


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
 
















