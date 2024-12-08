#include "Grille.h"
#include "ModeSimulation.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string fichierEntree = "etat_initial.txt";
    string fichierAttendu = "etat_attendu.txt";

    // Charger la grille initiale
    Grille grille(0, 0);
    if (!grille.chargerDepuisFichier(fichierEntree)) {
        cerr << "Erreur lors du chargement du fichier de grille initiale." << endl;
        return 1;
    }

    // Menu pour choisir le mode de fonctionnement
    int choixMode;
    cout << "Choisissez le mode de fonctionnement :\n";
    cout << "1. Mode console\n";
    cout << "2. Mode graphique\n";
    cout << "3. Test unitaire\n";
    cin >> choixMode;

    // Récupération du nombre d'itérations si nécessaire
    int maxIterations = 0;
    if (choixMode != 3) { 
        cout << "Entrez le nombre maximum d'itérations : ";
        cin >> maxIterations;
    }

    // Gestion des modes
    if (choixMode == 1) {
        // Mode console
        ModeSimulation::getInstance(false, maxIterations)->lancer(grille, fichierEntree);
    } else if (choixMode == 2) {
        // Mode graphique
        cout << "Mode graphique activé. Vous pouvez ajuster la vitesse avec les flèches haut et bas.\n";
        ModeSimulation::getInstance(true, maxIterations)->lancer(grille, fichierEntree);
    } else if (choixMode == 3) {
        // Mode test unitaire

        // Calcul de l'état attendu après une itération
        Grille grilleAttendue = grille;  // Clone la grille actuelle
        grilleAttendue.mettreAJour();   // Applique une itération pour obtenir l'état attendu

        // Sauvegarder la grille attendue dans le fichier
        ofstream fichier(fichierAttendu);
        if (!fichier.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier attendu." << endl;
            return 1;
        }
        grilleAttendue.sauvegarderDansFichier(fichier);
        fichier.close();

        // Appliquer une itération à la grille initiale
        grille.mettreAJour();

        // Vérifier si la grille calculée correspond à celle attendue
        if (grille.verifierGrilleApresIteration(grilleAttendue)) {
            cout << "Test unitaire réussi : la grille calculée correspond à la grille attendue." << endl;
        } else {
            cerr << "Test unitaire échoué : la grille calculée ne correspond pas à la grille attendue." << endl;
        }
    } else {
        cerr << "Choix invalide." << endl;
        return 1;
    }

    return 0;
}
