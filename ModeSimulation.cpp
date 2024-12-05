#include "ModeSimulation.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

void ModeSimulation::lancer(Grille &grille, const string &outputPath) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, outputPath);
    }
}

void ModeSimulation::lancerConsole(Grille &grille, const string &outputPath) {
    ofstream sortie(outputPath);
    if (!sortie.is_open()) {
        cerr << "Erreur : impossible d'écrire dans le fichier " << outputPath << endl;
        return;
    }

    for (int i = 0; i < maxIterations; ++i) {
        grille.mettreAJour();
        sortie << "Itération " << i + 1 << " :\n";
        grille.afficherConsole();
    }
    sortie.close();
}

void ModeSimulation::lancerGraphique(Grille &grille) {
    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        grille.mettreAJour();
        renderGrid(window, grille);
    }
}
