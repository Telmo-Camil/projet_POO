#include "Cellule.h"

// Constructeur : initialise une cellule avec un état initial et un type
Cellule::Cellule(bool etatInitial, TypeCellule type)
    : vivant(etatInitial), prochainEtat(false), type(type) {}

// Vérifie si la cellule est vivante
bool Cellule::estVivante() const {
    return vivant;
}

// Vérifie si la cellule est un obstacle
bool Cellule::estObstacle() const {
    return type == OBSTACLE;
}

// Vérifie si l'obstacle est vivant
bool Cellule::obstacleVivante() const {
    return estObstacle() && vivant;
}

// Définit le prochain état de la cellule si elle n'est pas un obstacle
void Cellule::definirProchainEtat(bool etat) {
    if (!estObstacle()) {
        prochainEtat = etat;
    }
}

// Applique le prochain état si la cellule n'est pas un obstacle
void Cellule::appliquerProchainEtat() {
    if (!estObstacle()) {
        vivant = prochainEtat;
    }
}
