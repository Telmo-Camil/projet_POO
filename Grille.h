#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Grille {
private:
    int largeur, hauteur;                              // Dimensions de la grille
    std::vector<std::vector<Cellule>> cellules;        // Matrice bidimensionnelle de cellules

    int compterVoisinsVivants(int x, int y) const;     // Compte les voisins vivants d'une cellule

public:
    Grille(int l, int h);                               
    bool chargerDepuisFichier(const std::string &chemin); // Charge une grille depuis un fichier
    void sauvegarderDansFichier(std::ofstream &fichier) const; // Sauvegarde une grille dans un fichier
    void mettreAJour();                                // Met à jour les cellules selon les règles
    void afficherConsole() const;                     // Affiche la grille dans la console
    int getLargeur() const;                            // Renvoie la largeur de la grille
    int getHauteur() const;                            // Renvoie la hauteur de la grille
    const Cellule &obtenirCellule(int x, int y) const; // Retourne une cellule en lecture seule
    Cellule &obtenirCellule(int x, int y);             // Retourne une cellule modifiable
};

#endif
