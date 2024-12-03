#include "Grille.h"
#include "Constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    Grille grille(gridWidth, gridHeight);

    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    grille.afficherConsole();

    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        grille.mettreAJour();
        grille.afficherConsole();

        sf::sleep(sf::milliseconds(500)); // Pause entre les itérations
    }

    return 0;
}
