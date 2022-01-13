#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"

class Game;

/// <summary>
/// a struct that holds all of the information of a move such as it's position and score
/// </summary>
struct Move
{
	Move() : score{ 0 } {};
	Move(int t_score) : score{ t_score } {};

	int score;
	int x, y, z;
};

/// <summary>
/// controls the AI and performs it's moves
/// </summary>
class AiAlg
{
public:
	AiAlg() {};
	Move executeMove(std::array<Board*, 4> t_boards, Piece* t_piece, GameState& t_currentState, int t_difficulty);

private:
	Move getBestMove(GameState t_currentState, std::array<Board*, 4> t_boards, Piece * t_piece, int t_depth, Move t_move);
	int evaluate(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards);
	int evaluateHorizontal(Move* currentMove, std::array<Board*, 4> boards);
	int evaluateVertical(Move* currentMove, std::array<Board*, 4> boards);
	int evaluateDiagonal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards);
	int evaluate3DHorizontal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards);
	int evaluate3DVertical(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards);
	int evaluate3DDiagonal(GameState t_currentState, Move* currentMove, std::array<Board*, 4> boards);
	int evaluate3DStack(Move* currentMove, std::array<Board*, 4> boards);
	int calculateEvalScore(int playerCount, int aiCount, int emptyCount);
	int compareScores(GameState t_currentState, int tempScore, int finalScore);
	int MAX_DEPTH = 1;
	std::vector<Move> moves;
};

#include "Game.h"