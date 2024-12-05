#pragma once

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
    bool obstacleVivante() const;  // Nouvelle méthode pour vérifier si l'obstacle est vivant
    void definirProchainEtat(bool etat);
    void appliquerProchainEtat();
    void definirType(TypeCellule nouveauType);
};
