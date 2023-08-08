#pragma once

class Enemy {
private:
	sf::Texture enemyTexture;
	
public:
	void Init();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();

	sf::Sprite enemySprite;
};