#pragma once
#include "Cellule.h"
#include <vector>
#include <string>

using namespace std;

class Grille {
private:
    int largeur; 
    int hauteur;  
    vector<vector<Cellule>> cellules; 
    int compterVoisinsVivants(int x, int y) const;

public:

    Grille(int l, int h);
    void chargerDepuisFichier(const string &chemin);
    void mettreAJour();
    void afficherConsole() const;
    int obtenirLargeur() const;
    int obtenirHauteur() const;
    const Cellule &obtenirCellule(int x, int y) const;
    Cellule &obtenirCellule(int x, int y);
};
