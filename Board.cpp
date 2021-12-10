#include "Board.h"

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

void Board::update(sf::Time dt, sf::RenderWindow* window)
{
	
}

bool Board::placement(sf::RenderWindow* window, Piece* piece)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (m_boardTiles.at(i).at(j)->rect().getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
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
