#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

ModeSimulation *ModeSimulation::instance = nullptr;  // Initialisation de l'instance singleton

// Constructeur privé
ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

// Retourne l'instance unique de ModeSimulation
ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

// Lance la simulation en fonction du mode
void ModeSimulation::lancer(Grille &grille, const string &fichierInitial) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, fichierInitial);
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &fichierInitial) {
    string dossierSortie = fichierInitial + "_out";  // Créer un dossier pour les résultats
    system(("mkdir -p " + dossierSortie).c_str());

    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    Grille grilleAttendue = grille;  // Cloner la grille pour le test unitaire
    for (int i = 0; i < maxIterations; ++i) {
        // Sauvegarde de l'état actuel
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Comparer à la dernière itération (test unitaire)
        if (i == maxIterations - 1) {
            Grille grilleAttendue = grille;  // État attendu après toutes les mises à jour
            for (int j = 0; j < maxIterations; ++j) {
                grilleAttendue.mettreAJour();
            }

            if (grille.verifierGrilleApresIteration(grilleAttendue)) {
                cout << "Test unitaire réussi pour la dernière itération.\n";
            } else {
                cerr << "Test unitaire échoué pour la dernière itération.\n";
            }
        }

        grille.mettreAJour();  // Mise à jour de la grille
    }

    cout << "Simulation terminée.\n";
}

// Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille) {
    const int tailleCellule = 10;
    RenderWindow fenetre(VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    int delaiEntreIterations = 100;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == Event::Closed)
                fenetre.close();

            if (evenement.type == Event::KeyPressed) {
                if (evenement.key.code == Keyboard::Up) {
                    delaiEntreIterations = max(10, delaiEntreIterations - 10);
                } else if (evenement.key.code == Keyboard::Down) {
                    delaiEntreIterations += 10;
                }
            }
        }

        fenetre.clear();
        renderGrid(fenetre, grille, tailleCellule);
        fenetre.display();
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}
