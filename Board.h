#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Board
{
private:
	float m_tileWidth{ 150.0f };
	std::array<std::array<sf::RectangleShape, 4>, 4> m_boardTiles;
	int m_index;

public:
	Board(int index);
	void update(sf::Time dt, sf::RenderWindow* window);
	void placement(sf::RenderWindow* window, Piece* piece);
	void render(sf::RenderWindow* window);

	int index() { return m_index; }
};

#endif // !BOARD_H

