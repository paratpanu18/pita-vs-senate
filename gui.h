#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"


class gui
{
public:

	sf::RectangleShape statusBox;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBG;

	sf::Font font;
	sf::Text status;
	sf::Text HP;
	sf::Text ATK;
	sf::Text SPD;
	sf::Text CRITRATE;
	sf::Text senateKilled;



	void Init();
	void Update(float hp, int atk, int spd, int critrate, float maxHP, int senateKilled);
	void Draw(sf::RenderWindow& window);

};

