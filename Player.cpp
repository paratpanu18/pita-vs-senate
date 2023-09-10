#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.h"

#define bulletSpeed 5

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

    if (bulletTexture.loadFromFile("Assets/bullet.png")) {
        
    }
    else {
        std::cout << "!!! Player texture failed to load !!!" << std::endl;
    }

    facing = 'u';
    maxHP = inputHP;
    hp = inputHP;
    atk = 40;
    critRate = 45;
    spd = 5;
    enemyKilled = 0;

    canDash = false;
    timeDash = 0;

    for (int i = 0; i < maxBullet; i++) {
        std::cout << "Bullet" << i << "texture loaded successfully" << std::endl;
        bullet[i].setTexture(bulletTexture);
        bullet[i].setTextureRect(sf::IntRect(0, 0, 20, 20));
        bullet[i].setOrigin(10, 10);
        bulletStatus[i] = 0;
    }

    shootSFX.openFromFile("Assets/SFX/bulletShoot.mp3");
}

void Player::Update() {

    sf::Vector2f currentPosition = playerSprite.getPosition();
    sf::Vector2f playerPosition = playerSprite.getPosition();

    if (timeDash < 30) timeDash++;
    else if (timeDash >= 30) canDash = true;

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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && canDash) {
        switch (facing)
        {
        case 'u': playerSprite.setPosition(currentPosition + sf::Vector2f(0, -50)); timeDash = 0; canDash = false; break;
        case 'd': playerSprite.setPosition(currentPosition + sf::Vector2f(0, 50)); timeDash = 0; canDash = false; break;
        case 'l': playerSprite.setPosition(currentPosition + sf::Vector2f(-50, 0)); timeDash = 0; canDash = false; break;
        case 'r': playerSprite.setPosition(currentPosition + sf::Vector2f(50, 0)); timeDash = 0; canDash = false; break;
        default:
            break;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (int i = 0; i < maxBullet; i++) {
            if (isBreak == 1) { isBreak = 0; break; }
            if (bulletStatus[i] == 0) {
                bool canFire = true;

                for (int j = 0; j < maxBullet; j++) {
                    if (i == j || bulletStatus[j] == 0) continue;
                    else if (findLen(bullet[i], bullet[j]) < 20) {
                        canFire = false;
                        isBreak = 1;
                        break;
                    }
                }

                if (canFire) {
                    fireBullet(i);
                    isBreak = 1;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < maxBullet; i++) {

        if (bulletStatus[i] == 1 && bullet[i].getPosition().y > 0 && bullet[i].getPosition().y < 600 && bullet[i].getPosition().x > 0 && bullet[i].getPosition().x < 800) {
            int bulletX = bullet[i].getPosition().x;
            int bulletY = bullet[i].getPosition().y;


            if (bulletDir[i] == 'u') {
                bullet[i].setPosition(sf::Vector2f(bulletX, bulletY - bulletSpeed));
            }
            else if (bulletDir[i] == 'd') {
                bullet[i].setPosition(sf::Vector2f(bulletX, bulletY + bulletSpeed));
            }
            else if (bulletDir[i] == 'l') {
                bullet[i].setPosition(sf::Vector2f(bulletX - bulletSpeed, bulletY));
            }
            else if (bulletDir[i] == 'r') {
                bullet[i].setPosition(sf::Vector2f(bulletX + bulletSpeed, bulletY));
            }

        }
        else {
            bulletStatus[i] = 0;
        }
    }
}

void Player::checkIfBulletHit(sf::Sprite enemySprite, int &HP)
{
    sf::FloatRect enemyHitbox = enemySprite.getGlobalBounds();

    for (int i = 0; i < maxBullet; i++) {
        sf::FloatRect bulletHitbox = bullet[i].getGlobalBounds();

        if (bulletHitbox.intersects(enemyHitbox)) {
            if (bulletStatus[i] == 1) {
                float totalATK = atk;
                if (rand() % 100 < critRate) {
                    isCrit = 1;
                    totalATK *= 2;
                }

                isCrit = 0;

                bulletStatus[i] = 0;
                if (HP - totalATK < 0) {
                    enemyKilled++;
                    HP -= totalATK;
                    break;
                }
                HP -= totalATK;
                continue;
            }
        }
    }
    
}

float Player::findLen(sf::Sprite a, sf::Sprite b)
{
    //std::cout << std::sqrt(pow((b.getPosition().x - a.getPosition().x), 2) + pow((b.getPosition().y - a.getPosition().y), 2)) << "\n";
    return std::sqrt(pow((b.getPosition().x - a.getPosition().x), 2) + pow((b.getPosition().y - a.getPosition().y), 2));
}

void Player::healFull()
{
    hp = maxHP;
}

void Player::skipWave(int num)
{
    if (enemyKilled < num) enemyKilled++;
}

void Player::buff(int inputhp, int inputmaxHP, int inputatk, int inputspd, int inputcritRate)
{
    hp += inputhp;
    maxHP += inputmaxHP;
    atk += inputatk;
    spd += inputspd;
    critRate += inputcritRate;
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(playerSprite);

    for (int i = 0; i < maxBullet; i++) {
        if (bulletStatus[i] == 1) {
            window.draw(bullet[i]);
        }
    }
}

sf::Vector2f Player::getPosition()
{
    return playerSprite.getPosition();
}

void Player::fireBullet(int bulletNum) {
    bulletStatus[bulletNum] = 1;
    bullet[bulletNum].setPosition(sf::Vector2f(playerSprite.getPosition()));

    bulletDir[bulletNum] = facing;
    shootSFX.play();
}
