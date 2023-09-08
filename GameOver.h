#pragma once
#include "MainMenu.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>
#include "Game.h"

class GameOver
{
public:
	GameOver(int widght, int height, sf::RenderWindow& window, int playerScore);
	void Update(sf::Event& event, sf::RenderWindow& window, int playerScore);
	void Draw(sf::RenderWindow& window);
	void GameOverLoop(sf::RenderWindow& window, int playerScore);
	void SaveHighScore(int playerScore, std::string playerName);

	sf::Font font;
	sf::Text yourScoreText;
	sf::Text playerScoreText;
	sf::Text GameOverText;
	sf::Text EnterYourNameText;
	std::string playerName;
	sf::Text playerNameText;
	sf::Text enterText;

	sf::Texture bgTexture;
	sf::Sprite bg;

	sf::Music bgMusic;
};

