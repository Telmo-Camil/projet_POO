#include "Grille.h"
#include <iostream>
#include <fstream>

using namespace std;

// Initialisation de la grille
Grille::Grille(int l, int h) : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}

// Compte les voisins vivants (inclut les obstacles vivants)
int Grille::compterVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = (x + dx + largeur) % largeur; // Gestion torique
            int ny = (y + dy + hauteur) % hauteur;

            if (cellules[nx][ny].estVivante()) {
                ++voisinsVivants;
            }
        }
    }

    return voisinsVivants;
}

// Compare deux grilles (vérifie état et type de chaque cellule)
bool Grille::verifierGrilleApresIteration(const Grille &autre) const {
    if (largeur != autre.largeur || hauteur != autre.hauteur) {
        cerr << "Erreur : Dimensions des grilles différentes.\n";
        return false;
    }

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estVivante() != autre.cellules[x][y].estVivante() ||
                cellules[x][y].estObstacle() != autre.cellules[x][y].estObstacle()) {
                cerr << "Différence détectée à la cellule (" << x << ", " << y << ").\n";
                return false;
            }
        }
    }

    return true;
}

// Sauvegarde la grille dans un fichier
void Grille::sauvegarderDansFichier(ofstream &fichier) const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[x][y].estObstacle()) {
                fichier << (cellules[x][y].estVivante() ? "O " : "X ");
            } else {
                fichier << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
        }
        fichier << '\n';
    }
}

// Charge la grille depuis un fichier
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
            if (etat == '1') {
                cellules[x][y] = Cellule(true);  // Cellule vivante
            } else if (etat == '0') {
                cellules[x][y] = Cellule(false); // Cellule morte
            } else if (etat == 'O') {
                cellules[x][y] = Cellule(true, OBSTACLE); // Obstacle vivant
            } else if (etat == 'X') {
                cellules[x][y] = Cellule(false, OBSTACLE); // Obstacle mort
            }
        }
    }

    return true;
}

// Met à jour la grille (en suivant les règles)
void Grille::mettreAJour() {
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            if (cellules[x][y].estObstacle()) continue; // Ignorer les obstacles

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

// Affiche la grille dans la console
void Grille::afficherConsole() const {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            cout << (cellules[x][y].estObstacle()
                         ? (cellules[x][y].estVivante() ? "O " : "X ")
                         : (cellules[x][y].estVivante() ? "1 " : "0 "));
        }
        cout << '\n';
    }
}
