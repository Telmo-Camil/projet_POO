#pragma once

class Cellule {
private:
    bool vivant;
    bool prochainEtat;

public:
    Cellule(bool etatInitial = false);

    bool estVivante() const;
    void definirProchainEtat(bool etat);
    void appliquerProchainEtat();
};
