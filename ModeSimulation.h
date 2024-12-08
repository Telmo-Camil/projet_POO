#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include "Grille.h"
#include <string>

class ModeSimulation {
private:
    bool modeGraphique;
    int maxIterations;
    static ModeSimulation *instance;

    ModeSimulation(bool graphique, int iterations);

    void lancerConsole(Grille &grille, const std::string &fichierInitial);
    void lancerGraphique(Grille &grille);

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &fichierInitial);
};

#endif
