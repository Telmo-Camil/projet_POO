#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>    // Pour system()

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

// Crée un dossier avec un numéro incrémenté
void ModeSimulation::creerDossierIncremente(const string &baseNom, string &nouveauNom) const {
    int numero = 1;
    while (true) {
        nouveauNom = baseNom + "_out_" + to_string(numero);
        if (system(("mkdir -p " + nouveauNom).c_str()) == 0) {
            break;
        }
        ++numero;
    }
}

// Lancer le mode approprié
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie;
    creerDossierIncremente(nomFichierEntree, dossierSortie);

    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &dossierSortie) {
    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";

        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        sortie << "Itération " << i + 1 << " :\n";
        ecrireEtatDansFichier(sortie, grille);
        grille.mettreAJour();
        sortie.close();
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
