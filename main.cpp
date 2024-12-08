#include "Grille.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    string fichierEntree = "etat_initial.txt";

    Grille grille(0, 0);
    if (!grille.chargerDepuisFichier(fichierEntree)) {
        cerr << "Erreur : Impossible de charger le fichier de grille initiale." << endl;
        return 1;
    }

    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console\n";
    cout << "2. Mode graphique\n";
    cin >> choixMode;

    int maxIterations = 0;
    if (choixMode == 1 || choixMode == 2) {
        cout << "Entrez le nombre maximum d'itérations : ";
        cin >> maxIterations;
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    // Lancer la simulation
    ModeSimulation::getInstance(choixMode == 2, maxIterations)->lancer(grille, fichierEntree);

    return 0;
}
