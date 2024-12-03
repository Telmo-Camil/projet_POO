#include "Grille.h"
#include "Constants.h"
#include "Interface.h" // Inclusion pour la fonction renderGrid
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std; 
using namespace sf; // Regroupe toutes les classes, fonctions, et types de la bibliothèque SFML

int main() {
    Grille grille(gridWidth, gridHeight);

    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } catch (const exception &e) {
        cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grille.mettreAJour();         // Actualise l'état de la grille
        renderGrid(window, grille);  // Affiche la grille mise à jour
        sleep(milliseconds(100)); // Pause entre les itérations
    }

    return 0;
}
