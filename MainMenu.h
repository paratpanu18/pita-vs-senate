#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class MainMenu {
public:
	
	MainMenu(int heigh, int widgth, sf::RenderWindow& window);

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


};

