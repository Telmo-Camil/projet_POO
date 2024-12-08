#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour system()

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

// Lancer le mode approprié (Console ou Graphique)
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie = nomFichierEntree + "_out";
    system(("mkdir -p " + dossierSortie).c_str());

    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &dossierSortie) {
    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    int iterationTest = 0;
    cout << "Voulez-vous effectuer un test unitaire ? (1 pour Oui, 0 pour Non) : ";
    int effectuerTest;
    cin >> effectuerTest;

    if (effectuerTest) {
        cout << "Entrez l'itération sur laquelle vous souhaitez effectuer le test unitaire (entre 1 et " << maxIterations << ") : ";
        cin >> iterationTest;

        if (iterationTest < 1 || iterationTest > maxIterations) {
            cerr << "Erreur : Numéro d'itération invalide. Aucun test unitaire ne sera effectué." << endl;
            iterationTest = 0;
        }
    }

    Grille grilleAttendue(grille.obtenirLargeur(), grille.obtenirHauteur());

    for (int i = 0; i < maxIterations; ++i) {
        // Sauvegarde de l'itération actuelle
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }
        ecrireEtatDansFichier(sortie, grille);
        sortie.close();

        // Si un test unitaire est demandé et que c'est l'itération cible
        if (effectuerTest && i + 1 == iterationTest) {
            cout << "Effectuer le test unitaire pour l'itération " << iterationTest << "...\n";

            // Calculer l'état attendu
            Grille grilleTemp(grille);
            for (int t = 0; t < iterationTest; ++t) {
                grilleTemp.mettreAJour();
            }

            if (grille.verifierGrilleApresIteration(grilleTemp)) {
                cout << "Test unitaire réussi : la grille calculée correspond à l'attendue.\n";
            } else {
                cerr << "Test unitaire échoué : divergence détectée.\n";
            }
        }

        // Met à jour la grille pour la prochaine itération
        grille.mettreAJour();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
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

        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}

// Écrit les états de la grille dans un fichier
void ModeSimulation::ecrireEtatDansFichier(ofstream &sortie, const Grille &grille) const {
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
