#include "ModeSimulation.h"
#include "Interface.h"
#include "Constants.h" 
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (!instance) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

void ModeSimulation::lancer(Grille &grille, const string &FichierSortie) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, FichierSortie);
    }
}

void ModeSimulation::lancerConsole(Grille &grille, const string &FichierSortie) {
    ofstream fichierOut(FichierSortie);
    if (!fichierOut.is_open()) {
        cerr << "Erreur : impossible de créer le fichier de sortie." << endl;
        return;
    }

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        fichierOut << "Iteration " << iteration + 1 << ":\n";
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            for (int x = 0; x < grille.obtenirLargeur(); ++x) {
                fichierOut << (grille.obtenirCellule(x, y).estVivante() ? "1 " : "0 ");
            }
            fichierOut << '\n';
        }
        fichierOut << '\n';
        grille.mettreAJour();
    }
    fichierOut.close();
    cout << "Simulation console terminée. Résultats écrits dans " << FichierSortie << endl;
}

void ModeSimulation::lancerGraphique(Grille &grille) {
    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    int iteration = 0;
    while (window.isOpen() && iteration < maxIterations) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grille.mettreAJour();
        renderGrid(window, grille); // Affichage graphique
        sleep(milliseconds(100));
        ++iteration;
    }

    cout << "Simulation graphique terminée après " << iteration << " itérations." << endl;
}
