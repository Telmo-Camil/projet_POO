#include "Grille.h"
#include "Constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std; 
using namespace sf; //regroupe toutes les classes, fonctions, et types de la bibliothèque SFML

int main() {
    Grille grille(gridWidth, gridHeight);

    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        grille.mettreAJour();         // Actualise l'état de la grille
        renderGrid(window, grille);  // Affiche la grille mise à jour
        sf::sleep(sf::milliseconds(100)); // Pause entre les itérations
    }

    return 0;
}

