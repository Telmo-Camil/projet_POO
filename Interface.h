#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

// Fonction pour afficher la grille dans une fenêtre graphique
void renderGrid(sf::RenderWindow &window, const Grille &grille, int tailleCellule);

#endif
