#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Board.h"
#include "PieceCheck.h"
#include "AI.h"

class Game
{
public:

	enum GameState
	{
		PLAYER_TURN,
		AI_TURN,
		PLAYER_WIN,
		AI_WIN,
		NONE,
	};

	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;
	std::array<Board*, 4> m_boards;
	Board* m_currentBoard;
	Piece m_player;
	Piece m_ai;

	AI m_aiAlg;

	sf::Font m_font;

	sf::Color m_selectedBoardColor{ 227, 189, 0 };

	std::array<sf::RectangleShape, 4> m_boardSwitchButtons;
	std::array<sf::Text, 4> m_boardSwitchTexts;

	sf::RectangleShape* m_currentBoardButton;

	GameState m_currentState = PLAYER_TURN;

	sf::RectangleShape m_gameOverBox;
	sf::Text m_gameOverText;

	sf::RectangleShape m_restartButton;
	sf::Text m_restartText;
};

#endif // !GAME_H
