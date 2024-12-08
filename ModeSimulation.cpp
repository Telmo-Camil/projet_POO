#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

ModeSimulation *ModeSimulation::instance = nullptr;

// Constructeur privé
ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

// Méthode pour obtenir l'instance unique
ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

// Méthode principale lancer
void ModeSimulation::lancer(Grille &grille, const string &fichierInitial) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, fichierInitial);
    }
}

// Mode Console avec Test Unitaire Simplifié
void ModeSimulation::lancerConsole(Grille &grille, const string &fichierInitial) {
    string dossierSortie = fichierInitial + "_out";
    system(("mkdir -p " + dossierSortie).c_str());
    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    Grille grilleAttendue = grille;

    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        // Sauvegarde de la grille actuelle
        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Préparer la grille attendue pour le test unitaire (si dernière itération)
        if (i == maxIterations - 1) {
            string fichierTest = dossierSortie + "/iteration_test_" + to_string(maxIterations) + ".txt";
            ofstream fichierAttendu(fichierTest);
            if (fichierAttendu.is_open()) {
                grilleAttendue.mettreAJour(); // Calculer une itération en avance
                grilleAttendue.sauvegarderDansFichier(fichierAttendu);
                fichierAttendu.close();

                // Comparer les deux grilles
                if (grille.verifierGrilleApresIteration(grilleAttendue)) {
                    cout << "Test unitaire réussi pour l'itération " << maxIterations << ".\n";
                } else {
                    cerr << "Test unitaire échoué pour l'itération " << maxIterations << ".\n";
                }
            } else {
                cerr << "Erreur : Impossible de créer le fichier d'état attendu pour le test unitaire.\n";
            }
        }

        grille.mettreAJour(); // Calcul de l'itération suivante
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

// Mode Graphique (inchangé)
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
