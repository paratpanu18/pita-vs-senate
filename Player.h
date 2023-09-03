#pragma once

class Player {
private:
	sf::Texture playerTexture;

public:
	std::vector<sf::RectangleShape> bullets;
	sf::Vector2f getPosition();
	sf::Sprite playerSprite;
	sf::Vector2f bulletDirection;

	char facing;
	int spd;
	int atk;
	int hp;
	int maxHP;
	int critRate;
	int enemyKilled;


public:
	void Init(); // Call once
	void Load(int inputHP); // Call once
	void Update(sf::Sprite enemySprite); // Call every frame
	void Draw(sf::RenderWindow& window); // Call every frame
	
};