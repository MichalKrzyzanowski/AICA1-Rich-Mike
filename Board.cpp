#include "Board.h"

Board::Board(int index)
{
	m_index = index;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_boardTiles.at(i).at(j).setSize(sf::Vector2f{ m_tileWidth, m_tileWidth });
			m_boardTiles.at(i).at(j).setFillColor(sf::Color::White);
			m_boardTiles.at(i).at(j).setOutlineThickness(0.5f);
			m_boardTiles.at(i).at(j).setOutlineColor(sf::Color::Black);
			m_boardTiles.at(i).at(j).setPosition((m_tileWidth * i), (m_tileWidth * j));
		}
	}
}

void Board::update(sf::Time dt, sf::RenderWindow* window)
{
	
}

void Board::placement(sf::RenderWindow* window, Piece* piece)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (m_boardTiles.at(i).at(j).getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					piece->addPosition(PieceData{ i,j,m_index });
				}
			}
		}
	}
}

void Board::render(sf::RenderWindow* window)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			window->draw(m_boardTiles.at(i).at(j));
		}
	}
}
