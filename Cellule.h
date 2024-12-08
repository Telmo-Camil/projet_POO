#ifndef CELLULE_H
#define CELLULE_H

// Type énuméré pour définir le type de cellule
enum TypeCellule { NORMALE, OBSTACLE };

class Cellule {
private:
    bool vivant;         // État actuel de la cellule (vivante ou morte)
    bool prochainEtat;   // État futur de la cellule
    TypeCellule type;    // Type de la cellule (NORMALE ou OBSTACLE)

public:
    Cellule(bool etatInitial = false, TypeCellule type = NORMALE); // Constructeur
    bool estVivante() const;             // Vérifie si la cellule est vivante
    bool estObstacle() const;            // Vérifie si la cellule est un obstacle
    bool obstacleVivante() const;        // Vérifie si l'obstacle est vivant
    void definirProchainEtat(bool etat); // Définit le prochain état
    void appliquerProchainEtat();        // Applique le prochain état
    void definirType(TypeCellule nouveauType); // Définit le type de la cellule
};

#endif
