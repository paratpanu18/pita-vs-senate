#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"


class endCredit
{
public:
	endCredit(sf::RenderWindow& window, sf::Music& bgm);

	sf::Font font;
	sf::Text creditTitle;
	sf::Text credit;
	sf::Text role;
	sf::Text pleaseProceed;

	sf::Texture bgTexture;
	sf::Sprite bg;
};

