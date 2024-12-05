#include "Cellule.h"

Cellule::Cellule(bool etatInitial) {
    vivant = etatInitial;

    prochainEtat = false;
}

bool Cellule::estVivante() const {
    return vivant;
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
