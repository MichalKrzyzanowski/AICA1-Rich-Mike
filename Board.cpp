#include "Board.h"

/// <summary>
/// init the board
/// </summary>
/// <param name="index">board index in the array of boards</param>
Board::Board(int index)
{
	m_index = index;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_boardTiles.at(i).at(j) = new Tile(m_tileWidth, i, j);
		}
	}
}


/// <summary>
/// function that places a given piece on the board
/// </summary>
/// <param name="window">current SFML window</param>
/// <param name="piece">piece to place</param>
/// <returns></returns>
bool Board::placement(sf::RenderWindow* window, Piece* piece)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			// place a piece on a tile where the mouse cursor was hovering over
			if (m_boardTiles.at(i).at(j)->rect().getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_boardTiles.at(i).at(j)->owner() == PieceCheck::NONE)
				{
					m_boardTiles.at(i).at(j)->owner() = piece->type();
					piece->addPosition(PieceData{ i, j, m_index });
					return true;
				}
			}
		}
	}

	return false;
}

/// <summary>
/// render the board
/// </summary>
/// <param name="window">current SFML window</param>
void Board::render(sf::RenderWindow* window)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			window->draw(m_boardTiles.at(i).at(j)->rect());
		}
	}
}

/// <summary>
/// reset all tile owners
/// </summary>
void Board::resetOwner()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_boardTiles.at(i).at(j)->owner() = PieceCheck::NONE;
		}
	}
}


