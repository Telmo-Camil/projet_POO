#include "ModeSimulation.h"
#include "Interface.h"
#include <SFML/Graphics.hpp>
#include <sys/stat.h> // Pour vérifier l'existence de dossiers
#include <cstdlib>    // Pour system()

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

// Vérifie si un dossier existe
bool ModeSimulation::dossierExiste(const string &nomDossier) const {
    struct stat info;
    return (stat(nomDossier.c_str(), &info) == 0 && (info.st_mode & S_IFDIR));
}

// Crée un dossier s'il n'existe pas
void ModeSimulation::creerDossier(const string &nomDossier) const {
    if (!dossierExiste(nomDossier)) {
        system(("mkdir -p " + nomDossier).c_str());
    }
}

// Lancer un des deux modes
void ModeSimulation::lancer(Grille &grille, const string &nomFichierEntree) {
    string dossierSortie = nomFichierEntree + "_out";
    creerDossier(dossierSortie); // Assure l'existence du dossier
    if (modeGraphique) {
        lancerGraphique(grille, dossierSortie);
    } else {
        lancerConsole(grille, dossierSortie);
    }
}
