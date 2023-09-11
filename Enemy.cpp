#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

void Enemy::Init() {
    superSenateTexture.loadFromFile("Assets/enemySpriteSheet.png");
    enemyTexture.loadFromFile("Assets/enemySpriteSheet.png");
}

void Enemy::Load(int x, int y, int inputHP,int prob) {
    enemyStatus = 1;
    spd = 2;

    if (prob < 5) { // Seper Senate spawn at rate of 5%
            std::cout << "SuperSenate texture loaded successfully" << std::endl;
            enemySprite.setTexture(superSenateTexture);
            enemySprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
            enemySprite.setScale(sf::Vector2f(1.5f, 1.5f));
            enemySprite.setPosition(x, y);
            enemySprite.setOrigin(16, 16);
            maxHP = inputHP * 3;
            HP = maxHP;
            type = 1;
    }
    else {
            std::cout << "Enemy texture loaded successfully" << std::endl;
            enemySprite.setTexture(enemyTexture);
            enemySprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
            enemySprite.setScale(sf::Vector2f(1.5f, 1.5f));
            enemySprite.setPosition(x, y);
            enemySprite.setOrigin(16, 16);
            HP = inputHP;
            maxHP = inputHP;
            type = 0;
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

void Enemy::Update(int& playerHP, int& playerMaxHP, int& playerAtk, int& playerSpd) {
    if (enemySprite.getPosition().y < 600) {
        enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y + spd);
    }

    frameTime = sf::seconds(0.2f);

    if (frameClock.getElapsedTime() >= frameTime) {
        frameClock.restart();
        currentFrame = ((currentFrame + 1) % 3);
        switch (type) {
        case 0: enemySprite.setTextureRect(sf::IntRect(currentFrame * 32, 224, 32, 32)); break;
        case 1: enemySprite.setTextureRect(sf::IntRect(currentFrame * 32, 256, 32, 32)); break;
        }
    }

    float hpRatio = (float)HP / (float)maxHP;

    if (hpRatio >= 0.6f) statusText.setFillColor(sf::Color::Green);
    else if (hpRatio >= 0.4f && hpRatio < 0.6f) statusText.setFillColor(sf::Color::Yellow);
    else if (hpRatio < 0.4f) statusText.setFillColor(sf::Color::Red);
    
    if (HP <= 0) {
        enemyStatus = 0;
        if (playerHP < playerMaxHP) {
            playerHP += 1;
        }
        if (type == 1) {  
            int buff = rand() % 3;
            switch (buff)
            {
            case 0: playerMaxHP += 3; playerHP += 3; break;
            case 1: playerAtk += 2; break;
            case 3: playerSpd += 1; break;
            default:
                break;
            }
        }
    }

    if (enemySprite.getPosition().y >= 600) {
        if (type == 1) {
            playerHP -= 100000; // Super Senate Instant dead
        }
        else {
            enemyStatus = 0;
            playerHP-=ATK;
        }
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
