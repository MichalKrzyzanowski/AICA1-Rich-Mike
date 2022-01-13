#include "Piece.h"

/// <summary>
/// function that checks for the horizontal win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::checkHorizontal(std::array<Board*, 4> boards)
{
	if (boards[m_currentPosition->boardIndex]->owner(0, m_currentPosition->col) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(1, m_currentPosition->col) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(2, m_currentPosition->col) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(3, m_currentPosition->col) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the vertical win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::checkVertical(std::array<Board*, 4> boards)
{
	if (boards[m_currentPosition->boardIndex]->owner(m_currentPosition->row, 0) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(m_currentPosition->row, 1) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(m_currentPosition->row, 2) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(m_currentPosition->row, 3) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the diagonal win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::checkDiagonal(std::array<Board*, 4> boards)
{
	if (boards[m_currentPosition->boardIndex]->owner(0, 0) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(1, 1) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(2, 2) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(3, 3) == m_type)
	{
		return true;
	}

	if (boards[m_currentPosition->boardIndex]->owner(0, 3) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(1, 2) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(2, 1) == m_type &&
		boards[m_currentPosition->boardIndex]->owner(3, 0) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the 3D horizontal win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::check3DHorizontal(std::array<Board*, 4> boards)
{
	if (boards[0]->owner(0, m_currentPosition->col) == m_type &&
		boards[1]->owner(1, m_currentPosition->col) == m_type &&
		boards[2]->owner(2, m_currentPosition->col) == m_type &&
		boards[3]->owner(3, m_currentPosition->col) == m_type)
	{
		return true;
	}

	if (boards[0]->owner(3, m_currentPosition->col) == m_type &&
		boards[1]->owner(2, m_currentPosition->col) == m_type &&
		boards[2]->owner(1, m_currentPosition->col) == m_type &&
		boards[3]->owner(0, m_currentPosition->col) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the 3D vertical win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::check3DVertical(std::array<Board*, 4> boards)
{
	if (boards[0]->owner(m_currentPosition->row, 0) == m_type &&
		boards[1]->owner(m_currentPosition->row, 1) == m_type &&
		boards[2]->owner(m_currentPosition->row, 2) == m_type &&
		boards[3]->owner(m_currentPosition->row, 3) == m_type)
	{
		return true;
	}

	if (boards[0]->owner(m_currentPosition->row, 3) == m_type &&
		boards[1]->owner(m_currentPosition->row, 2) == m_type &&
		boards[2]->owner(m_currentPosition->row, 1) == m_type &&
		boards[3]->owner(m_currentPosition->row, 0) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the 3D diagonal win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::check3DDiagonal(std::array<Board*, 4> boards)
{
	if (boards[0]->owner(0, 0) == m_type &&
		boards[1]->owner(1, 1) == m_type &&
		boards[2]->owner(2, 2) == m_type &&
		boards[3]->owner(3, 3) == m_type)
	{
		return true;
	}

	if (boards[0]->owner(3, 3) == m_type &&
		boards[1]->owner(2, 2) == m_type &&
		boards[2]->owner(1, 1) == m_type &&
		boards[3]->owner(0, 0) == m_type)
	{
		return true;
	}

	if (boards[0]->owner(0, 3) == m_type &&
		boards[1]->owner(1, 2) == m_type &&
		boards[2]->owner(2, 1) == m_type &&
		boards[3]->owner(3, 0) == m_type)
	{
		return true;
	}

	if (boards[0]->owner(3, 0) == m_type &&
		boards[1]->owner(2, 1) == m_type &&
		boards[2]->owner(1, 2) == m_type &&
		boards[3]->owner(0, 3) == m_type)
	{
		return true;
	}

	return false;
}

/// <summary>
/// function that checks for the 3D stack win.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::check3DStack(std::array<Board*, 4> boards)
{
	if (boards[0]->owner(m_currentPosition->row, m_currentPosition->col) == m_type &&
		boards[1]->owner(m_currentPosition->row, m_currentPosition->col) == m_type &&
		boards[2]->owner(m_currentPosition->row, m_currentPosition->col) == m_type &&
		boards[3]->owner(m_currentPosition->row, m_currentPosition->col) == m_type)
	{
		return true;
	}

	return false;
}
/// <summary>
/// init a piece
/// </summary>
/// <param name="t_color">piece color</param>
/// <param name="t_radius">piece radiu</param>
/// <param name="type">piece type, either ai or player</param>
Piece::Piece(sf::Color t_color, float t_radius, PieceCheck type) :
	m_type{ type }
{
	m_piece.setFillColor(t_color); m_piece.setRadius(t_radius);
}

/// <summary>
/// add a position to the positions vector.
/// this vector draws the same piece in multiple places.
/// </summary>
/// <param name="t_data">piece data</param>
void Piece::addPosition(PieceData t_data)
{
	m_positions.push_back(t_data);
	m_currentPosition = &m_positions.back();
}

/// <summary>
/// draw the piece at all positions from the positions vector
/// </summary>
/// <param name="t_window">current SFML window</param>
/// <param name="t_currentBoardIndex">current board</param>
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

/// <summary>
/// main win condition function that runs the other win check functions.
/// </summary>
/// <param name="boards">vector of boards</param>
/// <returns>true if victory, false if no victory</returns>
bool Piece::checkWin(std::array<Board*, 4> boards)
{
	bool win{ false };

	if ((win = checkHorizontal(boards)))
	{
		return win;
	}
	if ((win = checkVertical(boards)))
	{
		return win;
	}
	if ((win = checkDiagonal(boards)))
	{
		return win;
	}

	if ((win = check3DHorizontal(boards)))
	{
		return win;
	}
	if ((win = check3DVertical(boards)))
	{
		return win;
	}
	if ((win = check3DDiagonal(boards)))
	{
		return win;
	}
	if ((win = check3DStack(boards)))
	{
		return win;
	}

	return win;
}
