#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

void Enemy::Init() {

}

void Enemy::Load(int x, int y, int inputHP) {
    enemyStatus = 1;
    maxHP = inputHP;
    spd = 5;

    if (enemyTexture.loadFromFile("Assets/slime.png")) {
        std::cout << "Enemy texture loaded successfully" << std::endl;
        enemySprite.setTexture(enemyTexture);
        enemySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        enemySprite.setScale(sf::Vector2f(2, 2));
        enemySprite.setPosition(x, y);
        enemySprite.setOrigin(16, 16);
    }
    else {
        std::cout << "!!! Enemy texture failed to load !!!" << std::endl;
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

    HP = maxHP;
}

void Enemy::Update(int &playerHP) {
    if (enemySprite.getPosition().y < 600) {
        enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y + spd);
    }

    if (HP >= 60) statusText.setFillColor(sf::Color::Green);
    else if (HP >= 40 && HP < 60) statusText.setFillColor(sf::Color::Yellow);
    else if (HP < 40) statusText.setFillColor(sf::Color::Red);
    
    if (HP < 0) {
        enemyStatus = 0;
    }

    if (enemySprite.getPosition().y >= 600) {
        enemyStatus = 0;
        playerHP-=ATK;
    }

    statusText.setPosition(enemySprite.getPosition().x - 6, enemySprite.getPosition().y - 20);
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
