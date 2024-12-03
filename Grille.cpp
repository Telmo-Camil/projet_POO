#include "Grille.h"
#include <iostream>
//Fournit des classes et des fonctions pour manipuler des fichiers en entrée/sortie (lecture/écriture).
#include <fstream>
//Contient des classes pour gérer les exceptions standard
#include <stdexcept>

using namespace std; 

Grille::Grille(int l, int h) 
    : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}

int Grille::compterVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + largeur) % largeur;
            int ny = (y + dy + hauteur) % hauteur;
            if (cellules[nx][ny].estVivante() && !cellules[nx][ny].estObstacle())
                ++voisinsVivants;
        }
    }
    return voisinsVivants;
}

void Grille::chargerDepuisFichier(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible de lire le fichier.");
    }

    // Lire les dimensions depuis le fichier
    fichier >> hauteur >> largeur;
    cellules = std::vector<std::vector<Cellule>>(largeur, std::vector<Cellule>(hauteur));

    // Lire l'état initial de chaque cellule
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int etat;
            fichier >> etat;
            cellules[x][y] = Cellule(etat == 1);  // 1 = vivant, 0 = mort
        }
    }
}




void Grille::mettreAJour() {
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            int voisins = compterVoisinsVivants(x, y);
            if (cellules[x][y].estVivante()) {
                cellules[x][y].definirProchainEtat(voisins == 2 || voisins == 3);
            } else {
                cellules[x][y].definirProchainEtat(voisins == 3);
            }
        }
    }

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y].appliquerProchainEtat();
        }
    }

    // Ajoutez ce log pour vérifier
    std::cout << "Mise à jour de la grille effectuée." << std::endl;
    afficherConsole(); // Facultatif : Affiche la grille dans la console
}


void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                cout << "X ";
            } else {
                cout << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        cout << '\n';
    }
}
