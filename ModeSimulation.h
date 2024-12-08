#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include "Grille.h"
#include <string>

class ModeSimulation {
private:
    bool modeGraphique;         // Indique si le mode graphique est activé
    int maxIterations;          // Nombre d'itérations maximum
    static ModeSimulation *instance; // Instance Singleton
    ModeSimulation(bool graphique, int iterations);   // Constructeur privé

    void lancerConsole(Grille &grille, bool effectuerTest, int iterationTest); // Mode console
    void lancerGraphique(Grille &grille);             // Mode graphique

public:
    static ModeSimulation *getInstance(bool graphique, int iterations); // Singleton
    void lancer(Grille &grille, bool effectuerTest, int iterationTest); // Lance la simulation
};

#endif
