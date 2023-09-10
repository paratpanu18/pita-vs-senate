#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "GameWin.h"
#include <iostream>

bool isWaveBuff[5];

Game::Game(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    isGameClose = 0;

    for (int i = 0; i < 5; i++) {
        isWaveBuff[i] = false;
    }

    maxEnemy = 5;
    wave = 1;
    hpMultiplier = 100;

    pita.Load(100);

    srand(time(NULL));

    /*
    for (int i = 0; i < maxEnemy; i++) {

        int x = (rand() % 700) + 50;
        int y = (rand() % 50);
        int hp = (rand() % 50) + hpMultiplier;
        int prob = rand() % 100;

        Senate[i].Load(x, y, hp, prob);
        Senate[i].ATK = 3;
    }
    */

    isGameOver = 0;
    gui.Init();

    bg.loadFromFile("Assets/bg.jpg");
    bgSprite.setTexture(bg);

    bgmMusic.openFromFile("Assets/BGM/gameBGM.mp3");
    bgmMusic.setLoop(true);
    bgmMusic.play();

    GameLoop(window);
}

void Game::Init()
{
    

}

void Game::Update(sf::Event& event, sf::RenderWindow& window)
{
    // Cheat
    //pita.skipWave(240);
    //pita.enemyKilled = 250;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyReleased) {
            // Escape
            if (event.key.code == sf::Keyboard::Escape) {
                window.clear(sf::Color::Black);
                isGameClose = 1;
                bgmMusic.stop();
                MainMenu menu(800, 600, window);
            }
        }
             
    }

    for (int i = 0; i < maxEnemy; i++) {
        Senate[i].Update(pita.hp, pita.maxHP, pita.atk, pita.spd);
    }

    if (pita.enemyKilled >= 200 && isWaveBuff[3] == false) {
        wave = 5;
        hpMultiplier = 500;
        pita.buff(0, 0, 50, 1, 10); // HP maxHP ATK SPD CRIT
        pita.healFull();
        maxEnemy = 20;
        isWaveBuff[3] = true;
    }
    else if (pita.enemyKilled >= 150 && pita.enemyKilled <= 199 && isWaveBuff[2] == false) {
        wave = 4;
        hpMultiplier = 400;
        pita.buff(0, 0, 50, 1, 10); // HP maxHP ATK SPD CRIT
        pita.healFull();
        maxEnemy = 15;
        isWaveBuff[2] = true;
    }
    else if (pita.enemyKilled >= 100 && pita.enemyKilled <= 149 &&  isWaveBuff[1] == false) {
        wave = 3;
        hpMultiplier = 300;
        pita.buff(0, 0, 50, 1, 10); // HP maxHP ATK SPD CRIT
        pita.healFull();
        isWaveBuff[1] = true;
    }
    else if (pita.enemyKilled >= 50 && pita.enemyKilled <= 99 && isWaveBuff[0] == false) {
        wave = 2;
        hpMultiplier = 200;
        pita.buff(0, 50, 50, 1, 10); // HP maxHP ATK SPD CRIT
        pita.healFull();
        maxEnemy = 10;
        isWaveBuff[0] = true;
    }

    if (pita.hp <= 0) {
        isGameOver = 1; // Game Over
    }

    if (pita.enemyKilled >= 250) {
        isGameOver = 2; // Game Win
    }

    for (int i = 0; i < maxEnemy; i++) {
        if (Senate[i].enemyStatus == 0) {
            int x = (rand() % 700) + 50;
            int y = (rand() % 50);
            int hp = (rand() % 50) + hpMultiplier;
            int prob = rand() % 100;

            Senate[i].Init();
            Senate[i].Load(x, y, hp, prob);
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

    for (int i = 0; i < maxEnemy; i++) {
        pita.checkIfBulletHit(Senate[i].getSprite(), Senate[i].HP);
    }

    gui.Update(pita.hp, pita.atk, pita.spd, pita.critRate, pita.maxHP, pita.enemyKilled, wave);

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
    else if (isGameOver == 2) {
        window.clear(sf::Color::Black);
        isGameClose = 1;
        bgmMusic.stop();
        pita.enemyKilled = 250;
        GameWin win(800, 600, window, pita.enemyKilled);
    }
    else if (isGameOver == 1) {
        window.clear(sf::Color::Black);
        isGameClose = 1;
        bgmMusic.stop();
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
