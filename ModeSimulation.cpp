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

// Lancement d'un des deux modes
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    if (modeGraphique) {
        lancerGraphique(grille, nomFichierEntree); 
    } else {
        lancerConsole(grille, nomFichierEntree);  
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const string &nomFichierEntree) {
    cout << "Les fichiers seront enregistrés dans le dossier : " << nomFichierEntree << "_out" << endl;

    // Écriture des fichiers par itération
    for (int i = 0; i < maxIterations; ++i) {
        string fichierSortie = nomFichierEntree + "_out_iteration_" + to_string(i + 1) + ".txt";

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

    cout << "Simulation terminée. Résultats sauvegardés dans des fichiers : " << nomFichierEntree << "_out_iteration_<numéro>.txt" << endl;
}

// Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille, const string &nomFichierEntree) {
    const int tailleCellule = 10; // Taille des cellules en pixels
    string nomDossierSortie = nomFichierEntree + "_out";

    // Exécute une commande shell ou système externe pour créer le répertoire
    system(("mkdir -p " + nomDossierSortie).c_str());

    RenderWindow fenetre(VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == Event::Closed)
                fenetre.close();
        }

        string cheminFichier = nomDossierSortie + "/iteration_" + to_string(iteration + 1) + ".txt";
        ofstream fichierSortie(cheminFichier);
        if (fichierSortie.is_open()) {
            ecrireEtatDansFichier(fichierSortie, grille);
            fichierSortie.close();
        } else {
            cerr << "Erreur : Impossible de créer le fichier " << cheminFichier << endl;
        }

        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(100));
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
