#include "Cellule.h"
#include "Grille.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

// Les constantes et la grille doivent être cohérentes avec le code fourni
extern const int cellSize;
extern const int gridWidth;
extern const int gridHeight;
extern std::vector<std::vector<int>> grid;

// Prototypes des fonctions existantes dans le code fourni
void initializeGrid();
void renderGrid(sf::RenderWindow &window);

// Nouvelle fonction pour charger la grille depuis un fichier
bool loadGridFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    int height, width;
    file >> height >> width;

    if (height != gridHeight || width != gridWidth) {
        std::cerr << "Erreur : Les dimensions du fichier (" << width << "x" << height
                  << ") ne correspondent pas à celles du programme (" << gridWidth
                  << "x" << gridHeight << ")" << std::endl;
        return false;
    }

    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            if (!(file >> grid[x][y])) {
                std::cerr << "Erreur : Données insuffisantes dans le fichier." << std::endl;
                return false;
            }
        }
    }

    return true;
}

// Main qui utilise le code fourni
int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    // Charger la grille depuis un fichier
    if (!loadGridFromFile("etat_initial.txt")) {
        std::cerr << "Chargement échoué. Terminaison du programme." << std::endl;
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Utilisation de la fonction existante `renderGrid`
        renderGrid(window);

        sf::sleep(sf::milliseconds(100)); // Pause pour ralentir l'affichage
    }

    return 0;
}
