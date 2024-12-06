#include "Interface.h"
#include <SFML/Graphics.hpp>
#include "Grille.h"

using namespace sf;

void renderGrid(sf::RenderWindow &window, const Grille &grille, int cellSize) {
    window.clear();  // Efface l'écran

    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));  // Taille logique de la cellule

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x * cellSize, y * cellSize);

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
