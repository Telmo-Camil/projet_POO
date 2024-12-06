#include "Interface.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std; 
using namespace sf;

vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

//Initialiser la Grille avec les tailles fournies
void initializeGrid() {
    srand(time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = rand() % 2;  
        }
    }
}

void renderGrid(RenderWindow &window, const Grille &grille, int cellSize) {
    window.clear();  // Efface l'écran pour préparer le rendu

    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));  // Cellule de taille fournie
    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x * cellSize, y * cellSize);  // Positionner les cellules

            // Déterminer la couleur en fonction de l'état de la cellule
            if (grille.obtenirCellule(x, y).estObstacle()) {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::Red : Color::Blue);
            } else {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::White : Color::Black);
            }

            window.draw(cell);  
        }
    }

    window.display();  
}
