#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Constants.h"
#include "Grille.h"

using namespace std; 
using namespace sf;

vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

void initializeGrid() {
    srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = rand() % 2;  // Randomly initialize cells as alive or dead
        }
    }
}

void renderGrid(RenderWindow &window, const Grille &grille) {
    window.clear();
    RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            if (grille.obtenirCellule(x, y).estVivante()) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(Color::Green); // Couleur pour une cellule vivante
                window.draw(cell);
            } else {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(Color::Black); // Couleur pour une cellule morte
                window.draw(cell);
            }
        }
    }

    window.display();
}
