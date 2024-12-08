#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <vector>
#include <string>
#include <fstream>

class Grille {
private:
    int largeur, hauteur;                              // Dimensions de la grille
    std::vector<std::vector<Cellule>> cellules;        // Matrice de cellules

    int compterVoisinsVivants(int x, int y) const;     // Compte les voisins vivants d'une cellule

public:
    Grille(int l, int h);                               // Constructeur
    bool verifierGrilleApresIteration(const Grille &autre) const; // Compare deux grilles
    void sauvegarderDansFichier(std::ofstream &fichier) const;    // Sauvegarde la grille
    bool chargerDepuisFichier(const std::string &chemin);         // Charge la grille
    void mettreAJour();                                // Met à jour la grille
    void afficherConsole() const;                     // Affiche la grille dans la console
};

#endif
