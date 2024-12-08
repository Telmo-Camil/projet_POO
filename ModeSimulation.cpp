#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

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

void ModeSimulation::lancer(Grille &grille, bool effectuerTest, int iterationTest) {
    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, effectuerTest, iterationTest);
    }
}

void ModeSimulation::lancerConsole(Grille &grille, bool effectuerTest, int iterationTest) {
    cout << "Mode console activé.\n";

    // Créer un dossier pour sauvegarder les itérations
    string dossierSortie = "resultats_simulation";
    system(("mkdir -p " + dossierSortie).c_str());
    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    // Exécution des itérations
    for (int i = 0; i < maxIterations; ++i) {
        // Sauvegarde de l'état actuel dans un fichier
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }
        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Effectuer le test unitaire à l'itération demandée
        if (effectuerTest && i + 1 == iterationTest) {
            Grille grilleTest = grille; // Cloner la grille actuelle
            grilleTest.mettreAJour();  // Calculer la prochaine itération

            // Comparer la grille actuelle avec l'état attendu
            if (grille.verifierGrilleApresIteration(grilleTest)) {
                cout << "Test unitaire réussi pour l'itération " << iterationTest << ".\n";
            } else {
                cerr << "Test unitaire échoué pour l'itération " << iterationTest << ".\n";
            }
        }

        // Mettre à jour la grille pour la prochaine itération
        grille.mettreAJour();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

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

        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}
