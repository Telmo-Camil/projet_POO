#ifndef CELLULE_H
#define CELLULE_H

enum TypeCellule { NORMALE, OBSTACLE }; // Deux types possibles pour une cellule

class Cellule {
private:
    bool vivant;           // Indique si la cellule est vivante
    bool prochainEtat;     // Stocke l'état futur de la cellule
    TypeCellule type;      // Définit si la cellule est NORMALE ou OBSTACLE

public:
    Cellule(bool etatInitial = false, TypeCellule type = NORMALE); // Constructeur
    bool estVivante() const;             // Vérifie si la cellule est vivante
    bool estObstacle() const;            // Vérifie si la cellule est un obstacle
    bool obstacleVivante() const;        // Vérifie si l'obstacle est vivant
    void definirProchainEtat(bool etat); // Définit le prochain état
    void appliquerProchainEtat();        // Applique le prochain état
};

#endif
