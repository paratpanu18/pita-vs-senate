#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainMenu {
public:
	MainMenu(int, int, sf::RenderWindow&);

	sf::Texture bgTexture;
	sf::Sprite bg;

	void Draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void Update(sf::Event& event, sf::RenderWindow& window);

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	void MainMenuLoop(sf::RenderWindow& window);
	

private:
	int MainMenuSelected;
	int menuClose;
	sf::Font font;
	sf::Text menuButton[3];
	sf::Text credit;

	sf::Music bgMusic;
	sf::Music clickSFX;
};

