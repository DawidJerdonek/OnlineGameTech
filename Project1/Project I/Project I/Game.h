/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void assignPlayer(int t_playerID);
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void chooseChaser();
	void checkIfCaught();

	sf::Time deathTime;
	sf::Clock deathClock;

	Player m_playerGreen;
	Player m_playerBlue;
	Player m_playerYellow;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_chaseMessage; // text used for message on screen
	/// <summary>
	/// Used for displayed each player death Time
	/// </summary>
	sf::Text m_deathTimes[3];

	bool isPlayerGreen = false;
	bool isPlayerBlue= false;
	bool isPlayerYellow = false;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

