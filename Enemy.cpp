#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>

void Enemy::Init() {

}

void Enemy::Load() {
    if (enemyTexture.loadFromFile("Assets/slime.png")) {
        std::cout << "Enemy texture loaded successfully" << std::endl;
        enemySprite.setTexture(enemyTexture);
        enemySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        enemySprite.setScale(sf::Vector2f(2, 2));
        enemySprite.setPosition(400, 300);
        enemySprite.setOrigin(16, 16);
    }
    else {
        std::cout << "!!! Enemy texture failed to load !!!" << std::endl;
    }
}

void Enemy::Update() {

}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(enemySprite);
}

sf::Vector2f Enemy::getPosition()
{
    return enemySprite.getPosition();
}
