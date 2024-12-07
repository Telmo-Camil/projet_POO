#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <sys/stat.h> // Pour mkdir
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

// Vérifie si un dossier existe
bool ModeSimulation::dossierExiste(const string &nomDossier) const {
    struct stat info;
    return (stat(nomDossier.c_str(), &info) == 0 && (info.st_mode & S_IFDIR));
}

// Crée un dossier s'il n'existe pas
void ModeSimulation::creerDossier(const string &nomDossier) const {
    if (!dossierExiste(nomDossier)) {
        system(("mkdir -p " + nomDossier).c_str());
    }
}

// Lancer un des deux modes
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie = nomFichierEntree + "_out";
    creerDossier(dossierSortie);
    if (modeGraphique) {
        lancerGraphique(grille, dossierSortie); // Appel à lancerGraphique
    } else {
        lancerConsole(grille, dossierSortie);  // Appel à lancerConsole
    }
}

// Mode Console : Sauvegarde chaque itération dans un fichier
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

// Mode Graphique : Affiche la grille à chaque itération
void ModeSimulation::lancerGraphique(Grille &grille, const string &dossierSortie) {
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

        string fichierSortie = dossierSortie + "/iteration_" + to_string(iteration + 1) + ".txt";
        ofstream sortie(fichierSortie);
        if (sortie.is_open()) {
            ecrireEtatDansFichier(sortie, grille);
            sortie.close();
        } else {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
        }

        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}

// Écrire les états dans des fichiers
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
