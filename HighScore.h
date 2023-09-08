#pragma once
#include "MainMenu.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>
#include <vector>

class HighScore {
public:
	struct HighScoreEntry {
		std::string playerName;
		int score;

		// Define a comparison operator for sorting
		bool operator<(const HighScoreEntry& other) const {
			return score > other.score; // Sort in descending order
		}
	};
	
	std::vector<HighScoreEntry> highScores;

	HighScore(sf::RenderWindow& window);
	void Update(sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void HighScoreLoop(sf::RenderWindow& window);
	std::vector<HighScoreEntry> LoadHighScores(const std::string &filename);

	sf::Text HighScorePlayerName[5];
	sf::Text HighScorePlayer[5];
	
	sf::Font font;
	sf::Text highScoreText;

	sf::Texture bgTexture;
	sf::Sprite bg;
};