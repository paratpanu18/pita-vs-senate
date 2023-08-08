#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    isGameClose = 0;

    pita.Load();
    slime.Load();

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
    pita.Update(slime.getPosition());
}

void Game::Draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(bgSprite);
    window.draw(pita.playerSprite);
    window.draw(slime.enemySprite);

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
