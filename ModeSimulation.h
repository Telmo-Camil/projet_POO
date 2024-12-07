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

    static ModeSimulation *instance; // instance Singleton
    ModeSimulation(bool graphique, int iterations);

    bool dossierExiste(const std::string &nomDossier) const; // Vérifie l'existence d'un dossier
    void creerDossier(const std::string &nomDossier) const;  // Crée un dossier

    void lancerConsole(Grille &grille, const std::string &dossierSortie);
    void lancerGraphique(Grille &grille, const std::string &dossierSortie);
    void ecrireEtatDansFichier(std::ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const std::string &nomFichierEntree);
};

#endif
