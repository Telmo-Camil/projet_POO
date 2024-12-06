#include "Cellule.h"

Cellule::Cellule(bool etatInitial, TypeCellule type) {
    vivant = etatInitial;
    prochainEtat = false;
    this->type = type;
}

//Vérification de si la cellule est vivante
bool Cellule::estVivante() const {
    return vivant;
}

//Cellules obstacles 
bool Cellule::estObstacle() const {
    return type == OBSTACLE;
}

//Cellules obstacles vivantes
bool Cellule::obstacleVivante() const {
    return estObstacle() && vivant;
}

//Prochain état des cellules en fonction de si elles sont obstacles ou non
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
