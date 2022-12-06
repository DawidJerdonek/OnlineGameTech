/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{

	setupFontAndText(); // load font 

	chooseChaser();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	deathClock.restart();
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::assignPlayer(int t_playerID)
{
	if (t_playerID == 0)
	{
		isPlayerGreen = true;
	}
	else if (t_playerID == 1)
	{
		isPlayerBlue = true;
	}
	else if (t_playerID == 2)
	{
		isPlayerYellow= true;
	}

}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	deathTime = deathClock.getElapsedTime();
	if (isPlayerGreen)
	{
		m_playerGreen.update(t_deltaTime, deathTime);
	}
	if (isPlayerBlue)
	{
		m_playerBlue.update(t_deltaTime, deathTime);
	}
	if (isPlayerYellow)
	{
		m_playerYellow.update(t_deltaTime, deathTime);
	}


	
	//if (m_player1.isAlive)
	//{
	//	m_player1.playerMove();
	//}
	checkIfCaught();
	m_chaseMessage.setString("Red is the chaser\nTime elapsed: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_chaseMessage);

	m_playerGreen.render(m_window);
	m_playerBlue.render(m_window);
	m_playerYellow.render(m_window);

	for (int i = 0; i < 3; i++)
	{
		m_window.draw(m_deathTimes[i]);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_chaseMessage.setFont(m_ArialBlackfont);
	m_chaseMessage.setString("Red is the chaser\nTime elapsed: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
	m_chaseMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_chaseMessage.setPosition(700.0f, 20.0f);
	m_chaseMessage.setCharacterSize(30U);
	m_chaseMessage.setOutlineColor(sf::Color::Red);
	m_chaseMessage.setFillColor(sf::Color::Transparent);
	m_chaseMessage.setOutlineThickness(2.0f);
	for (int i = 0; i < 3; i++)
	{ 
		m_deathTimes[i].setFont(m_ArialBlackfont);
		m_deathTimes[i].setString("Player -- has survived for: ");
		m_deathTimes[i].setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
		m_deathTimes[i].setCharacterSize(30U);
		m_deathTimes[i].setOutlineColor(sf::Color::Red);
		m_deathTimes[i].setFillColor(sf::Color::Transparent);
		m_deathTimes[i].setOutlineThickness(1.0f);
	}
	m_deathTimes[0].setPosition(650.0f, 90.0f);
	m_deathTimes[1].setPosition(650.0f, 120.0f);
	m_deathTimes[2].setPosition(650.0f, 150.0f);

}


void Game::chooseChaser()
{
	srand(time(NULL));
	int chaserNum = rand() % 3 + 1;
	m_playerGreen.m_playerShape.setFillColor(sf::Color::Green);
	m_playerBlue.m_playerShape.setFillColor(sf::Color::Blue);
	m_playerYellow.m_playerShape.setFillColor(sf::Color::Yellow);
	if (chaserNum == 1)
	{
		m_playerGreen.m_isChaser = true;
		m_playerBlue.m_playerShape.setPosition(200, 200);
		m_playerYellow.m_playerShape.setPosition(1700, 200);
	}
	else if (chaserNum == 2)
	{
		m_playerBlue.m_isChaser = true;
		m_playerGreen.m_playerShape.setPosition(200, 200);
		m_playerYellow.m_playerShape.setPosition(1700, 200);
	}
	else if (chaserNum == 3)
	{
		m_playerYellow.m_isChaser = true;
		m_playerGreen.m_playerShape.setPosition(200, 200);
		m_playerBlue.m_playerShape.setPosition(1700, 200);
	}
	
	m_playerGreen.chaserCheck();
	m_playerBlue.chaserCheck();
	m_playerYellow.chaserCheck();
}

void Game::checkIfCaught()
{
	/// <summary>
	/// Player 1 = Green
	/// Player 2 = Blue
	/// Player 3 = Yellow
	/// </summary>
	/// 
	if (m_playerGreen.m_playerShape.getGlobalBounds().intersects(m_playerBlue.m_playerShape.getGlobalBounds()))
	{
		if (m_playerGreen.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Blue are colliding" << std::endl;
	
			if (m_playerBlue.m_isAlive)
			{
				m_deathTimes[1].setString("Player Blue has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerBlue.m_isAlive = false;
			}
		}
		else if (m_playerBlue.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Green are colliding" << std::endl;
			if (m_playerGreen.m_isAlive)
			{
				m_deathTimes[0].setString("Player Green has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerGreen.m_isAlive = false;
			}
		}
		
	}
	if (m_playerBlue.m_playerShape.getGlobalBounds().intersects(m_playerYellow.m_playerShape.getGlobalBounds()))
	{
		if (m_playerBlue.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Yellow are colliding" << std::endl;
			if (m_playerYellow.m_isAlive)
			{
				m_deathTimes[2].setString("Player Yellow has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerYellow.m_isAlive = false;
			}
		}
		else if (m_playerYellow.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Blue are colliding" << std::endl;
			if (m_playerBlue.m_isAlive)
			{
				m_deathTimes[1].setString("Player Blue has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerBlue.m_isAlive = false;
			}
		}
	}
	if (m_playerGreen.m_playerShape.getGlobalBounds().intersects(m_playerYellow.m_playerShape.getGlobalBounds()))
	{
		if (m_playerGreen.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Yellow are colliding" << std::endl;
			if (m_playerYellow.m_isAlive)
			{
				m_deathTimes[2].setString("Player Yellow has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerYellow.m_isAlive = false;
			}
		}
		else if (m_playerYellow.m_isChaser)
		{
			//std::cout << "Chaser Red and Player Green are colliding" << std::endl;
			if (m_playerGreen.m_isAlive)
			{
				m_deathTimes[0].setString("Player Green has survived for: " + std::to_string(deathClock.getElapsedTime().asSeconds()));
				m_playerGreen.m_isAlive = false;
			}
		}
	}
}
