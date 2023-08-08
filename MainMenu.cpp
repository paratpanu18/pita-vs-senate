#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu(int height, int widgth, sf::RenderWindow& window)
{
	menuClose = 0;
	// Load font used in main menu
	if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
		std::cout << "!!! MainMenu font failed to load !!!" << std::endl;
	}
	else {
		std::cout << "MainMenu font loaded succesfully" << std::endl;
	}

	// Load background
	if (!bgTexture.loadFromFile("Assets/menuBackground.jpg")) {
		std::cout << "!!! MainMenu background failed to load !!!" << std::endl;
	}
	else {
		std::cout << "MainMenu background loaded succesfully" << std::endl;
		bg.setTexture(bgTexture);
	}

	// Play button
	menuButton[0].setFont(font);
	menuButton[0].setFillColor(sf::Color::White);
	menuButton[0].setOutlineColor(sf::Color(252, 107, 3));
	menuButton[0].setOutlineThickness(5);
	menuButton[0].setString("Play");
	menuButton[0].setCharacterSize(30);
	menuButton[0].setPosition(500, 300);


	// Option button
	menuButton[1].setFont(font);
	menuButton[1].setFillColor(sf::Color::White);
	menuButton[1].setOutlineColor(sf::Color::Blue);
	menuButton[1].setOutlineThickness(5);
	menuButton[1].setString("Scoreboard");
	menuButton[1].setCharacterSize(30);
	menuButton[1].setPosition(500, 350);

	// Exit button
	menuButton[2].setFont(font);
	menuButton[2].setFillColor(sf::Color::White);
	menuButton[2].setOutlineColor(sf::Color::Blue);
	menuButton[2].setOutlineThickness(5);
	menuButton[2].setString("Exit Game");
	menuButton[2].setCharacterSize(30);
	menuButton[2].setPosition(500, 400);

	//Credit
	credit.setFont(font);
	credit.setFillColor(sf::Color::White);
	credit.setString("Paratpanu Pechsaman | 66010542 | Programming Project KMITL");
	credit.setCharacterSize(16);
	credit.setPosition(30, 570);
	credit.setOutlineColor(sf::Color::Black);
	credit.setOutlineThickness(1);



	MainMenuSelected = 0;

	MainMenuLoop(window);
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	if (menuClose == 0) {
		window.draw(bg);
		window.draw(credit);
		for (int i = 0; i < 3; i++) {
			window.draw(menuButton[i]);
		}
	}
	
}

void MainMenu::moveUp()
{
	if (MainMenuSelected - 1 >= -1) {
		menuButton[MainMenuSelected].setOutlineColor(sf::Color::Blue);

		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		menuButton[MainMenuSelected].setOutlineColor(sf::Color(252, 107, 3));
	}
}

void MainMenu::moveDown()
{
	if (MainMenuSelected + 1 <= 3) {
		menuButton[MainMenuSelected].setOutlineColor(sf::Color::Blue);

		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 0;
		}
		menuButton[MainMenuSelected].setOutlineColor(sf::Color(252, 107, 3));
	}
}

void MainMenu::Update(sf::Event& event, sf::RenderWindow& window)
{
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyReleased) {
			// Move Up
			if ((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up)) {
				moveUp();
			}

			// Move Down
			if ((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down)) {
				moveDown();
			}

			// Enter
			if (event.key.code == sf::Keyboard::Return) {
				// Play
				if (MainMenuSelected == 0) {
					menuClose = 1;
					window.clear(sf::Color::Black);
					Game game(window);
				}
				
				// Option
				else if (MainMenuSelected == 1) {
					std::cout << "Options" << std::endl;
				}

				// Exit Game
				else if (MainMenuSelected == 2) {
					window.close();
				}
			}
		}
		
	}
	
}

void MainMenu::MainMenuLoop(sf::RenderWindow& window)
{
	while (window.isOpen() && menuClose == 0) {
		sf::Event event;
		Update(event, window);

		window.clear(sf::Color::Black);
		Draw(window);

		window.display();
	}
}
