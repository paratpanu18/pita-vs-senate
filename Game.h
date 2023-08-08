#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
	Game(sf::RenderWindow&);

	sf::Texture bg;
	sf::Sprite bgSprite;

	Player pita;
	Enemy slime;

	void Init();
	void Update(sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void GameLoop(sf::RenderWindow& window);

	int isGameClose;
};

