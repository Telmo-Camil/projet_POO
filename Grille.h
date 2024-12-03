#pragma once
#include "Cellule.h"
#include <vector>
#include <string>

class Grille {
private:
    int largeur, hauteur;
    std::vector<std::vector<Cellule>> cellules;

    int compterVoisinsVivants(int x, int y) const;

public:
    Grille(int l, int h);

    void chargerDepuisFichier(const std::string &chemin);
    void mettreAJour();
    void afficherConsole() const;
    int obtenirLargeur() const { return largeur; }
    int obtenirHauteur() const { return hauteur; }
    const Cellule& obtenirCellule(int x, int y) const { return cellules[x][y]; }
};
