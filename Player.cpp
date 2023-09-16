#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.h"

#define bulletSpeed 6

sf::Vector2f normalizeVector(sf::Vector2f vector) {
    float vectorMagnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalizeVector = sf::Vector2f(vector.x / vectorMagnitude, vector.y / vectorMagnitude);
    return normalizeVector;
}

void Player::Init() {

}

void Player::Load(int inputHP) {
    // Texture Init
    if (playerTexture.loadFromFile("Assets/Player/Texture/playerTexture.png")) {
        std::cout << "Player texture loaded successfully" << std::endl;
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
        playerSprite.setScale(sf::Vector2f(2.5f, 2.5f));
        playerSprite.setPosition(640, 600);
        playerSprite.setOrigin(24, 24);
    }
    else {
        std::cout << "!!! Player texture failed to load !!!" << std::endl;
    }

    antiStunActiveTexture.loadFromFile("Assets/Player/Texture/antiStunActiveEffect.png");
    antiStunActiveEffect.setTexture(antiStunActiveTexture);

    if (bulletTexture.loadFromFile("Assets/fireball.png")) {
        
    }
    else {
        std::cout << "!!! Bullet texture failed to load !!!" << std::endl;
    }

    // Player Status Init
    facing = 'u';
    maxHP = inputHP;
    hp = inputHP;
    atk = 40;
    critRate = 45;
    spd = 5;
    enemyKilled = 0;
    canDash = false;
    dashCD.restart();
    antiStunActive = false;
    canUseAntiStun = false;

    // Bullet Texture Init
    for (int i = 0; i < maxBullet; i++) {
        std::cout << "Bullet" << i << "texture loaded successfully" << std::endl;
        bullet[i].setTexture(bulletTexture);
        bullet[i].setScale(1, 1);
        bullet[i].setTextureRect(sf::IntRect(0, 0, 64, 64));
        bullet[i].setOrigin(32,32);
        bulletStatus[i] = 0;
    }

    // Dash CD Status Init
    dashCDStatusBack.setSize(sf::Vector2f(3, 48));
    dashCDStatusBack.setFillColor(sf::Color::Black);
    dashCDStatus.setSize(sf::Vector2f(3, 48));
    dashCDStatus.setFillColor(sf::Color(66, 176, 245));

    // Sound Init
    shootSoundBuffer.loadFromFile("Assets/SFX/bulletShoot.mp3");
    shootSound.setBuffer(shootSoundBuffer);
    shootSound.setVolume(50);

    dashSoundBuffer.loadFromFile("Assets/SFX/dashSFX.mp3");
    dashSound.setBuffer(dashSoundBuffer);
    dashSound.setVolume(70);

    antiStunSoundBuffer.loadFromFile("Assets/SFX/antiStunSFX.mp3");
    antiStunSound.setBuffer(antiStunSoundBuffer);
    antiStunSound.setVolume(70);

    StunSoundBuffer.loadFromFile("Assets/SFX/StunSFX.mp3");
    StunSound.setBuffer(StunSoundBuffer);
    StunSound.setVolume(70);
}

void Player::Update() {

    sf::Vector2f currentPosition = playerSprite.getPosition();
    sf::Vector2f playerPosition = playerSprite.getPosition();

    if (dashCD.getElapsedTime().asSeconds() > 2) {
        canDash = true;
    }

    if (bulletFireCD.getElapsedTime().asMilliseconds() > 180) {
        canFire = true;
    }

    frameTimePlayer = sf::seconds(0.2f);

    if (!isPlayerStun || antiStunActive) {

        if (frameClockPlayer.getElapsedTime() >= frameTimePlayer) {
            frameClockPlayer.restart();
            currentFramePlayer = ((currentFramePlayer + 1) % 6);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currentPosition.y - spd > 48) {

            playerSprite.setTextureRect(sf::IntRect(currentFramePlayer * 48, 96, 48, 48));
            playerSprite.setScale(2.5f, 2.5f);
            playerSprite.setPosition(currentPosition + sf::Vector2f(0, -spd));
            facing = 'u';
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currentPosition.x - spd > 0) {
            playerSprite.setTextureRect(sf::IntRect(currentFramePlayer * 48, 48, 48, 48));
            playerSprite.setScale(-2.5f, 2.5f);
            playerSprite.setPosition(currentPosition + sf::Vector2f(-spd, 0));
            facing = 'l';
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currentPosition.y + spd < 700 - 48) {
            playerSprite.setTextureRect(sf::IntRect(currentFramePlayer * 48, 0, 48, 48));
            playerSprite.setScale(2.5f, 2.5f);
            playerSprite.setPosition(currentPosition + sf::Vector2f(0, spd));
            facing = 'd';
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currentPosition.x + spd < 1270) {
            playerSprite.setTextureRect(sf::IntRect(currentFramePlayer * 48, 48, 48, 48));
            playerSprite.setScale(2.5f, 2.5f);
            playerSprite.setPosition(currentPosition + sf::Vector2f(spd, 0));
            facing = 'r';
        }

        if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && canDash) {
            switch (facing)
            {
            case 'u': playerSprite.setPosition(currentPosition + sf::Vector2f(0, -100)); dashCD.restart(); canDash = false; break;
            case 'd': playerSprite.setPosition(currentPosition + sf::Vector2f(0, 100)); dashCD.restart(); canDash = false; break;
            case 'l': playerSprite.setPosition(currentPosition + sf::Vector2f(-100, 0)); dashCD.restart(); canDash = false; break;
            case 'r': playerSprite.setPosition(currentPosition + sf::Vector2f(100, 0)); dashCD.restart(); canDash = false; break;
            default:
                break;
            }
            dashSound.play();
        }

        if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (canFire || antiStunActive)) {
            for (int i = 0; i < maxBullet; i++) {
                if (bulletStatus[i] == 0) {
                    fireBullet(i);
                    break;
                }
            }
            canFire = false;
            bulletFireCD.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && canUseAntiStun) {
            antiStunSound.play();
            std::cout << "Anti Stun activated\n";
            antiStunActive = true;
            canUseAntiStun = false;
            antiStunDuration.restart();
            antiStunCD.restart();
        }

    }

    frameTimeBullet = sf::seconds(0.2f);

    if (frameClockBullet.getElapsedTime() >= frameTimeBullet) {
        frameClockBullet.restart();
        currentFrameBullet = ((currentFrameBullet + 1) % 8);
    }



    for (int i = 0; i < maxBullet; i++) {

        if (bulletStatus[i] == 1 && bullet[i].getPosition().y > 0 && bullet[i].getPosition().y < 720 && bullet[i].getPosition().x > 0 && bullet[i].getPosition().x < 1280) {
            int bulletX = bullet[i].getPosition().x;
            int bulletY = bullet[i].getPosition().y;

            if (bulletDir[i] == 'u') {
                bullet[i].setPosition(sf::Vector2f(bulletX, bulletY - bulletSpeed));
                bullet[i].setTextureRect(sf::IntRect(currentFrameBullet * 64, 128, 64, 64));
            }
            else if (bulletDir[i] == 'd') {
                bullet[i].setPosition(sf::Vector2f(bulletX, bulletY + bulletSpeed));
                bullet[i].setTextureRect(sf::IntRect(currentFrameBullet * 64, 384, 64, 64));
            }
            else if (bulletDir[i] == 'l') {
                bullet[i].setPosition(sf::Vector2f(bulletX - bulletSpeed, bulletY));
                bullet[i].setTextureRect(sf::IntRect(currentFrameBullet * 64, 0, 64, 64));
            }
            else if (bulletDir[i] == 'r') {
                bullet[i].setPosition(sf::Vector2f(bulletX + bulletSpeed, bulletY));
                bullet[i].setTextureRect(sf::IntRect(currentFrameBullet * 64, 256, 64, 64));
            }

        }
        else {
            bulletStatus[i] = 0;
        }
    }

    if (antiStunCD.getElapsedTime().asSeconds() < 10) {
        canUseAntiStun = false;
    }
    else if (antiStunCD.getElapsedTime().asSeconds() > 10 && !canUseAntiStun) {
        canUseAntiStun = true; std::cout << "Anti Stun REady\n";
    }

    if (antiStunDuration.getElapsedTime().asSeconds() > 3 && antiStunActive) { antiStunActive = false; std::cout << "Inactivated\n"; }

    if (antiStunActive) antiStunActiveEffect.setPosition(sf::Vector2f(playerSprite.getPosition().x - 24, playerSprite.getPosition().y + 5));

    // Dash CD Status Update
    dashCDStatusBack.setPosition(currentPosition + sf::Vector2f(30, -5));
    dashCDStatus.setPosition(currentPosition + sf::Vector2f(30, -5));
    dashCDStatus.setSize(sf::Vector2f(3, (dashCD.getElapsedTime().asSeconds() / 2.0f) * 48));


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
                if (HP - totalATK <= 0) {
                    enemyKilled++;
                    HP -= totalATK;
                    break;
                }
                HP -= totalATK;
                continue;
            }
        }
    }

    if (playerSprite.getGlobalBounds().intersects(enemyHitbox) && !isPlayerStun && stunClock.getElapsedTime().asSeconds() > 1 && !antiStunActive) {
        isPlayerStun = true;
        playerSprite.setTextureRect(sf::IntRect(96, 432, 48, 48));
        StunSound.play();
        stunClock.restart();
    }
    
    if (stunClock.getElapsedTime().asSeconds() > 0.5f) {
        switch (facing)
        {
        case 'u': playerSprite.setTextureRect(sf::IntRect(0, 96, 48, 48)); break;
        case 's': playerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48)); break;
        case 'l': playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48)); playerSprite.setScale(-2.5f, 2.5f); break;
        case 'r': playerSprite.setTextureRect(sf::IntRect(0, 48, 48, 48)); break;
        default:
            break;
        }
        isPlayerStun = false;
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
    if (antiStunActive) window.draw(antiStunActiveEffect);
    window.draw(playerSprite);

    for (int i = 0; i < maxBullet; i++) {
        if (bulletStatus[i] == 1) {
            window.draw(bullet[i]);
        }
    }

    if (!canDash) {
        window.draw(dashCDStatusBack);
        window.draw(dashCDStatus);
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
    shootSound.play();
}
