#include "GameWin.h"
#include <fstream>

GameWin::GameWin(int widght, int height, sf::RenderWindow& window, int playerScore) {
    window.clear(sf::Color::Black);

    // Load Font
    if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
        std::cout << "!!! GameWin font failed to load !!!" << std::endl;
    }
    else {
        std::cout << "GameWin font loaded succesfully" << std::endl;
    }


    // Load background
    if (!bgTexture.loadFromFile("Assets/GameWinBG.png")) {
        std::cout << "!!! GameWin background failed to load !!!" << std::endl;
    }
    else {
        std::cout << "GameWin background loaded succesfully" << std::endl;
        bg.setTexture(bgTexture);
    }

    bgMusic.openFromFile("Assets/BGM/gamewinmusic.mp3");
    bgMusic.setLoop(true);

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

    EnterYourNameText.setFont(font);
    EnterYourNameText.setString("Enter the name of the PRIME MINISTER\n[                                                                 ]");
    EnterYourNameText.setFillColor(sf::Color::White);
    EnterYourNameText.setCharacterSize(20);
    EnterYourNameText.setPosition(200, 450);


    playerNameText.setFont(font);
    playerNameText.setString("");
    playerNameText.setFillColor(sf::Color::Yellow);
    playerNameText.setCharacterSize(15);
    playerNameText.setPosition(350, 485);

    enterText.setFont(font);
    enterText.setString("");
    enterText.setFillColor(sf::Color::Yellow);
    enterText.setCharacterSize(20);
    enterText.setPosition(270, 530);

    bgMusic.play();
    GameOverLoop(window, playerScore);
}

void GameWin::Update(sf::Event& event, sf::RenderWindow& window, int playerScore)
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
            else if (playerName.size() < 12 && event.text.unicode != '\r' && ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode == ' '))) { // Max player's name len is 12
                playerName += event.text.unicode;
            }
            playerNameText.setString(playerName);
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Return) {
                if (playerName.size() <= 0) {
                    enterText.setString("Please Enter Your Name");
                    enterText.setFillColor(sf::Color::Red);
                }
                else {
                    SaveHighScore(playerScore, playerName);
                    bgMusic.stop();
                    MainMenu menu(800, 600, window);
                }
            }
        }
    }
}

void GameWin::Draw(sf::RenderWindow& window)
{
    window.draw(bg);
    window.draw(yourScoreText);
    window.draw(playerScoreText);
    window.draw(EnterYourNameText);
    window.draw(playerNameText);
    if (playerName.size() > 0) {
        enterText.setString("Press [ENTER] to proceed");
        enterText.setFillColor(sf::Color::Yellow);
        enterText.setCharacterSize(20);
        //enterText.setPosition(270, 500);
    }
    window.draw(enterText);
}

void GameWin::GameOverLoop(sf::RenderWindow& window, int playerScore)
{
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        Update(event, window, playerScore);
        Draw(window);
        window.display();
    }
}

void GameWin::SaveHighScore(int playerScore, std::string playerName)
{
    // Define the filename to save the data
    std::string filename = "highscores.oakkun";

    // Open the file for writing (append mode)
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Write the player name and score to the file
    file << playerName << " (PRIME MINISTER)," << playerScore << "\n";

    // Close the file
    file.close();

    std::cout << "High score saved successfully." << std::endl;
}