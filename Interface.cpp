#include "Interface.h"
#include <SFML/Graphics.hpp>
#include "Grille.h"

using namespace sf;

// Fonction pour afficher la grille dans une fenêtre graphique
void renderGrid(RenderWindow &window, const Grille &grille, int tailleCellule) {
    window.clear(); // Nettoyer la fenêtre avant de redessiner

    // Création d'un rectangle représentant une cellule
    RectangleShape cell(Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));

    // Parcours de toutes les cellules de la grille
    for (int x = 0; x < grille.getLargeur(); ++x) {  // Utilisation de getLargeur()
        for (int y = 0; y < grille.getHauteur(); ++y) {  // Utilisation de getHauteur()
            cell.setPosition(x * tailleCellule, y * tailleCellule);  // Positionnement de la cellule

            // Définir la couleur selon l'état de la cellule
            const Cellule &cellule = grille.obtenirCellule(x, y);  // Lecture de la cellule
            if (cellule.estObstacle()) {
                cell.setFillColor(cellule.estVivante() ? Color::Red : Color::Blue); // Obstacle vivant ou mort
            } else {
                cell.setFillColor(cellule.estVivante() ? Color::White : Color::Black); // Cellule normale
            }

            window.draw(cell); // Dessiner la cellule dans la fenêtre
        }
    }

    window.display(); // Met à jour l'affichage de la fenêtre
}
