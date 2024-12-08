#include "Grille.h"
#include <iostream>
#include <fstream>

using namespace std;

Grille::Grille(int l, int h) : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}

// Compte les voisins vivants d'une cellule, en tenant compte des règles d'une grille torique
int Grille::compterVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même

            int nx = (x + dx + largeur) % largeur; // Gestion torique des colonnes
            int ny = (y + dy + hauteur) % hauteur; // Gestion torique des lignes

            if (cellules[nx][ny].estVivante()) {
                ++voisinsVivants;
            }
        }
    }
    return voisinsVivants;
}

// Charge une grille depuis un fichier texte
bool Grille::chargerDepuisFichier(const string &chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << chemin << endl;
        return false;
    }

    fichier >> hauteur >> largeur;
    cellules = vector<vector<Cellule>>(largeur, vector<Cellule>(hauteur));

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            char etat;
            fichier >> etat;
            if (etat == '1') cellules[x][y] = Cellule(true);
            else if (etat == '0') cellules[x][y] = Cellule(false);
            else if (etat == 'O') cellules[x][y] = Cellule(true, OBSTACLE);
            else if (etat == 'X') cellules[x][y] = Cellule(false, OBSTACLE);
        }
    }
    return true;
}

// Met à jour la grille en appliquant les règles du jeu
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
}

// Sauvegarde la grille dans un fichier
void Grille::sauvegarderDansFichier(ofstream &sortie) const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                sortie << (cellules[x][y].estVivante() ? "O " : "X ");
            } else {
                sortie << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        sortie << '\n';
    }
}

// Affiche la grille dans la console
void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                cout << (cellules[x][y].estVivante() ? "O " : "X ");
            } else {
                cout << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        cout << '\n';
    }
}

// Renvoie la largeur de la grille
int Grille::getLargeur() const {
    return largeur;
}

// Renvoie la hauteur de la grille
int Grille::getHauteur() const {
    return hauteur;
}

// Retourne une cellule en lecture seule
const Cellule &Grille::obtenirCellule(int x, int y) const {
    return cellules[x][y];
}

// Retourne une cellule modifiable
Cellule &Grille::obtenirCellule(int x, int y) {
    return cellules[x][y];
}
