#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour system()
#include <sstream> // Pour std::ostringstream
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

//Lancement d'un des deux modes
void ModeSimulation::lancer(Grille &grille, const string &outputPath) {
    if (modeGraphique) {
        lancerGraphique(grille);  
    } else {
        lancerConsole(grille, outputPath);  
    }
}

//Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &outputPath) {
    // Crée un dossier pour les fichiers d'itération
    string commandeMkdir = "mkdir -p " + outputPath;
    if (system(commandeMkdir.c_str()) != 0) {
        cerr << "Erreur : impossible de créer le dossier de sortie." << endl;
        return;
    }

    // Générer un fichier par itération
    for (int i = 0; i < maxIterations; ++i) {
        ostringstream fileName;
        fileName << outputPath << "/iteration_" << i + 1 << ".txt";

        ofstream sortie(fileName.str());
        if (!sortie.is_open()) {
            cerr << "Erreur : impossible de créer le fichier " << fileName.str() << endl;
            return;
        }

        sortie << "Itération " << i + 1 << " :\n";
        ecrireEtatDansFichier(sortie, grille); // Écrit l'état de la grille dans le fichier
        grille.mettreAJour();                 // Met à jour la grille pour l'itération suivante
        sortie.close();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans le dossier : " << outputPath << endl;
}

void ModeSimulation::ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const {
    for (int y = 0; y < grille.obtenirHauteur(); ++y) {
        for (int x = 0; x < grille.obtenirLargeur(); ++x) {
            if (grille.obtenirCellule(x, y).estObstacle()) {
                sortie << (grille.obtenirCellule(x, y).estVivante() ? "O " : "X ");
            } else {
                sortie << (grille.obtenirCellule(x, y).estVivante() ? "1 " : "0 ");
            }
        }
        sortie << '\n';
    }
    sortie << '\n';
}


//Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille) {
    const int cellSize = 10; // Taille des cellules en pixels
    RenderWindow window(VideoMode(grille.obtenirLargeur() * cellSize, grille.obtenirHauteur() * cellSize), "Game of Life");

    for (int i = 0; i < maxIterations; ++i) {
        // Gestion des événements pour permettre la fermeture de la fenêtre
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Affichage de l'état actuel de la grille
        cout << "Itération : " << i + 1 << endl; 
        renderGrid(window, grille, cellSize);   
        grille.mettreAJour();                  
        sleep(milliseconds(100));              
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}


