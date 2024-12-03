#include "ModeSimulation.h"
#include "Interface.h"
#include "Constants.h" 
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>


ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (!instance) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

void ModeSimulation::lancer(Grille &grille, const std::string &outputPath) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, outputPath);
    }
}

void ModeSimulation::lancerConsole(Grille &grille, const std::string &outputPath) {
    std::ofstream fichierOut(outputPath);
    if (!fichierOut.is_open()) {
        std::cerr << "Erreur : impossible de créer le fichier de sortie." << std::endl;
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
    std::cout << "Simulation console terminée. Résultats écrits dans " << outputPath << std::endl;
}

void ModeSimulation::lancerGraphique(Grille &grille) {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    int iteration = 0;
    while (window.isOpen() && iteration < maxIterations) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        grille.mettreAJour();
        renderGrid(window, grille); // Affichage graphique
        sf::sleep(sf::milliseconds(100));
        ++iteration;
    }

    std::cout << "Simulation graphique terminée après " << iteration << " itérations." << std::endl;
}
