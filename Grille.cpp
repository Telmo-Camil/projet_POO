#include "Grille.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

Grille::Grille(int l, int h) 
    : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}

// Compte les voisins vivants d'une cellule
int Grille::compterVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même
            int nx = (x + dx + largeur) % largeur; // Gestion torique
            int ny = (y + dy + hauteur) % hauteur;
            if (cellules[nx][ny].estVivante() && !cellules[nx][ny].estObstacle())
                ++voisinsVivants;
        }
    }
    return voisinsVivants;
}

// Charge la grille depuis le fichier texte
void Grille::chargerDepuisFichier(const string &chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible de lire le fichier.");
    }

    fichier >> hauteur >> largeur;
    cellules = vector<vector<Cellule>>(largeur, vector<Cellule>(hauteur));

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int etat;
            fichier >> etat;
            if (etat == 2) {
                cellules[x][y] = Cellule(false, OBSTACLE);  // Obstacle mort
            } else if (etat == 3) {
                cellules[x][y] = Cellule(true, OBSTACLE);   // Obstacle vivant
            } else {
                cellules[x][y] = Cellule(etat == 1);       // 1 = vivant, 0 = mort
            }
        }
    }
}

// Met à jour les états de toutes les cellules
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
    cout << "Mise à jour de la grille effectuée." << endl;
}


void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                cout << (cellules[x][y].estVivante() ? "X " : "O ");
            } else {
                cout << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        cout << '\n';
    }
}

    Cellule &Grille::obtenirCellule(int x, int y) {
        return cellules[x][y];
    }

    const Cellule &Grille::obtenirCellule(int x, int y) const {
        return cellules[x][y];
    }