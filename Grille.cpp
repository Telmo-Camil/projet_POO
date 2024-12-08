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

    cout << "Comparaison des grilles :\n";
    cout << "Grille calculée :" << endl;
    afficherConsole();
    cout << "Grille attendue :" << endl;
    attendue.afficherConsole();

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            const Cellule &celluleActuelle = obtenirCellule(x, y);
            const Cellule &celluleAttendue = attendue.obtenirCellule(x, y);

            // Comparer états vivants et types (obstacle ou normal)
            if (celluleActuelle.estVivante() != celluleAttendue.estVivante() ||
                celluleActuelle.estObstacle() != celluleAttendue.estObstacle()) {
                cerr << "Erreur : Différence détectée à la cellule (" << x << ", " << y << ")." << endl;
                return false;
            }
        }
    }

    cout << "Grilles identiques après comparaison.\n";
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
            if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même
            
            // Gestion torique
            int nx = (x + dx + largeur) % largeur; 
            int ny = (y + dy + hauteur) % hauteur;

            const Cellule &voisin = cellules[nx][ny];
            
            // Les obstacles vivants sont comptés comme vivants
            if (voisin.estVivante()) {
                ++voisinsVivants;
            }
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

            // Ignorer les obstacles pour le changement d'état
            if (cellules[x][y].estObstacle()) {
                continue;
            }

            if (cellules[x][y].estVivante()) {
                cellules[x][y].definirProchainEtat(voisins == 2 || voisins == 3);
            } else {
                cellules[x][y].definirProchainEtat(voisins == 3);
            }
        }
    }

    // Appliquer les états
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
                cout << (cellules[x][y].estVivante() ? "O " : "X "); // Obstacle vivant ou mort
            } else {
                cout << (cellules[x][y].estVivante() ? "1 " : "0 "); // Cellule normale
            }
        }
        cout << '\n';
    }
}


