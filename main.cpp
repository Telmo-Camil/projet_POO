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

    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    const int maxIterations = 500; 
    int iteration = 0;

    while (window.isOpen() && iteration < maxIterations) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grille.mettreAJour();         // Actualise la grille
        renderGrid(window, grille);  // Affiche la grille dans SFML
        sleep(milliseconds(100));    // Pause entre les mises à jour

        ++iteration; // Incrémente le compteur d'itérations
    }

    // Affiche un message lorsque la simulation se termine
    cout << "Simulation terminée après " << iteration << " itérations." << endl;

    return 0;
}
