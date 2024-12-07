#ifndef CELLULE_H
#define CELLULE_H

#pragma once

//Type énuméré : avoir les deux états de la cellule
enum TypeCellule { NORMALE, OBSTACLE };

class Cellule {
private:
    bool vivant;
    bool prochainEtat;
    TypeCellule type;

public:
    Cellule(bool etatInitial = false, TypeCellule type = NORMALE);

    bool estVivante() const;
    bool estObstacle() const;
    bool obstacleVivante() const;
    void definirProchainEtat(bool etat);
    void appliquerProchainEtat();
    void definirType(TypeCellule nouveauType);
};

#endif
