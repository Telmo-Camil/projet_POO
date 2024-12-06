#include "Grille.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    //Création d'une instance
    Grille grille(0, 0); 

    //Essayer d'ouvrir le fichier texte
    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } catch (const exception &e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }

    //L'utilisateur choisit entre les deux modes
    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console\n";
    cout << "2. Mode graphique\n";
    cin >> choixMode;

    int maxIterations;
    cout << "Entrez le nombre maximum d'itérations : ";
    cin >> maxIterations;

    //Lancer le mode en fonction de son choix
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
