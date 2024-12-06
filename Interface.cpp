#include "Interface.h"
#include <SFML/Graphics.hpp>
#include "Grille.h"

using namespace sf;

void renderGrid(RenderWindow &window, const Grille &grille, int cellSize) {
    window.clear(); // Efface l'écran

    RectangleShape cell(Vector2f(cellSize, cellSize)); // Cellule de la taille spécifiée

    // Parcours des cellules de la grille
    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x * cellSize, y * cellSize); // Position de la cellule

            // Définir la couleur de la cellule en fonction de son état
            if (grille.obtenirCellule(x, y).estObstacle()) {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::Red : Color::Blue);
            } else {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::White : Color::Black);
            }

            window.draw(cell);
        }
    }

    window.display(); 
