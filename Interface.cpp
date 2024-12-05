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

void renderGrid(sf::RenderWindow &window, const Grille &grille) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            const Cellule &cellule = grille.obtenirCellule(x, y);
            cell.setPosition(x * cellSize, y * cellSize);

            if (cellule.estObstacle()) {
                if (cellule.obstacleVivante()) {
                    cell.setFillColor(sf::Color::Blue);  
                } else {
                    cell.setFillColor(sf::Color::Red);  
                }
            } else if (cellule.estVivante()) {
                cell.setFillColor(sf::Color::White);  
            } else {
                cell.setFillColor(sf::Color::Black);  
            }

            window.draw(cell);
        }
    }
    window.display();
}s




