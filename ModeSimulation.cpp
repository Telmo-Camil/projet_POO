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
void ModeSimulation::lancerConsole(Grille &grille, const std::string &dossier) {
    std::cout << "Les fichiers seront enregistrés dans le dossier : " << dossier << std::endl;

    // Écriture des fichiers par itération
    for (int i = 0; i < maxIterations; ++i) {
        // Nom du fichier pour cette itération
        std::string fichierSortie = dossier + "_iteration_" + std::to_string(i + 1) + ".txt";

        // Création/écriture dans le fichier
        std::ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            std::cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << std::endl;
            return;
        }

        sortie << "Itération " << i + 1 << " :\n";
        ecrireEtatDansFichier(sortie, grille); // Écrit l'état de la grille dans le fichier
        grille.mettreAJour();                 // Met à jour la grille pour l'itération suivante
        sortie.close();
    }

    std::cout << "Simulation terminée. Résultats sauvegardés dans des fichiers : " << dossier << "_iteration_<numéro>.txt" << std::endl;
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

//Ecrire les différents états dans les fichiers
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
}

