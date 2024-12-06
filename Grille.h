#ifndef GRILLE_H
#define GRILLE_H

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

    bool chargerDepuisFichier(const std::string &chemin);
    void mettreAJour();
    void afficherConsole() const;

    int obtenirLargeur() const;
    int obtenirHauteur() const;
    const Cellule &obtenirCellule(int x, int y) const;
    Cellule &obtenirCellule(int x, int y);
};

#endif
