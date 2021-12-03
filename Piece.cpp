#include "Piece.h"

void Piece::render(sf::RenderWindow* t_window, int t_currentBoardIndex)
{
	for (auto& position : m_positions)
	{
		if (position.boardIndex == t_currentBoardIndex)
		{
			m_piece.setPosition((m_piece.getRadius() * 2) * position.row, (m_piece.getRadius() * 2) * position.col);
			t_window->draw(m_piece);
		}
	}
}
