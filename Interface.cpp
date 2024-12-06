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

void renderGrid(RenderWindow &window, const Grille &grille) {
    window.clear();  // Efface l'écran

    RectangleShape cell(Vector2f(1.0f, 1.0f));  // Une cellule logique de 1x1
    cell.setScale(10, 10);  // Échelle de la cellule

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x, y);  // Position logique de la cellule

            if (grille.obtenirCellule(x, y).estObstacle()) {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::Red : Color::Blue);
            } else {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::White : Color::Black);
            }
            window.draw(cell);
        }
    }

    window.display();  // Affiche le rendu
}
