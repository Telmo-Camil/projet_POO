#include "Grille.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Grille::Grille(int l, int h) 
    : largeur(l), hauteur(h), cellules(l, std::vector<Cellule>(h)) {}

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
    if (!fichier.is_open()) throw std::runtime_error("Impossible de lire le fichier.");

    fichier >> hauteur >> largeur;
    cellules = std::vector<std::vector<Cellule>>(largeur, std::vector<Cellule>(hauteur));

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int etat;
            fichier >> etat;
            if (etat == 2) {  // 2 représente une cellule obstacle
                cellules[x][y] = Cellule(false, OBSTACLE);
            } else {
                cellules[x][y] = Cellule(etat == 1);
            }
        }
    }
}

void Grille::mettreAJour() {
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (!cellules[x][y].estObstacle()) {
                int voisins = compterVoisinsVivants(x, y);
                if (cellules[x][y].estVivante())
                    cellules[x][y].definirProchainEtat(voisins == 2 || voisins == 3);
                else
                    cellules[x][y].definirProchainEtat(voisins == 3);
            }
        }
    }
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y].appliquerProchainEtat();
        }
    }
}

void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                std::cout << "X ";
            } else {
                std::cout << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        std::cout << '\n';
    }
}
