#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"  

void initializeGrid(int gridWidth, int gridHeight);
void renderGrid(sf::RenderWindow &window, const Grille &grille);

#endif // INTERFACE_H
