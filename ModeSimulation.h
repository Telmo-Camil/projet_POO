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

    void creerDossierIncremental(const std::string &baseNom, std::string &nouveauNom) const;
    void lancerConsole(Grille &grille, const std::string &dossierSortie);
    void lancerGraphique(Grille &grille);

    void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &nomFichierEntree);
};

#endif
