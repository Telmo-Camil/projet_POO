#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Interface.h"
#include "Constants.h"
#include "Grille.h"

using namespace std; 
using namespace sf;

vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

void initializeGrid() {
    srand(time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = rand() % 2;  
        }
    }
}

void renderGrid(RenderWindow &window, const Grille &grille) {
    window.clear();
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f)); // Taille ajustée pour un espacement
    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            if (grille.obtenirCellule(x, y).estVivante()) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(Color::White);  // Cellule vivante = blanche
                window.draw(cell);
            } else {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(Color::Black);  // Cellule morte = noire
                window.draw(cell);
            }
        }
    }
    window.display();
}




