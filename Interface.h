#pragma once

#include <SFML/Graphics.hpp>  // Pour RenderWindow et les graphiques SFML
#include "Grille.h"           // Inclut la définition de la classe Grille

// Déclaration de la fonction renderGrid
void renderGrid(sf::RenderWindow &window, const Grille &grille);

#endif // INTERFACE_H
