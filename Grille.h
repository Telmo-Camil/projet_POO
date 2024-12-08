#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <vector>
#include <string>
#include <fstream>

class Grille {
private:
    int largeur, hauteur;                              // Dimensions de la grille
    std::vector<std::vector<Cellule>> cellules;        // Grille de cellules

    int compterVoisinsVivants(int x, int y) const;     // Compte les voisins vivants d'une cellule

public:
    Grille(int l, int h);                              
    bool verifierGrilleApresIteration(const Grille &autre) const; // Compare avec une autre grille
    void sauvegarderDansFichier(std::ofstream &fichier) const;    // Sauvegarde la grille dans un fichier
    bool chargerDepuisFichier(const std::string &chemin);         // Charge une grille depuis un fichier
    void mettreAJour();                                // Met à jour la grille selon les règles
    void afficherConsole() const;                     // Affiche la grille dans la console
    int obtenirLargeur() const;                       // Renvoie la largeur
    int obtenirHauteur() const;                       // Renvoie la hauteur
    const Cellule &obtenirCellule(int x, int y) const; // Renvoie une cellule en lecture seule
    Cellule &obtenirCellule(int x, int y);            // Renvoie une cellule modifiable
};

#endif
