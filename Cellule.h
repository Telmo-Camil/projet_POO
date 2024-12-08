#ifndef CELLULE_H
#define CELLULE_H

// Type énuméré pour définir les types de cellule
enum TypeCellule { NORMALE, OBSTACLE };

class Cellule {
private:
    bool vivant;         // État actuel : vivant ou mort
    bool prochainEtat;   // État futur calculé
    TypeCellule type;    // Type de cellule : normale ou obstacle

public:
    Cellule(bool etatInitial = false, TypeCellule type = NORMALE); // Constructeur
    bool estVivante() const;                                      // Vérifie si vivant
    bool estObstacle() const;                                     // Vérifie si obstacle
    void definirProchainEtat(bool etat);                          // Définit l'état futur
    void appliquerProchainEtat();                                 // Applique l'état futur
};

#endif
