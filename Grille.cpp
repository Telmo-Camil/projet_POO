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
                cerr << "Erreur : Différence détectée à la cellule (" << x << ", " << y << ").\n";
                cerr << "Cellule actuelle : "
                     << (celluleActuelle.estVivante() ? "vivante" : "morte") << ", "
                     << (celluleActuelle.estObstacle() ? "obstacle" : "normale") << "\n";
                cerr << "Cellule attendue : "
                     << (celluleAttendue.estVivante() ? "vivante" : "morte") << ", "
                     << (celluleAttendue.estObstacle() ? "obstacle" : "normale") << "\n";
                return false;
            }
        }
    }

    cout << "Grilles identiques après comparaison.\n";
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

//Getter Largeur
int Grille::obtenirLargeur() const {
    return largeur;
}

//Getter Hauteur
int Grille::obtenirHauteur() const {
    return hauteur;
}

const Cellule &Grille::obtenirCellule(int x, int y) const {
    return cellules[x][y];
}

Cellule &Grille::obtenirCellule(int x, int y) {
    return cellules[x][y];
}
