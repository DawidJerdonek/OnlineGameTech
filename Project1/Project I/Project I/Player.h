#pragma once
#include <SFML/Graphics.hpp>
#include "Client.h"
class Player
{
public:
	Player();
	~Player();

	void playerMove(sf::Event t_event, Client* t_client);
	void chaserCheck();
	void boundary();

	void update(sf::Time t_deltaTime, sf::Time t_deathTime, Client* t_client);
	void render(sf::RenderWindow& m_window);

	int m_playerId = 0;
	bool m_isChaser = false;
	bool m_isAlive = true;
	sf::CircleShape m_playerShape;

private:

	int m_initialPosSender = 0;
	bool m_timeDisplayed = false;
	float m_speed = 10.0f;

	void displayDeathTime(sf::Time t_time);
};

