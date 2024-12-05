#include "Grille.h"
#include "Constants.h"
#include "ModeSimulation.h"
#include <iostream>

using namespace std;

int main() {
    Grille grille(gridWidth, gridHeight);

    //le programme tente de charger une grille à partir du fichier "etat_initial.txt"
    try {
        grille.chargerDepuisFichier("etat_initial.txt");
    } 
    //Si une exception est levée dans le bloc try, elle est interceptée par le bloc catch
    catch (const exception &e) {
        //La méthode e.what() retourne un message décrivant l'exception, qui est ensuite affiché.
        cerr << "Erreur : " << e.what() << endl;
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
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, "simulation_out.txt");
    } else if (choixMode == 2) {
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille);
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}
