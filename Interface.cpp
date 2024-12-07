#include "Interface.h"
#include <SFML/Graphics.hpp>
#include "Grille.h"

using namespace sf;

void renderGrid(RenderWindow &window, const Grille &grille, int tailleCellule) {
    window.clear();  // Efface l'écran

    RectangleShape cell(Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));  // Taille logique de la cellule

    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x * tailleCellule, y * tailleCellule);

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
