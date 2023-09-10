#pragma once
#define maxBullet 10
#include <SFML/Audio.hpp>

class Player {
private:
	sf::Texture playerTexture;

public:
	sf::Sprite bullet[maxBullet];
	int bulletStatus[maxBullet];
	sf::Vector2f getPosition();
	sf::Sprite playerSprite;
	sf::Vector2f bulletDirection;

	sf::Texture bulletTexture;

	char facing;
	char bulletDir[maxBullet];
	int spd;
	int atk;
	int hp;
	int maxHP;
	int critRate;
	int enemyKilled;
	int isCrit;
	bool canDash;

	int timeDash;

	int isBreak;

	sf::Music shootSFX;


public:
	void Init(); // Call once
	void Load(int inputHP); // Call once
	void Update(); // Call every frame
	void Draw(sf::RenderWindow& window); // Call every frame
	void fireBullet(int bulletNum);
	void checkIfBulletHit(sf::Sprite enemySprite, int &HP);
	float findLen(sf::Sprite a, sf::Sprite b);
	void healFull();
	void skipWave(int num);

	void buff(int hp, int maxHP, int atk, int spd, int critRate);
	
};