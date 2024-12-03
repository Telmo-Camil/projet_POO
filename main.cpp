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
    } catch (const exception &e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }

    RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        grille.mettreAJour();         // Actualise l'état de la grille
        grille.afficherConsole();    // Affiche la grille sur le terminal
        renderGrid(window, grille);  // Affiche la grille mise à jour sur l'interface graphique
        sleep(milliseconds(100)); // Pause entre les itérations
    }

    return 0;
}
