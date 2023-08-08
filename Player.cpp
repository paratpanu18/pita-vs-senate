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

void Player::Load() {
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
}

void Player::Update(sf::Vector2f enemyPosition) {
    sf::Vector2f currentPosition = playerSprite.getPosition();
    sf::Vector2f playerPosition = playerSprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentPosition.y - spd > 48) {
        playerSprite.setTextureRect(sf::IntRect(0, 96, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(0, -spd));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentPosition.x - spd > 0) {
        playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48));
        playerSprite.setScale(-2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(-spd, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentPosition.y + spd < 600 - 48) {
        playerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(0, spd));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentPosition.x + spd < 800) {
        playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48));
        playerSprite.setScale(2, 2);
        playerSprite.setPosition(currentPosition + sf::Vector2f(spd, 0));
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(5, 5)));
        bullets[bullets.size() - 1].setPosition(playerPosition);

        bulletDirection = sf::Vector2f(enemyPosition) - bullets[bullets.size() - 1].getPosition();
        bulletDirection = normalizeVector(bulletDirection);
    }


    for (int j = 0; j < bullets.size(); j++) {
        if ((bullets[j].getPosition().x <= enemyPosition.x - 5.0f || bullets[j].getPosition().x >= enemyPosition.x + 5.0f) || (bullets[j].getPosition().y <= enemyPosition.y - 5.0f || bullets[j].getPosition().y >= enemyPosition.y + 5.0f)) {
            bullets[j].setPosition(bullets[j].getPosition() + bulletDirection * 3.0f);
        }
        else {
            bullets.erase(bullets.begin());
        }
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(playerSprite);

    // Draw Bullet
    for (int i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i]);
    }
}

sf::Vector2f Player::getPosition()
{
    return playerSprite.getPosition();
}
