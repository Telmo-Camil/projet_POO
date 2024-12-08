#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace sf;


ModeSimulation *ModeSimulation::instance = nullptr;

// Initialise le mode (graphique ou console) et le nombre d'itérations
ModeSimulation::ModeSimulation(bool graphique, int iterations)
    : modeGraphique(graphique), maxIterations(iterations) {}

// Renvoie l'instance unique de ModeSimulation, la crée si elle n'existe pas encore
ModeSimulation *ModeSimulation::getInstance(bool graphique, int iterations) {
    if (instance == nullptr) {
        instance = new ModeSimulation(graphique, iterations);
    }
    return instance;
}

/* Lancer la simulation (graphique ou console)
Crée un dossier de sortie pour sauvegarder les résultats*/ 
void ModeSimulation::lancer(Grille &grille, const std::string &fichierInitial) {
    // Définit le dossier de sortie basé sur le nom du fichier d'entrée
    string dossierSortie = fichierInitial + "_out";

    // Crée le dossier 
    system(("mkdir -p " + dossierSortie).c_str());

    // Lance le mode approprié
    if (modeGraphique) {
        lancerGraphique(grille); 
    } else {
        lancerConsole(grille, dossierSortie); 
    }
}

// Mode console : simule la grille et sauvegarde chaque itération dans un dossier unique incrémenté
void ModeSimulation::lancerConsole(Grille &grille, const string &baseNomDossier) {
    string dossierSortie;
    int numDossier = 1;

    // Cherche un nouveau dossier incrémenté qui n'existe pas encore
    while (true) {
        dossierSortie = baseNomDossier + "_" + to_string(numDossier);

        // Teste si le dossier existe en essayant de créer un fichier temporaire
        string testFichier = dossierSortie + "/test.txt";
        ofstream testStream(testFichier);
        if (!testStream.is_open()) {
            // Le dossier n'existe pas encore
            break;
        }

        // Ferme et supprime le fichier temporaire avant de continuer
        testStream.close();
        remove(testFichier.c_str());
        numDossier++;
    }

    // Crée le nouveau dossier
    system(("mkdir -p " + dossierSortie).c_str());

    cout << "Les résultats seront enregistrés dans le dossier : " << dossierSortie << endl;

    // Boucle sur chaque itération de la simulation
    for (int i = 0; i < maxIterations; ++i) {
        // Définit le fichier de sortie pour cette itération
        string fichierSortie = dossierSortie + "/iteration_" + to_string(i + 1) + ".txt";

        ofstream sortie(fichierSortie);
        if (!sortie.is_open()) {
            cerr << "Erreur : Impossible de créer le fichier " << fichierSortie << endl;
            return;
        }

        // Sauvegarde l'état actuel de la grille dans le fichier
        grille.sauvegarderDansFichier(sortie);
        sortie.close();

        // Met à jour la grille pour l'itération suivante
        grille.mettreAJour();
    }

    cout << "Simulation terminée. Résultats sauvegardés dans : " << dossierSortie << endl;
}

// Mode graphique : affiche la grille et met à jour chaque itération dans une fenêtre
void ModeSimulation::lancerGraphique(Grille &grille) {
    const int tailleCellule = 10; // Taille d'une cellule en pixels

    // Crée une fenêtre graphique avec une taille basée sur les dimensions de la grille
    sf::RenderWindow fenetre(sf::VideoMode(grille.getLargeur() * tailleCellule,
                                           grille.getHauteur() * tailleCellule),
                             "Jeu de la Vie",
                             sf::Style::Default);

    fenetre.setFramerateLimit(60); // Limite les FPS pour éviter les coupures d'images

    int delaiEntreIterations = 100; // Délai entre les itérations en millisecondes

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        sf::Event evenement;

        // Gestion des événements utilisateur
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed)
                fenetre.close(); // Ferme la fenêtre si demandé

            if (evenement.type == sf::Event::KeyPressed) {
                if (evenement.key.code == sf::Keyboard::Up) {
                    delaiEntreIterations = std::max(10, delaiEntreIterations - 10); // Augmente la vitesse
                } else if (evenement.key.code == sf::Keyboard::Down) {
                    delaiEntreIterations += 10; // Réduit la vitesse
                }
            }
        }

        fenetre.clear(); 
        renderGrid(fenetre, grille, tailleCellule); 
        fenetre.display(); 
        grille.mettreAJour(); 
        sleep(milliseconds(delaiEntreIterations)); 
    }

    cout << "Simulation graphique terminée après " << maxIterations << " itérations." << endl;
}