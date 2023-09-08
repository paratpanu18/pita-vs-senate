#include "HighScore.h"
#include <algorithm>

HighScore::HighScore(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // Load Font
    if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
        std::cout << "!!! HighScore font failed to load !!!" << std::endl;
    }
    else {
        std::cout << "HighScore font loaded succesfully" << std::endl;
    }

    // Load background
    if (!bgTexture.loadFromFile("Assets/HighScoreBG.png")) {
        std::cout << "!!! High Score background failed to load !!!" << std::endl;
    }
    else {
        std::cout << "High Score background loaded succesfully" << std::endl;
        bg.setTexture(bgTexture);
    }

   highScoreText.setFont(font);
   highScoreText.setString("SCOREBOARD");
   highScoreText.setFillColor(sf::Color::Yellow);
   highScoreText.setCharacterSize(50);
   highScoreText.setPosition(220, 50);

   std::vector<HighScoreEntry> highScores = LoadHighScores("highscores.oakkun");
   
       for (int i = 0; i < 5 && i < highScores.size(); i++) {
           HighScorePlayerName[i].setFont(font);
           HighScorePlayerName[i].setString(std::to_string(i+1) + " - " + highScores[i].playerName);
           HighScorePlayerName[i].setFillColor(sf::Color::White);
           HighScorePlayerName[i].setCharacterSize(20);
           HighScorePlayerName[i].setPosition(150, (i + 1) * 50 + 100);

           HighScorePlayer[i].setFont(font);
           HighScorePlayer[i].setString("[ " + std::to_string(highScores[i].score) + " ]");
           HighScorePlayer[i].setFillColor(sf::Color::White);
           HighScorePlayer[i].setCharacterSize(20);
           HighScorePlayer[i].setPosition(600, (i + 1) * 50 + 100);
       }



   HighScoreLoop(window);
}

void HighScore::Update(sf::Event& event, sf::RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                MainMenu menu(800, 600, window);
            }

        }
    }
}

void HighScore::Draw(sf::RenderWindow& window)
{
    window.draw(bg);
    window.draw(highScoreText);
    for (int i = 0; i < 5; i++) {
        window.draw(HighScorePlayerName[i]);
        window.draw(HighScorePlayer[i]);
    }
}

void HighScore::HighScoreLoop(sf::RenderWindow& window)
{
    while (window.isOpen()) {
        sf::Event event;
        window.clear();
        Update(event, window);
        Draw(window);
        window.display();
    }
}

std::vector<HighScore::HighScoreEntry> HighScore::LoadHighScores(const std::string& filename)
{
    std::vector<HighScore::HighScoreEntry> highScores;
    // Open the file for reading
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Split the line into playerName and score
        std::istringstream iss(line);
        std::string playerName;
        int score;

        if (std::getline(iss, playerName, ',') && iss >> score) {
            highScores.push_back({ playerName, score });
        }
    }

    // Close the file
    file.close();

    // Sort the high scores in descending order
    std::sort(highScores.begin(), highScores.end());

    // Get the top five scores
    std::vector<HighScore::HighScoreEntry> topFive;
    if (highScores.size() >= 5) {
        topFive.assign(highScores.begin(), highScores.begin() + 5);
    }
    else {
        topFive = highScores;
    }

    return topFive;

}