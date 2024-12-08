#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

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

void ModeSimulation::lancer(Grille &grille, const std::string &fichierInitial) {
    string dossierSortie = fichierInitial + "_out";
    system(("mkdir -p " + dossierSortie).c_str());

    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}

void ModeSimulation::lancerConsole(Grille &grille, const string &baseNomDossier) {
    // Trouver un nouveau dossier incrémenté
    string dossierSortie;
    int numDossier = 1;

    while (true) {
        dossierSortie = baseNomDossier + "_" + to_string(numDossier);

        // Essayer d'ouvrir un fichier test dans le dossier
        string testFichier = dossierSortie + "/test.txt";
        ofstream testStream(testFichier);
        if (!testStream.is_open()) {
            // Le dossier n'existe pas encore
            break;
        }

        // Fermer et supprimer le fichier temporaire
        testStream.close();
        remove(testFichier.c_str());
        numDossier++;
    }

    // Créer le nouveau dossier
    system(("mkdir -p " + dossierSortie).c_str());

    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    // Sauvegarde des fichiers par itération
    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        // Sauvegarder l'état actuel de la grille
        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Mise à jour de la grille pour l'itération suivante
        grille.mettreAJour();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

void ModeSimulation::lancerGraphique(Grille &grille) {
    const int tailleCellule = 10;

    // Création d'une fenêtre
    sf::RenderWindow fenetre(sf::VideoMode(grille.getLargeur() * tailleCellule,
                                           grille.getHauteur() * tailleCellule),
                             "Jeu de la Vie",
                             sf::Style::Default);

    fenetre.setFramerateLimit(60); // Limiter les FPS à 60 pour éviter les coupures visuelles

    int delaiEntreIterations = 100;

    // Simulation graphique
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed)
                fenetre.close();

            if (evenement.type == sf::Event::KeyPressed) {
                if (evenement.key.code == sf::Keyboard::Up) {
                    delaiEntreIterations = std::max(10, delaiEntreIterations - 10);
                } else if (evenement.key.code == sf::Keyboard::Down) {
                    delaiEntreIterations += 10;
                }
            }
        }

        fenetre.clear();
        renderGrid(fenetre, grille, tailleCellule);
        fenetre.display();
        grille.mettreAJour();
        sf::sleep(sf::milliseconds(delaiEntreIterations));
    }

    std::cout << "Simulation graphique terminée après " << maxIterations << " itérations." << std::endl;
}

