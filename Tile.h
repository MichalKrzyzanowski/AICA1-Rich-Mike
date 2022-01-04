#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "PieceCheck.h"

class Tile
{
private:
	sf::RectangleShape m_rect;
	PieceCheck m_owner{ PieceCheck::NONE };

public:
	Tile(float width, int row, int col);
	PieceCheck& owner() { return m_owner; }

	sf::RectangleShape& rect() { return m_rect; }
};

#endif // !TILE_H

