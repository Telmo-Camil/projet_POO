#include "Cellule.h"

// Initialisation de la cellule
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

// Définit le prochain état de la cellule (les obstacles ne changent pas)
void Cellule::definirProchainEtat(bool etat) {
    if (!estObstacle()) {
        prochainEtat = etat;
    }
}

// Applique le prochain état à la cellule
void Cellule::appliquerProchainEtat() {
    if (!estObstacle()) {
        vivant = prochainEtat;
    }
}
