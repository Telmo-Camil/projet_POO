#include "Grille.h"
#include "Constants.h"
#include "Interface.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

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
        grille.afficherConsole();    // Affiche la grille sur le terminal
        renderGrid(window, grille);  // Affiche la grille mise à jour sur l'interface graphique
        sf::sleep(sf::milliseconds(100)); // Pause entre les itérations
    }

    return 0;
}
