#include "Tile.h"

Tile::Tile(float width, int row, int col)
{
	m_rect.setSize(sf::Vector2f{ width, width });
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineThickness(0.5f);
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setPosition((width * row), (width * col));
}
