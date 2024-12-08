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
    string dossierSortie = "etat_initial.txt_out"; // Nom du dossier de sortie
    system(("mkdir -p " + dossierSortie).c_str());

    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    Grille grilleAttendue(grille.obtenirLargeur(), grille.obtenirHauteur());
    if (effectuerTest) {
        // Créer la grille attendue pour l'itération demandée
        grilleAttendue = grille;
        for (int i = 0; i < iterationTest; ++i) {
            grilleAttendue.mettreAJour();
        }

        // Sauvegarde de la grille attendue dans le fichier correspondant
        string fichierAttendu = dossierSortie + "/iteration_test_" + to_string(iterationTest) + ".txt";
        ofstream fichierSortieAttendu(fichierAttendu);
        if (fichierSortieAttendu.is_open()) {
            grilleAttendue.sauvegarderDansFichier(fichierSortieAttendu);
            fichierSortieAttendu.close();
        } else {
            cerr << "Erreur : Impossible de créer le fichier de test attendu : " << fichierAttendu << endl;
        }
    }

    // Sauvegarde des résultats de chaque itération
    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        sortie << "Itération " << i + 1 << " :\n";
        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Comparer si c'est l'itération demandée pour le test
        if (effectuerTest && (i + 1 == iterationTest)) {
            if (grille.verifierGrilleApresIteration(grilleAttendue)) {
                cout << "Test unitaire réussi pour l'itération " << iterationTest << ".\n";
            } else {
                cerr << "Test unitaire échoué pour l'itération " << iterationTest << ".\n";
            }
        }

        grille.mettreAJour();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

void ModeSimulation::lancerGraphique(Grille &grille) {
    const int tailleCellule = 10;
    RenderWindow fenetre(VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    fenetre.setVerticalSyncEnabled(false); // Désactiver VSync pour éviter les avertissements

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
