#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour system()

using namespace sf;
using namespace std;
namespace fs = std::filesystem;

ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

// Dossier de sortie
string ModeSimulation::creerDossierSortie(const string &nomFichierEntree) {
    string nomDossier = nomFichierEntree + "_out";
    if (!fs::exists(nomDossier)) {
        fs::create_directory(nomDossier);
    }
    return nomDossier;
}

// Lancement du mode approprié
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie = creerDossierSortie(nomFichierEntree);
    if (modeGraphique) {
        lancerGraphique(grille, dossierSortie);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &dossierSortie) {
    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    // Sauvegarde de chaque itération
    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";

        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        sortie << "Itération " << i + 1 << " :\n";
        ecrireEtatDansFichier(sortie, grille); // Écrit l'état de la grille dans le fichier
        grille.mettreAJour();                 // Met à jour la grille pour l'itération suivante
        sortie.close();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

// Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille, const string &dossierSortie) {
    const int tailleCellule = 10; // Taille des cellules en pixels
    RenderWindow fenetre(VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    int delaiEntreIterations = 100; // Temps initial en millisecondes

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        Event evenement; // Déclare un événement pour capturer les interactions utilisateur
        while (fenetre.pollEvent(evenement)) {
            // Vérifie si l'utilisateur ferme la fenêtre
            if (evenement.type == Event::Closed)
                fenetre.close();
        
            if (evenement.type == Event::KeyPressed) {
                // Si la flèche haut est pressée, réduire le délai entre les itérations pour augmenter la vitesse
                if (evenement.key.code == Keyboard::Up) {
                    delaiEntreIterations = max(10, delaiEntreIterations - 10);
                } 
                // Si la flèche bas est pressée, augmenter le délai entre les itérations pour réduire la vitesse
                else if (evenement.key.code == Keyboard::Down) {
                    delaiEntreIterations += 10;
                }
            }
        }
    }
        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}

// Écrire les différents états dans les fichiers
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
