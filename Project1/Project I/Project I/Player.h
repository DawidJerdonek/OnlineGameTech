#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player();
	~Player();

	void playerMove();
	void chaserCheck();
	void boundary();

	void update(sf::Time t_deltaTime, sf::Time t_deathTime);
	void render(sf::RenderWindow& m_window);


	bool isChaser = false;
	bool isAlive = true;
	sf::CircleShape m_playerShape;

private:

	bool timeDisplayed = false;
	float m_speed = 5.5f;

	void displayDeathTime(sf::Time t_time);
};

