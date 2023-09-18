#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "gui.h"
#include "Player.h"
#include "Enemy.h"
#include "Buff.h"

class Game
{
public:
	Game(sf::RenderWindow&);

	sf::Texture bg;
	sf::Sprite bgSprite;

	int maxEnemy;
	int wave;
	int hpMultiplier;
	Enemy Senate[100] = {};
	int isGameOver;

	gui gui;

	Player pita;

	Buff buff;
	sf::Clock buffCDClock;

	void Init();
	void Update(sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void GameLoop(sf::RenderWindow& window);

	int isGameClose;

	sf::SoundBuffer wavePassSoundBuffer;
	sf::Sound wavePassSound;

	sf::SoundBuffer superSenateAlertBuffer;
	sf::Sound superSenateAlertSFX;

	sf::Music bgmMusic;
};

