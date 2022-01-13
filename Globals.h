#ifndef PIECE_CHECK_H
#define PIECE_CHECK_H

enum class PieceCheck
{
	PLAYER,
	AI,
	NONE
};

enum GameState
{
	PLAYER_TURN,
	AI_TURN,
	PLAYER_WIN,
	AI_WIN,
	NONE,
};

#endif // !PIECE_CHECK_H

