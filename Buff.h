#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gui.h"

class Buff
{
public:
	void Init(int buffType);
	void Update(sf::Sprite playerSprite);
	void UpdateDuration(int& playerHP, int& playerMaxHP, int& playerATK, int &playerSPD);
	void Draw(sf::RenderWindow& window);

public:
	gui gui;

	sf::Texture buffTexture;
	sf::Sprite buffSprite;

	int type;

	int isBuffActive;
	int isBuffOnfeild;
	int isBuffTriggered;
	sf::Clock buffActiveDuration;

	sf::Clock buffAnimationClock;
	int currentBuffFrame;
};

