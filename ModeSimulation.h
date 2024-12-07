#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include <iostream>
#include <string>
#include <fstream>
#include "Grille.h"
#include <filesystem> // Pour gestion des dossiers

class ModeSimulation {
private:
    bool modeGraphique; 
    int maxIterations;  

    static ModeSimulation *instance; // instance Singleton
    ModeSimulation(bool graphique, int iterations);

    std::string creerDossierSortie(const std::string &nomFichierEntree);
    void lancer(Grille &grille, const string &nomFichierEntree);
    void lancerConsole(Grille &grille, const std::string &nomDossierBase);
    void lancerGraphique(Grille &grille, const std::string &nomFichierEntree);
    void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &nomFichierEntree);
};

#endif
