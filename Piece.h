#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "Globals.h"

/// <summary>
/// data of a placeable piece
/// </summary>
struct PieceData
{
	unsigned row;
	unsigned col;
	int boardIndex;
};

class Board;

/// <summary>
/// class that allows the user/ai to place a piece on any board
/// </summary>
class Piece
{
private:
	sf::CircleShape m_piece;
	std::vector<PieceData> m_positions;
	PieceData* m_currentPosition{ nullptr };
	PieceCheck m_type;

private:
	bool checkHorizontal(std::array<Board*, 4> boards);
	bool checkVertical(std::array<Board*, 4> boards);
	bool checkDiagonal(std::array<Board*, 4> boards);
	bool check3DHorizontal(std::array<Board*, 4> boards);
	bool check3DVertical(std::array<Board*, 4> boards);
	bool check3DDiagonal(std::array<Board*, 4> boards);
	bool check3DStack(std::array<Board*, 4> boards);

public:
	Piece(sf::Color t_color, float t_radius, PieceCheck type);
	void addPosition(PieceData t_data);
	void render(sf::RenderWindow* t_window, int t_currentBoardIndex);
	void resetPositions() { m_positions.clear(); }
	bool checkWin(std::array<Board*, 4> boards);

	PieceCheck type() { return m_type; }
};

#include "Board.h"

#endif // !PIECE_H
