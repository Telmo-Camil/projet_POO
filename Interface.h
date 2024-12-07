#ifndef INTERFACE_H
#define INTERFACE_H

#pragma once

#include <SFML/Graphics.hpp>
#include "Grille.h"

void renderGrid(sf::RenderWindow &window, const Grille &grille, int cellSize);


#endif 
