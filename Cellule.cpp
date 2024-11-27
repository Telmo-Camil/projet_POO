#include "Cellule.h"

// Constructeur : Initialise l'état vivant et le prochain état de la cellule.
Cellule::Cellule(bool etatInitial) : vivant(etatInitial), prochainEtat(false) {}

// Retourne l'état actuel (vivant ou mort) de la cellule.
bool Cellule::estVivante() const {
    return vivant;
}

// Définit le prochain état de la cellule.
void Cellule::definirProchainEtat(bool etat) {
    prochainEtat = etat;
}

// Applique le prochain état à la cellule (mise à jour).
void Cellule::appliquerProchainEtat() {
    vivant = prochainEtat;
}
