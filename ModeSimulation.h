#pragma once

#include "Grille.h"
#include <string>
#include <fstream>

class ModeSimulation {
private:
    static ModeSimulation *instance;
    bool modeGraphique; // true : mode graphique, false : mode console
    int maxIterations;

    ModeSimulation(bool graphique, int iterations);

    void lancerConsole(Grille &grille, const std::string &outputPath);
    void lancerGraphique(Grille &grille);
    void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &outputPath = "");
};
