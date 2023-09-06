#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "GameOver.h"
#include <iostream>

bool isMouseRelease = false;

Game::Game(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    isGameClose = 0;

    maxEnemy = 5;
    wave = 1;
    hpMultiplier = 100;

    pita.Load(10);

    srand(time(NULL));

    for (int i = 0; i < maxEnemy; i++) {
        int x = (rand() % 700) + 50;
        int y = (rand() % 50);
        int hp = (rand() % 50) + hpMultiplier;
        Senate[i].Load(x, y, hp);
        Senate[i].ATK = 3;
    }

    isGameOver = 0;
    gui.Init();

    bg.loadFromFile("Assets/bg.jpg");
    bgSprite.setTexture(bg);

    GameLoop(window);
}

void Game::Init()
{
    

}

void Game::Update(sf::Event& event, sf::RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyReleased) {
            // Escape
            if (event.key.code == sf::Keyboard::Escape) {
                window.clear(sf::Color::Black);
                isGameClose = 1;
                MainMenu menu(800, 600, window);
            }
        }
             
    }

    for (int i = 0; i < maxEnemy; i++) {
        Senate[i].Update(pita.hp);
    }

    for (int i = 0; i < maxEnemy; i++) {
        if (Senate[i].enemyStatus == 0) {
            int x = (rand() % 700) + 50;
            int y = (rand() % 50);
            int hp = (rand() % 50) + hpMultiplier;
            Senate[i].Load(x, y, hp);
            switch (wave) {
            case 1: Senate[i].ATK = 3; break;
            case 2: Senate[i].ATK = 5; break;
            case 3: Senate[i].ATK = 7; break;
            case 4: Senate[i].ATK = 9; break;
            case 5: Senate[i].ATK = 10; break;
            }
        }
    }

    pita.Update();

    for (int i = 0; i < 10; i++) {
        pita.checkIfBulletHit(Senate[i].getSprite(), Senate[i].HP);
    }

    gui.Update(pita.hp, pita.atk, pita.spd, pita.critRate, pita.maxHP, pita.enemyKilled, wave);

    if (pita.enemyKilled > 200) {
        wave = 5;
        hpMultiplier = 500;
        pita.atk = 250;
        maxEnemy = 20;
    }
    else if (pita.enemyKilled > 150) {
        wave = 4;
        hpMultiplier = 400;
        pita.atk = 200;
        maxEnemy = 15;
    }
    else if (pita.enemyKilled > 100) {
        wave = 3;
        hpMultiplier = 300;
        pita.atk = 150;
        maxEnemy = 13;
    }
    else if (pita.enemyKilled > 50) {
        wave = 2;
        hpMultiplier = 200;
        pita.atk = 100;
        maxEnemy = 10;
        pita.maxHP = 150;
    }

    if (pita.hp <= 0) {
        isGameOver = 1;
    }
}

void Game::Draw(sf::RenderWindow& window)
{
    if (!isGameOver) {
        window.clear(sf::Color::Black);

        window.draw(bgSprite);
        pita.Draw(window);
    
        for (int i = 0; i < maxEnemy; i++) {
            Senate[i].Draw(window);
        }


        gui.Draw(window);

        window.display();
    }

    else {
        window.clear(sf::Color::Black);
        isGameClose = 1;
        GameOver over(800, 600, window, pita.enemyKilled);
    }


}

void Game::GameLoop(sf::RenderWindow& window)
{
    while (window.isOpen() && isGameClose == 0) {
        sf::Event event;

        Update(event, window);
        Draw(window);

    }
}
