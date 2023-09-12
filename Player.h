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

	sf::Clock stunClock;
	bool isPlayerStun;
	

	sf::Music shootSFX;

	sf::SoundBuffer shootSoundBuffer;
	sf::Sound shootSound;

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

	sf::Time frameTimeBullet;
	sf::Clock frameClockBullet;
	int currentFrameBullet = 0;

	sf::Time frameTimePlayer;
	sf::Clock frameClockPlayer;
	int currentFramePlayer = 0;

	void buff(int hp, int maxHP, int atk, int spd, int critRate);
	
};