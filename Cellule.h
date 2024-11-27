#pragma once

class Cellule {
private:
    bool vivant;
    bool prochainEtat;

public:
    Cellule(bool etatInitial = false) : vivant(etatInitial), prochainEtat(false) {}

    bool estVivante() const { return vivant; }
    void definirProchainEtat(bool etat) { prochainEtat = etat; }
    void appliquerProchainEtat() { vivant = prochainEtat; }
};