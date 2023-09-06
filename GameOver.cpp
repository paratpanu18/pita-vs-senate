#include "GameOver.h"

GameOver::GameOver(int widght, int height, sf::RenderWindow &window, int playerScore) {
    window.clear(sf::Color::Black);

    if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
        std::cout << "!!! GameOver font failed to load !!!" << std::endl;
    }
    else {
        std::cout << "GameOver font loaded succesfully" << std::endl;
    }

    yourScoreText.setFont(font);
    yourScoreText.setString("YOUR SCORE");
    yourScoreText.setFillColor(sf::Color::Yellow);
    yourScoreText.setCharacterSize(20);
    yourScoreText.setPosition(350, 10);

    playerScoreText.setFont(font);
    playerScoreText.setString(std::to_string(playerScore));
    playerScoreText.setFillColor(sf::Color::White);
    playerScoreText.setCharacterSize(35);
    playerScoreText.setPosition(390, 30);

    GameOverText.setFont(font);
    GameOverText.setString("Game Over !!");
    GameOverText.setFillColor(sf::Color::Red);
    GameOverText.setCharacterSize(90);
    GameOverText.setPosition(110, 200);

    EnterYourNameText.setFont(font);
    EnterYourNameText.setString("Enter your name (1 - 10 Char)\n[                                               ]");
    EnterYourNameText.setFillColor(sf::Color::White); 
    EnterYourNameText.setCharacterSize(20);
    EnterYourNameText.setPosition(250, 400);


    playerNameText.setFont(font);
    playerNameText.setString("");
    playerNameText.setFillColor(sf::Color::Yellow);
    playerNameText.setCharacterSize(15);
    playerNameText.setPosition(350, 435);

    GameOverLoop(window, playerScore);
}

void GameOver::Update(sf::Event& event, sf::RenderWindow& window, int playerScore)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b' && playerName.size() != 0 && event.text.unicode != '\r') {
                playerName.erase(playerName.size() - 1, 1);
            }
            else if (playerName.size() < 12 && event.text.unicode != '\r') { // Max player's name len is 12
                playerName += event.text.unicode;
            }
            playerNameText.setString(playerName);
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Return && playerName.size() != 0) {
                SaveHighScore(playerScore, playerName);
                MainMenu menu(800, 600, window);
            }
        }
    }
}

void GameOver::Draw(sf::RenderWindow& window)
{
    window.draw(yourScoreText);
    window.draw(playerScoreText);
    window.draw(GameOverText);
    window.draw(EnterYourNameText);
    window.draw(playerNameText);
}

void GameOver::GameOverLoop(sf::RenderWindow& window, int playerScore)
{
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        Update(event, window, playerScore);
        Draw(window);
        window.display();
    }
}

void GameOver::SaveHighScore(int playerScore, std::string playerName)
{
    // handle save score & playername to file
}
