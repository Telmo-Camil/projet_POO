#include "Grille.h"
#include "ModeSimulation.h"
#include <filesystem>
#include <iostream>

using namespace std;

int main() {
    //Création d'une instance
    Grille grille(0, 0); 

    //Essayer d'ouvrir le fichier texte
    if (!grille.chargerDepuisFichier("etat_initial.txt")) {
        cerr << "Erreur lors du chargement du fichier de grille." << endl;
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

// Lancer le mode en fonction 
   if (choixMode == 1) {
        string baseOutputDir = "simulation_out"; 
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, baseOutputDir);
    } else if (choixMode == 2) {
        string dummyOutputDir = "unused"; // Nom de dossier factice pour le mode graphique
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille, dummyOutputDir);
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}
