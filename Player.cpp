#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

sf::Vector2f normalizeVector(sf::Vector2f vector) {
    float vectorMagnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalizeVector = sf::Vector2f(vector.x / vectorMagnitude, vector.y / vectorMagnitude);
    return normalizeVector;
}

void Player::Init() {

}

void Player::Load(int inputHP) {
    if (playerTexture.loadFromFile("Assets/Player/Texture/playerTexture.png")) {
        std::cout << "Player texture loaded successfully" << std::endl;
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
        playerSprite.setScale(sf::Vector2f(2, 2));
        playerSprite.setPosition(400, 300);
        playerSprite.setOrigin(24, 24);
    }
    else {
        std::cout << "!!! Player texture failed to load !!!" << std::endl;
    }

    facing = 'u';
    maxHP = inputHP;
    hp = inputHP;
    atk = 10;
    critRate = 45;
    spd = 3;
    enemyKilled = 0;
}

void Player::Update(sf::Sprite enemySprite) {
    sf::Vector2f currentPosition = playerSprite.getPosition();
    sf::Vector2f playerPosition = playerSprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentPosition.y - spd > 48) {
        playerSprite.setTextureRect(sf::IntRect(0, 96, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(0, -spd));
        facing = 'u';
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentPosition.x - spd > 0) {
        playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48));
        playerSprite.setScale(-2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(-spd, 0));
        facing = 'l';
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentPosition.y + spd < 600 - 48) {
        playerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(0, spd));
        facing = 'd';
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentPosition.x + spd < 800) {
        playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(spd, 0));
        facing = 'r';
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        enemyKilled++;
        hp--;
    }

}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(playerSprite);
}

sf::Vector2f Player::getPosition()
{
    return playerSprite.getPosition();
}
