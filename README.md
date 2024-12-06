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
Nom de l'exécutable final.

### 3. Règles du Makefile
```makefile
all: $(TARGET)
```
Règle par défaut. Génère l'exécutable `main` en appelant la règle suivante.

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
- Règle générique pour compiler les fichiers `.cpp` en fichiers `.o` :
  - `$<` : Représente le fichier source `.cpp` en cours de compilation.
  - `$@` : Représente le fichier objet `.o` correspondant.

### 4. Nettoyage
```makefile
clean:
	rm -f $(OBJS) $(TARGET)
```
 Supprime tous les fichiers objets (`$(OBJS)`) et l'exécutable final (`$(TARGET)`).
















