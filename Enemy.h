#pragma once
#include "gui.h"

class Enemy {
private:
	sf::Texture enemyTexture;
	sf::Texture superSenateTexture;
	
public:
	void Init();
	void Load(int x, int y, int inputHP, int prob);
	void Update(int& playerHP, int &playerMaxHP, int& playerAtk, int& playerSpd);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();

	sf::Font statusFont;
	sf::Text statusText;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;

	int maxHP;
	int HP;
	int enemyStatus;
	int ATK;
	int spd;
	int type; // 0 = Senate / 1 = Super Senate

	int getStatus();


	sf::Sprite enemySprite;
	sf::Time frameTime;
	sf::Clock frameClock;
	int currentFrame = 0;
};