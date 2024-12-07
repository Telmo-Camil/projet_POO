#include "Grille.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    // Nom du fichier d'entrée
    string fichierEntree = "etat_initial.txt"; 
    //Instance d'une grille
    Grille grille(0, 0);

    if (!grille.chargerDepuisFichier(fichierEntree)) {
        cerr << "Erreur lors du chargement du fichier de grille." << endl;
        return 1;
    }

    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console\n";
    cout << "2. Mode graphique\n";
    cin >> choixMode;

    int maxIterations;
    cout << "Entrez le nombre maximum d'itérations : ";
    cin >> maxIterations;

    if (choixMode == 1) {
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, fichierEntree + "_out");
    } else if (choixMode == 2) {
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille, fichierEntree);
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}

