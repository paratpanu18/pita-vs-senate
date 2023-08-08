#pragma once

class Player {
private:
	sf::Texture playerTexture;

public:
	std::vector<sf::RectangleShape> bullets;
	sf::Vector2f getPosition();
	sf::Sprite playerSprite;
	sf::Vector2f bulletDirection;
	float spd = 3.0f;
	float atk;
	float hp;
	float critRate;


public:
	void Init(); // Call once
	void Load(); // Call once
	void Update(sf::Vector2f enemyPosition); // Call every frame
	void Draw(sf::RenderWindow& window); // Call every frame
	
};