#include "Buff.h"

void Buff::Init(int buffType)
{
	gui.Init();
	switch (buffType) {
	case 0: {
		// HP
		type = 0;
		buffTexture.loadFromFile("Assets/enemySpriteSheet.png");
		buffSprite.setTexture(buffTexture);
		buffSprite.setScale(1, 1);
		buffSprite.setTextureRect(sf::IntRect(160, 288, 32, 32));
		break;
	}
	case 1: {
		// Score x2
		type = 1;
		buffTexture.loadFromFile("Assets/enemySpriteSheet.png");
		buffSprite.setTexture(buffTexture);
		buffSprite.setScale(1, 1);
		buffSprite.setTextureRect(sf::IntRect(128, 320, 32, 32));
		break;
	}
	case 2: {
		// Smth
		type = 2;
		buffTexture.loadFromFile("Assets/enemySpriteSheet.png");
		buffSprite.setTexture(buffTexture);
		buffSprite.setScale(1, 1);
		buffSprite.setTextureRect(sf::IntRect(128, 256, 32, 32));
		break;
	}
	}

	// Random Position On the map
	int x = 100 + (rand() % 1000);
	int y = 50 + (rand() % 500);
	buffSprite.setPosition(x, y);

	gui.showText("Buff randomly appered !", sf::Color::White, 20, 0, 0, 0, sf::Color::White, 5);

	isBuffActive = 0;
	isBuffOnfeild = 1;
}

void Buff::Update(sf::Sprite playerSprite)
{
	// Animation
	if (buffAnimationClock.getElapsedTime().asMilliseconds() > 250) {
		switch (type) {
		case 0: {
			currentBuffFrame = (currentBuffFrame + 1) % 7;
			buffSprite.setTextureRect(sf::IntRect((6 + currentBuffFrame) * 32, 288, 32, 32));
			break;
		}
		case 1: {
			currentBuffFrame = (currentBuffFrame + 1) % 5;
			buffSprite.setTextureRect(sf::IntRect((5 + currentBuffFrame) * 32, 320, 32, 32));
			break;
		}
		case 2: {
			currentBuffFrame = (currentBuffFrame + 1) % 10;
			buffSprite.setTextureRect(sf::IntRect((5 + currentBuffFrame) * 32, 256, 32, 32));
			break;
		}
		}
		buffAnimationClock.restart();
	}

	// Buff Active
	if (buffSprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds())) {
		isBuffOnfeild = 0;
		isBuffActive = 1;
		buffActiveDuration.restart();
	}
}

void Buff::UpdateDuration(int& playerHP, int& playerMaxHP, int& playerATK, int &playerSPD)
{
	if (isBuffActive && buffActiveDuration.getElapsedTime().asSeconds() < 5) {
		if (!isBuffTriggered) {
			isBuffTriggered = 1;
			switch (type) {
			case 0: {

			}
			case 1: {

			}
			case 2: {

			}
			}
		}
	}
	else if (buffActiveDuration.getElapsedTime().asSeconds() >= 5) {
		isBuffActive = 0;
		isBuffTriggered = 0;
	}
}

void Buff::Draw(sf::RenderWindow& window)
{
	if (isBuffOnfeild) {
		window.draw(buffSprite);
	}

	gui.DrawPopup(window);
}
