#pragma once
#include <SFML/Graphics.hpp>

struct PieceData
{
	unsigned row;
	unsigned col;
	int boardIndex;
};

class Piece
{
private:
	sf::CircleShape m_piece;
	std::vector<PieceData> m_positions;

public:
	Piece(sf::Color t_color, float t_radius) { m_piece.setFillColor(t_color); m_piece.setRadius(t_radius); }
	void addPosition(PieceData t_data) { m_positions.push_back(t_data); };
	void render(sf::RenderWindow* t_window, int t_currentBoardIndex);
	void resetPositions() { m_positions.clear(); }
};

