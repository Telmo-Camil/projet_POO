#include "Interface.h"
#include <SFML/Graphics.hpp>
#include "Grille.h"

using namespace sf;

// Affiche la grille dans une fenêtre graphique
void renderGrid(RenderWindow &window, const Grille &grille, int tailleCellule) {
    window.clear();  // Nettoie la fenêtre avant de redessiner

    // Rectangle représentant une cellule
    RectangleShape cell(Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));

    // Parcours de toutes les cellules de la grille
    for (int x = 0; x < grille.obtenirLargeur(); ++x) {
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            cell.setPosition(x * tailleCellule, y * tailleCellule);  // Positionner la cellule

            // Définir la couleur selon le type et l'état de la cellule
            if (grille.obtenirCellule(x, y).estObstacle()) {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::Red : Color::Blue);
            } else {
                cell.setFillColor(grille.obtenirCellule(x, y).estVivante() ? Color::White : Color::Black);
            }

            window.draw(cell);  // Dessiner la cellule dans la fenêtre
        }
    }

    window.display();  // Met à jour l'affichage de la fenêtre
}
