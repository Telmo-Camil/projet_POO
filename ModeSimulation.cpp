#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

void ModeSimulation::lancer(Grille &grille, const string &outputPath) {
    if (modeGraphique) {
        lancerGraphique(grille);  // Appel au mode graphique
    } else {
        lancerConsole(grille, outputPath);  // Appel au mode console
    }
}

//Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &outputPath) {
    ofstream sortie(outputPath);
    if (!sortie.is_open()) {
        cerr << "Erreur : impossible de créer le fichier de sortie." << endl;
        return;
    }

    for (int i = 0; i < maxIterations; ++i) {
        grille.afficherConsole();  
        grille.mettreAJour();    
        sortie << "Itération " << i + 1 << " :\n";
        grille.afficherConsole();r
    }

    sortie.close();
    cout << "Simulation terminée. Résultats sauvegardés dans : " << outputPath << endl;
}

//Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille) {
    const int cellSize = 10; // Taille des cellules en pixels
    RenderWindow window(VideoMode(grille.obtenirLargeur() * cellSize, grille.obtenirHauteur() * cellSize), "Game of Life");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grille.mettreAJour();  
        renderGrid(window, grille, cellSize); // Passe la taille des cellules ici
        sleep(milliseconds(100));  
    }
}

