#ifndef PIECE_CHECK_H
#define PIECE_CHECK_H

/// <summary>
/// signifies what is contained in each tile of the board: a player or ai piece, or nothing
/// </summary>
enum class PieceCheck
{
	PLAYER,
	AI,
	NONE
};

/// <summary>
/// signifies what the current state the game is in, such as the current turn, or who won
/// </summary>
enum GameState
{
	PLAYER_TURN,
	AI_TURN,
	PLAYER_WIN,
	AI_WIN,
	NONE,
};

#endif // !PIECE_CHECK_H

