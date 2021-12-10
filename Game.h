#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Board.h"
#include "PieceCheck.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void checkWin();

	sf::RenderWindow m_window;
	std::array<Board*, 4> m_boards;
	Board* m_currentBoard;
	Piece m_player;
	Piece m_ai;

	sf::Font m_font;

	sf::Color m_selectedBoardColor{ 227, 189, 0 };

	std::array<sf::RectangleShape, 4> m_boardSwitchButtons;
	std::array<sf::Text, 4> m_boardSwitchTexts;

	sf::RectangleShape* m_currentBoardButton;
};

#endif // !GAME_H
