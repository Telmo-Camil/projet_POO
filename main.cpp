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
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }

    grille.afficherConsole();

    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grille.mettreAJour();
        grille.afficherConsole();

        sleep(milliseconds(500)); // Pause entre les itérations
    }

    return 0;
}
