#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include <iostream>
#include <string>
#include <fstream>
#include "Grille.h"

class ModeSimulation {
private:
    bool modeGraphique;
    int maxIterations;

    static ModeSimulation *instance; // Singleton instance
    ModeSimulation(bool graphique, int iterations);

    bool dossierExiste(const std::string &nomDossier) const; // Vérifie l'existence du dossier
    void creerDossier(const std::string &nomDossier) const;  // Crée un dossier si nécessaire

    void lancerConsole(Grille &grille, const std::string &nomDossierBase);
    void lancerGraphique(Grille &grille, const std::string &nomFichierEntree);
    void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &nomFichierEntree);
};

#endif
