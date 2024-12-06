#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Interface.h"
#include "Grille.h"

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

void renderGrid(sf::RenderWindow &window, const Grille &grille) {
    window.clear();  // Efface l'écran pour préparer le rendu

    sf::RectangleShape cell(sf::Vector2f(1.0f, 1.0f));  // Cellule de taille logique 1x1
    cell.setScale(cellSize, cellSize);  //Agrandir les cellules de la taille donnée

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x, y);  // Position des cellules

            //Couleur en fonction de l'état de la cellule
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
