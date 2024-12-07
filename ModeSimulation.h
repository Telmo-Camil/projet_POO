#ifndef MODESIMULATION_H
#define MODESIMULATION_H

#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h> // Pour vérifier l'existence de dossiers
#include "Grille.h"

using namespace std;

class ModeSimulation {
private:
    bool modeGraphique; 
    int maxIterations;  

    static ModeSimulation *instance; // Instance Singleton
    ModeSimulation(bool graphique, int iterations);

    bool dossierExiste(const string &nomDossier) const; 
    std::string creerDossierSortie(const string &nomFichierEntree);
    void lancerConsole(Grille &grille, const string &nomDossierBase);
    void lancerGraphique(Grille &grille, const string &nomDossierBase);
    void ecrireEtatDansFichier(ofstream &sortie, const Grille &grille) const;

public:
    static ModeSimulation *getInstance(bool graphique, int iterations);
    void lancer(Grille &grille, const string &nomFichierEntree);
};

#endif
