#include "Grille.h"
#include "Constants.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    Grille grille(gridWidth, gridHeight);

    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } catch (const exception &e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }

    // Initialisation des obstacles
    grille.obtenirCellule(1, 1).definirType(OBSTACLE); // Obstacle mort
    grille.obtenirCellule(1, 1).definirProchainEtat(false);
    grille.obtenirCellule(1, 1).appliquerProchainEtat();

    grille.obtenirCellule(3, 3).definirType(OBSTACLE); // Obstacle vivant
    grille.obtenirCellule(3, 3).definirProchainEtat(true);
    grille.obtenirCellule(3, 3).appliquerProchainEtat();

    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console\n";
    cout << "2. Mode graphique\n";
    cin >> choixMode;

    int maxIterations;
    cout << "Entrez le nombre maximum d'itérations : ";
    cin >> maxIterations;

    if (choixMode == 1) {
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, "simulation_out.txt");
    } else if (choixMode == 2) {
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille);
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}
