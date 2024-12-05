#include "Cellule.h"

Cellule::Cellule(bool etatInitial, TypeCellule type) {
    vivant = etatInitial;
    prochainEtat = false;.
    this->type = type;
}

bool Cellule::estVivante() const {
    return vivant;
}

//Méthode mettant en place les cellules obstacles 
bool Cellule::estObstacle() const {
    return type == OBSTACLE;
}

//Méthode mettant en place les cellules obstacles vivantes
bool Cellule::obstacleVivante() const {
    return estObstacle() && vivant;
}

void Cellule::definirProchainEtat(bool etat) {
    if (!estObstacle()) {
        prochainEtat = etat;
    }
}

void Cellule::appliquerProchainEtat() {
    if (!estObstacle()) {
        vivant = prochainEtat;
    }
}

void Cellule::definirType(TypeCellule nouveauType) {
    type = nouveauType;
}
