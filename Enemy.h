#pragma once

class Enemy {
private:
	sf::Texture enemyTexture;
	
public:
	void Init();
	void Load(int x, int y, int inputHP);
	void Update();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();

	sf::Font statusFont;
	sf::Text statusText;

	int maxHP;
	int HP;


	sf::Sprite enemySprite;
};