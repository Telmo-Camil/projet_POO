#include "Grille.h"
#include <iostream>
#include <fstream> //utiliser les classes et fonctions pour gérer les fichiers

using namespace std;

Grille::Grille(int l, int h) : largeur(l), hauteur(h), cellules(l, vector<Cellule>(h)) {}

bool Grille::verifierGrilleApresIteration(const Grille &attendue) const {
    if (largeur != attendue.obtenirLargeur() || hauteur != attendue.obtenirHauteur()) {
        cerr << "Erreur : Dimensions des grilles différentes." << endl;
        return false;
    }

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            const Cellule &celluleActuelle = obtenirCellule(x, y);
            const Cellule &celluleAttendue = attendue.obtenirCellule(x, y);

            if (celluleActuelle.estVivante() != celluleAttendue.estVivante() ||
                celluleActuelle.estObstacle() != celluleAttendue.estObstacle()) {
                cerr << "Erreur : Différence détectée à la cellule (" << x << ", " << y << ")." << endl;
                return false;
            }
        }
    }

    cout << "Test unitaire réussi : la grille calculée correspond à la grille attendue." << endl;
    return true;
}

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

// Regarder l'entourage d'une cellule
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

// Prendre le fichier texte de départ
bool Grille::chargerDepuisFichier(const string &chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << chemin << endl;
        return false;
    }

    fichier >> hauteur >> largeur;
    if (hauteur <= 0 || largeur <= 0) {
        cerr << "Erreur : Dimensions de la grille incorrectes." << endl;
        return false;
    }

    cellules = vector<vector<Cellule>>(largeur, vector<Cellule>(hauteur));

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            char etat;
            fichier >> etat;
            if (etat == '1') {
                cellules[x][y] = Cellule(true);  // Cellule vivante normale
            } else if (etat == '0') {
                cellules[x][y] = Cellule(false);  // Cellule morte normale
            } else if (etat == 'O') {
                cellules[x][y] = Cellule(true, OBSTACLE);  // Obstacle vivant
            } else if (etat == 'X') {
                cellules[x][y] = Cellule(false, OBSTACLE);  // Obstacle mort
            } else {
                cerr << "Erreur : État de cellule inconnu '" << etat << "' au fichier." << endl;
                return false;
            }
        }
    }

    return true;
}

// Rendre une cellule vivante ou morte en fonction de son entourage
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
