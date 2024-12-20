#include "Grille.h"
#include "ModeSimulation.h"

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

    cout << "Entrez le nombre maximum d'itérations : ";
    cin >> maxIterations;

    ModeSimulation::getInstance(choixMode == 2, maxIterations)->lancer(grille, fichierEntree);

    return 0;
}
