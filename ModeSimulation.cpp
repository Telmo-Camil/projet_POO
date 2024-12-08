#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour system()

using namespace sf;
using namespace std;

ModeSimulation *ModeSimulation::instance = nullptr;

ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

// Crée un dossier avec un numéro incrémenté
void ModeSimulation::creerDossierIncremente(const string &nomDepart, string &nouveauNom) const {
    int numero = 1;
    while (true) {
        nouveauNom = nomDepart + "_out_" + to_string(numero);
        // Teste si le dossier existe déjà
        if (system(("test -d " + nouveauNom).c_str()) != 0) {
            // Si le dossier n'existe pas, le crée
            system(("mkdir -p " + nouveauNom).c_str());
            break;
        }
        ++numero;
    }
}

// Lancer le mode approprié
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie;
    creerDossierIncremente(nomFichierEntree, dossierSortie);

    if (modeGraphique) {
        lancerGraphique(grille);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}

// Mode Console
void ModeSimulation::lancerConsole(Grille &grille, const std::string &nomFichierEntree) {
    int iterationTest = 0;
    cout << "Voulez-vous effectuer un test unitaire ? (1 pour Oui, 0 pour Non) : ";
    int effectuerTest;
    cin >> effectuerTest;

    if (effectuerTest) {
        cout << "Entrez l'itération sur laquelle vous souhaitez effectuer le test unitaire (entre 1 et " << maxIterations << ") : ";
        cin >> iterationTest;

        if (iterationTest < 1 || iterationTest > maxIterations) {
            cerr << "Erreur : Numéro d'itération invalide. Aucune vérification effectuée." << endl;
            iterationTest = 0;
        }
    }

    Grille grilleAttendue(grille.obtenirLargeur(), grille.obtenirHauteur());
    if (effectuerTest) {
        string fichierAttendu = nomFichierEntree + "_etat_attendu.txt";
        if (!grilleAttendue.chargerDepuisFichier(fichierAttendu)) {
            cerr << "Erreur : Impossible de charger la grille attendue pour le test unitaire." << endl;
            iterationTest = 0;
        }
    }

    for (int i = 0; i < maxIterations; ++i) {
        if (effectuerTest && i + 1 == iterationTest) {
            cout << "Effectuer le test unitaire pour l'itération " << iterationTest << "...\n";
            if (grille.verifierGrilleApresIteration(grilleAttendue)) {
                cout << "Test unitaire réussi : la grille calculée correspond à la grille attendue pour l'itération " << iterationTest << ".\n";
            } else {
                cerr << "Test unitaire échoué : des divergences ont été détectées pour l'itération " << iterationTest << ".\n";
            }
        }

        grille.mettreAJour();
    }

    cout << "Simulation terminée." << endl;
}


// Mode Graphique
void ModeSimulation::lancerGraphique(Grille &grille) {
    const int tailleCellule = 10;
    RenderWindow fenetre(VideoMode(grille.obtenirLargeur() * tailleCellule, grille.obtenirHauteur() * tailleCellule), "Jeu de la Vie");

    int delaiEntreIterations = 100;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == Event::Closed)
                fenetre.close();

            if (evenement.type == Event::KeyPressed) {
                if (evenement.key.code == Keyboard::Up) {
                    delaiEntreIterations = max(10, delaiEntreIterations - 10);
                } else if (evenement.key.code == Keyboard::Down) {
                    delaiEntreIterations += 10;
                }
            }
        }

        renderGrid(fenetre, grille, tailleCellule);
        grille.mettreAJour();
        sleep(milliseconds(delaiEntreIterations));
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}

// Écrit les états de la grille dans un fichier
void ModeSimulation::ecrireEtatDansFichier(ofstream &sortie, const Grille &grille) const {
    for (int y = 0; y < grille.obtenirHauteur(); ++y) {
        for (int x = 0; x < grille.obtenirLargeur(); ++x) {
            if (grille.obtenirCellule(x, y).estObstacle()) {
                sortie << (grille.obtenirCellule(x, y).estVivante() ? "O " : "X ");
            } else {
                sortie << (grille.obtenirCellule(x, y).estVivante() ? "1 " : "0 ");
            }
        }
        sortie << '\n';
    }
}
