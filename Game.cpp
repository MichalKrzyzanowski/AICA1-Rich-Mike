#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 700, 600 }, "SFML Starter" }
{
	m_font.loadFromFile("Assets/CaviarDreams.ttf");

	for (auto& board : m_boards)
	{
		board = new Board();
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
	m_currentBoard->update(t_deltaTime, &m_window);

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

/// <summary>
/// draw the screen
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_currentBoard->render(&m_window);

	for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		m_window.draw(m_boardSwitchButtons[i]);
		m_window.draw(m_boardSwitchTexts[i]);
	}

	m_window.display();
}