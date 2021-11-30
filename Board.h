#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <SFML/Graphics.hpp>

class Board
{
private:
	float m_tileWidth{ 150.0f };
	std::array<std::array<sf::RectangleShape, 4>, 4> m_boardTiles;

public:
	Board();
	void update(sf::Time dt, sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
};

#endif // !BOARD_H

