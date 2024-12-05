#pragma once

#include "Grille.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class ModeSimulation {
private:
    bool modeGraphique; // true : mode graphique, false : mode console
    int maxIterations;
    static ModeSimulation *instance;

    ModeSimulation(bool graphique, int iterations);

    void lancerConsole(Grille &grille, const string &FichierSortie);
    void lancerGraphique(Grille &grille);

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);

    void lancer(Grille &grille, const string &FichierSortie = "");
};

