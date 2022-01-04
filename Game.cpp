#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 700, 600 }, "SFML Starter" }, m_player{ sf::Color::Red, 75, PieceCheck::PLAYER }, m_ai{ sf::Color::Yellow, 75, PieceCheck::AI }
{
	m_font.loadFromFile("Assets/CaviarDreams.ttf");

	int boardIndex{};
	for (auto& board : m_boards)
	{
		board = new Board(boardIndex);
		++boardIndex;
	}

	for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		m_boardSwitchButtons[i].setFillColor(sf::Color::White);
		m_boardSwitchButtons[i].setSize(sf::Vector2f{ 100.0f, 150.0f });
		m_boardSwitchButtons[i].setPosition(600.0f, 150.0f * i);
		m_boardSwitchButtons[i].setOutlineThickness(0.5f);
		m_boardSwitchButtons[i].setOutlineColor(sf::Color::Black);

		m_boardSwitchTexts[i].setFont(m_font);
		m_boardSwitchTexts[i].setCharacterSize(24u);
		m_boardSwitchTexts[i].setString("Board\n   " + std::to_string(i + 1));
		m_boardSwitchTexts[i].setPosition(m_boardSwitchButtons[i].getPosition().x + 20.0f,
			m_boardSwitchButtons[i].getPosition().y + m_boardSwitchButtons[i].getGlobalBounds().height / 3.0f);
		m_boardSwitchTexts[i].setFillColor(sf::Color::Black);
	}

	m_gameOverBox.setFillColor(sf::Color(105, 105, 105));
	m_gameOverBox.setSize(sf::Vector2f{ 700.0f, 100.0f });

	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(24u);
	m_gameOverText.setPosition(sf::Vector2f{ 0.0f + 20.0f,
		m_gameOverBox.getPosition().y + m_gameOverBox.getGlobalBounds().height / 3.0f });

	m_restartButton.setFillColor(sf::Color(194, 0, 0));
	m_restartButton.setSize(sf::Vector2f{ 200.0f, 50.0f });
	m_restartButton.setPosition(sf::Vector2f{ 700.0f - m_restartButton.getGlobalBounds().width - 50.0f, m_gameOverText.getPosition().y / 1.5f });

	m_restartText.setFont(m_font);
	m_restartText.setCharacterSize(24u);
	m_restartText.setString("Restart");
	m_restartText.setPosition(sf::Vector2f{ m_restartButton.getPosition().x + 20.0f,
		m_restartButton.getPosition().y + m_restartButton.getGlobalBounds().height / 4.0f });

	m_currentBoard = m_boards[0];
	m_currentBoardButton = &m_boardSwitchButtons[0];
	m_currentBoardButton->setFillColor(m_selectedBoardColor);
}

Game::~Game()
{
	for (auto& board : m_boards)
	{
		delete board;
	}
}

/// <summary>
/// game loop @ 60 fps
/// </summary>
void Game::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{ sf::Time::Zero };
	sf::Time timePerFrame{ sf::seconds(1.0f / 60.f) }; // 60 fps

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// check for input
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		// quit when ESC is pressed or when the window is closed manually
		if ((sf::Keyboard::Escape == newEvent.key.code) ||
			sf::Event::Closed == newEvent.type)
		{
			m_window.close();
		}
	}
}

/// <summary>
/// update the game world @ 60 fps
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_currentState == PLAYER_TURN)
	{
		if (m_currentBoard->placement(&m_window, &m_player))
		{
			if (m_player.checkWin(m_boards))
			{
				m_gameOverText.setString("You Win!");
				m_currentState = PLAYER_WIN;
			}
		}

		for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
		{
			if (m_boardSwitchButtons[i].getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_currentBoardButton->setFillColor(sf::Color::White);
					m_currentBoardButton = &m_boardSwitchButtons[i];
					m_currentBoardButton->setFillColor(m_selectedBoardColor);
					m_currentBoard = m_boards.at(i);
				}
			}
		}
	}
	else if (m_currentState == PLAYER_WIN)
	{
		if (m_restartButton.getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_player.resetPositions();

				for (auto& board : m_boards)
				{
					board->resetOwner();
				}
				m_currentState = PLAYER_TURN;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_player.resetPositions();

			for (auto& board : m_boards)
			{
				board->resetOwner();
			}
			m_currentState = PLAYER_TURN;
		}
	}
}

/// <summary>
/// draw the screen
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_currentBoard->render(&m_window);
	m_player.render(&m_window, m_currentBoard->index());

	for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		m_window.draw(m_boardSwitchButtons[i]);
		m_window.draw(m_boardSwitchTexts[i]);
	}

	if (m_currentState == PLAYER_WIN)
	{
		m_window.draw(m_gameOverBox);
		m_window.draw(m_gameOverText);
		m_window.draw(m_restartButton);
		m_window.draw(m_restartText);
	}

	m_window.display();
}
