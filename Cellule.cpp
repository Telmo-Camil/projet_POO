#include "Cellule.h"

Cellule::Cellule(bool etatInitial) {
    vivant = etatInitial;
    prochainEtat = false;
    type = type;
}


bool Cellule::estVivante() const {
    return vivant;
}

bool Cellule::estObstacle() const {
    return type == OBSTACLE;
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
