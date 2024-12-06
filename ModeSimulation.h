#ifndef MODE_SIMULATION_H
#define MODE_SIMULATION_H

#include "Grille.h"
#include <string>

class ModeSimulation {
private:
    bool modeGraphique;   // true pour le mode graphique, false pour le mode console
    int maxIterations;

    ModeSimulation(bool graphique, int iterations);

    static ModeSimulation *instance;

    void lancerConsole(Grille &grille, const std::string &outputPath);
    void lancerGraphique(Grille &grille);

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);

    void lancer(Grille &grille, const std::string &outputPath = "");
};

#endif // MODE_SIMULATION_H
