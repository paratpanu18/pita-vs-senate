#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

void Enemy::Init() {

}

void Enemy::Load(int x, int y, int inputHP) {
    enemyStatus = 1;
    spd = 2;

    srand(time(NULL));
    int prob = rand() % 100;

    if (prob == 1) {
        if (superSenateTexture.loadFromFile("Assets/enemySpriteSheet.png")) {
            std::cout << "SuperSenate texture loaded successfully" << std::endl;
            enemySprite.setTexture(superSenateTexture);
            enemySprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
            enemySprite.setScale(sf::Vector2f(1.5f, 1.5f));
            enemySprite.setPosition(x, y);
            enemySprite.setOrigin(16, 16);
            maxHP = inputHP * 2;
            HP = maxHP;
        }
        else {
            std::cout << "!!! SuperSenate texture failed to load !!!" << std::endl;
        }
    }
    else {
        if (enemyTexture.loadFromFile("Assets/enemySpriteSheet.png")) {
            std::cout << "Enemy texture loaded successfully" << std::endl;
            enemySprite.setTexture(enemyTexture);
            enemySprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
            enemySprite.setScale(sf::Vector2f(1.5f, 1.5f));
            enemySprite.setPosition(x, y);
            enemySprite.setOrigin(16, 16);
            HP = inputHP;
            maxHP = inputHP;
        }
        else {
            std::cout << "!!! Enemy texture failed to load !!!" << std::endl;
        }
    }

    if (!statusFont.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
        std::cout << "!!! Enemy Status Font failed to load !!!" << std::endl;
    }
    else {
        std::cout << "Enemy Status Font loaded successfully." << std::endl;
        statusText.setFont(statusFont);
        statusText.setCharacterSize(10);
        statusText.setFillColor(sf::Color::White);
        statusText.setPosition(enemySprite.getPosition().x - 10, enemySprite.getPosition().y - 20);
        statusText.setString(std::to_string(maxHP));
    }

}

void Enemy::Update(int &playerHP, int playerMaxHP) {
    if (enemySprite.getPosition().y < 600) {
        enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y + spd);
    }

    float hpRatio = HP / maxHP;

    if (hpRatio >= 0.6f) statusText.setFillColor(sf::Color::Green);
    else if (hpRatio >= 0.4f && hpRatio < 0.6f) statusText.setFillColor(sf::Color::Yellow);
    else if (hpRatio < 0.4f) statusText.setFillColor(sf::Color::Red);
    
    if (HP <= 0) {
        enemyStatus = 0;
        if (playerHP < playerMaxHP) {
            playerHP += 1;
        }
    }

    if (enemySprite.getPosition().y >= 600) {
        enemyStatus = 0;
        playerHP-=ATK;
    }

    statusText.setPosition(enemySprite.getPosition().x - 6, enemySprite.getPosition().y - 40);
    statusText.setString(std::to_string(HP));
}

void Enemy::Draw(sf::RenderWindow& window) {
    if (enemyStatus == 1) {
        window.draw(statusText);
        window.draw(enemySprite);
    }
    
    
}

sf::Vector2f Enemy::getPosition()
{
    return enemySprite.getPosition();
}

sf::Sprite Enemy::getSprite()
{
    return enemySprite;
}

int Enemy::getStatus() {
    return enemyStatus;
}
