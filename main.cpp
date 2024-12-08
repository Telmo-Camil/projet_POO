#include "Grille.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    string fichierEntree = "etat_initial.txt";

    // Charger la grille initiale
    Grille grille(0, 0);
    if (!grille.chargerDepuisFichier(fichierEntree)) {
        cerr << "Erreur lors du chargement du fichier de grille initiale." << endl;
        return 1;
    }

    // Demander à l'utilisateur de choisir le mode
    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console avec tests unitaires\n";
    cout << "2. Mode graphique\n";
    cin >> choixMode;

    // Récupération du nombre d'itérations
    int maxIterations = 0;
    if (choixMode == 1 || choixMode == 2) {
        cout << "Entrez le nombre maximum d'itérations : ";
        cin >> maxIterations;
    }

    // Gestion des modes
    if (choixMode == 1) {
        cout << "Mode console avec tests unitaires activé.\n";
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, fichierEntree);
    } else if (choixMode == 2) {
        cout << "Mode graphique activé. Vous pouvez ajuster la vitesse avec les flèches haut et bas.\n";
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille, fichierEntree);
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}
