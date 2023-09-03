#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    isGameClose = 0;

    pita.Load(100);

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        int x = (rand() % 700) + 50;
        int y = (rand() % 50);
        int hp = (rand() % 100) + 1;
        Senate[i].Load(x, y, hp);
    }

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

    for (int i = 0; i < 10; i++) {
        Senate[i].Update();
    }

    pita.Update(Senate[0].getSprite());
    gui.Update(pita.hp, pita.atk, pita.spd, pita.critRate, pita.maxHP, pita.enemyKilled);
}

void Game::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(bgSprite);
    pita.Draw(window);
    
    for (int i = 0; i < 10; i++) {
        Senate[i].Draw(window);
    }


    gui.Draw(window);

    window.display();


}

void Game::GameLoop(sf::RenderWindow& window)
{
    while (window.isOpen() && isGameClose == 0) {
        sf::Event event;

        Update(event, window);
        Draw(window);

    }
}
