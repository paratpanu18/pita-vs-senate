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
	sf::Text waveDetail;

	sf::Texture hpIconTexture;
	sf::Sprite hpIcon;

	sf::Texture atkIconTexture;
	sf::Sprite atkIcon;

	sf::Texture spdIconTexture;
	sf::Sprite spdIcon;

	sf::Texture critIconTexture;
	sf::Sprite critIcon;

	sf::Text popUpText;
	sf::Clock clock;

	void Init();
	void Update(float hp, int atk, int spd, int critrate, float maxHP, int senateKilled, int wave);
	void Draw(sf::RenderWindow& window);

	void showText(std::string text, sf::Color color, int fontSize, int x, int y);

};

