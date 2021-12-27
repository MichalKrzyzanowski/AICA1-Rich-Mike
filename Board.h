#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Piece.h"
#include "PieceCheck.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Board
{
private:
	float m_tileWidth{ 150.0f };
	std::array<std::array<Tile*, 4>, 4> m_boardTiles;
	int m_index;

public:
	Board(int index);
	void update(sf::Time dt, sf::RenderWindow* window);
	bool placement(sf::RenderWindow* window, Piece* piece);
	void render(sf::RenderWindow* window);
	void resetOwner();

	int index() { return m_index; }
	PieceCheck owner(int row, int col) { return m_boardTiles.at(row).at(col)->owner(); }
};

#endif // !BOARD_H

