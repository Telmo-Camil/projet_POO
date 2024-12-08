#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include "Grille.h"
#include <string>

class ModeSimulation {
private:
    bool modeGraphique;               // Indique si on est en mode graphique
    int maxIterations;                // Nombre maximal d'itérations
    static ModeSimulation *instance;  // Instance unique (singleton)

    ModeSimulation(bool graphique, int iterations);  // Constructeur privé (singleton)
    void lancerConsole(Grille &grille, const std::string &fichierInitial);  // Mode console
    void lancerGraphique(Grille &grille);                                   // Mode graphique

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);    // Singleton
    void lancer(Grille &grille, const std::string &fichierInitial);        // Lance la simulation
};

#endif
