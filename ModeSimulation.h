#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include <string>
#include "Grille.h"

class ModeSimulation {
private:
    bool modeGraphique;
    int maxIterations;

    static ModeSimulation *instance;
    ModeSimulation(bool graphique, int iterations);

    void lancerConsole(Grille &grille, const std::string &dossier);
    void lancerGraphique(Grille &grille);
    void ecrireEtatDansFichier(ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &dossier);
};

#endif 
