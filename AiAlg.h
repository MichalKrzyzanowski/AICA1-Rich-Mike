#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"

class Game;

struct Move
{
	Move() : score{0} {};
	Move(int t_score) : score{ t_score } {};

	int score;
	int x, y, z;
};

class AiAlg
{
public:
	AiAlg() {};
	Move executeMove(sf::RenderWindow* t_window, std::array<Board*, 4> t_boards, Piece* t_piece, GameState& t_currentState);

private:
	Move getBestMove(GameState& t_currentState, std::array<Board*, 4> t_boards, int t_depth, Move t_move);
	int const MAX_DEPTH = 2;
	std::vector<Move> moves;
};

#include "Game.h"