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

    int maxIterations = 0, iterationTest = 0;
    bool effectuerTest = false;

    if (choixMode == 1) {
        cout << "Entrez le nombre maximum d'itérations : ";
        cin >> maxIterations;

        cout << "Voulez-vous effectuer un test unitaire ? (1 pour Oui, 0 pour Non) : ";
        cin >> effectuerTest;

        if (effectuerTest) {
            cout << "Entrez l'itération sur laquelle vous souhaitez effectuer le test unitaire (entre 1 et " << maxIterations << ") : ";
            cin >> iterationTest;

            if (iterationTest < 1 || iterationTest > maxIterations) {
                cerr << "Erreur : Numéro d'itération invalide. Aucun test unitaire ne sera effectué." << endl;
                effectuerTest = false;
            }
        }
    } else if (choixMode == 2) {
        cout << "Mode graphique activé. Vous pouvez ajuster la vitesse avec les flèches haut et bas.\n";
        cout << "Entrez le nombre maximum d'itérations : ";
        cin >> maxIterations;
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    ModeSimulation::getInstance(choixMode == 2, maxIterations)->lancer(grille, effectuerTest, iterationTest);
    return 0;
}
