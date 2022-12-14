#include "Player.h"
#include <iostream>

Player::Player()
{
	m_playerShape.setRadius(20);
	m_playerShape.setOrigin(10,10);
	m_playerShape.setPosition(100,100);
	m_playerShape.setFillColor(sf::Color::Yellow);
	m_playerShape.setOutlineColor(sf::Color::White);
	m_playerShape.setOutlineThickness(2.0f);
}

Player::~Player()
{
}

void Player::playerMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_playerShape.move(0, -m_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_playerShape.move(-m_speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_playerShape.move(0, m_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_playerShape.move(m_speed, 0);
	}
}

void Player::chaserCheck()
{
	if (m_isChaser == true)
	{
		m_playerShape.setFillColor(sf::Color::Red);
		m_playerShape.setPosition(1000,1000);
		m_speed = 5.0f;
	}
}

void Player::boundary()
{
	if (m_playerShape.getPosition().x >= 1890)
	{
		m_playerShape.setPosition(1889, m_playerShape.getPosition().y);
	}
	if (m_playerShape.getPosition().x <= 10)
	{
		m_playerShape.setPosition(11, m_playerShape.getPosition().y);
	}
	if (m_playerShape.getPosition().y >= 1050)
	{
		m_playerShape.setPosition(m_playerShape.getPosition().x, 1049);
	}
	if (m_playerShape.getPosition().y <= 10)
	{
		m_playerShape.setPosition(m_playerShape.getPosition().x, 11);
	}
}


void Player::update(sf::Time t_deltaTime, sf::Time t_deathTime)
{
	if (m_isAlive)
	{
		boundary();
		playerMove();
	}
	if (m_timeDisplayed == false)
	{
		if (m_isAlive == false)
		{
			displayDeathTime(t_deathTime);
		}
	}
}

void Player::render(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerShape);
}

void Player::displayDeathTime(sf::Time t_time)
{
	m_timeDisplayed = true;
	std::cout << "player died at 9" << t_time.asSeconds() << std::endl;
}




