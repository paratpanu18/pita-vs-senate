#pragma once

class Enemy {
private:
	sf::Texture enemyTexture;
	sf::Texture superSenateTexture;
	
public:
	void Init();
	void Load(int x, int y, int inputHP);
	void Update(int& playerHP, int playerMaxHP);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();

	sf::Font statusFont;
	sf::Text statusText;

	int maxHP;
	int HP;
	int enemyStatus;
	int ATK;
	int spd;

	int getStatus();


	sf::Sprite enemySprite;
};