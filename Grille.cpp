#include "Grille.h"
#include <iostream>
#include <fstream>
//Permet de signaler et traiter des erreurs à l'exécution.
#include <stdexcept>

using namespace std;

Grille::Grille(int l, int h ) : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}


//Regarder l'entourage d'une cellule
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

//Prendre le fichier texte de départ
void Grille::chargerDepuisFichier(const string &chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible de lire le fichier.");
    }

    fichier >> hauteur >> largeur;  // Lire les dimensions de la grille
    cellules = vector<vector<Cellule>>(largeur, vector<Cellule>(hauteur));  // Redimensionner la grille

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            char etat;
            fichier >> etat;  // Lecture de chaque cellule

            if (etat == '1') {
                cellules[x][y] = Cellule(true);  // Cellule vivante normale
            } else if (etat == '0') {
                cellules[x][y] = Cellule(false);  // Cellule morte normale
            } else if (etat == 'O') {
                cellules[x][y] = Cellule(true, OBSTACLE);  // Obstacle vivant
            } else if (etat == 'X') {
                cellules[x][y] = Cellule(false, OBSTACLE);  // Obstacle mort
            } else {
                //throw : Pour communiquer une erreur 
                throw runtime_error("Fichier incorrect : état de cellule inconnu.");
            }
        }
    }
}


//Rendre une cellule vivante ou morte en fonction de son entourage
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
    afficherConsole();
}

void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                cout << (cellules[x][y].estVivante() ? "O " : "X "); // Obstacle vivant : O, mort : X
            } else {
                cout << (cellules[x][y].estVivante() ? "1 " : "0 "); // Cellule normale
            }
        }
        cout << '\n';
    }
}


int Grille::obtenirLargeur() const {
    return largeur;
}

int Grille::obtenirHauteur() const {
    return hauteur;
}

/*
Fonction obtenirCellule avec 2 versions :
- La version const est utilisée pour garantir un accès sécurisé et immuable.
- La version non-const est utilisée pour permettre des modifications.
*/

const Cellule &Grille::obtenirCellule(int x, int y) const {
    return cellules[x][y];
}


Cellule &Grille::obtenirCellule(int x, int y) {
    return cellules[x][y];
}
