#include "MainMenu.h"
#include "Game.h"
#include "HighScore.h"
#include "GameWin.h"

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
	if (!bgTexture.loadFromFile("Assets/menuBackground2.png")) {
		std::cout << "!!! MainMenu background failed to load !!!" << std::endl;
	}
	else {
		std::cout << "MainMenu background loaded succesfully" << std::endl;
		bg.setTexture(bgTexture);
	}

	bgMusic.openFromFile("Assets/BGM/menuBGM.mp3");
	bgMusic.setLoop(true);

	clickSFX.openFromFile("Assets/SFX/menuClick.mp3");

	// Play button
	menuButton[0].setFont(font);
	menuButton[0].setFillColor(sf::Color(242, 120, 0));
	menuButton[0].setString("Play");
	menuButton[0].setCharacterSize(25);
	menuButton[0].setOrigin((menuButton[0].getGlobalBounds().width)/2, 0);
	menuButton[0].setPosition(window.getSize().x / 2, window.getSize().y * 0.55f);


	// Option button
	menuButton[1].setFont(font);
	menuButton[1].setFillColor(sf::Color::White);
	menuButton[1].setString("Scoreboard");
	menuButton[1].setCharacterSize(25);
	menuButton[1].setOrigin((menuButton[1].getGlobalBounds().width) / 2, 0);
	menuButton[1].setPosition(window.getSize().x / 2, window.getSize().y * 0.65f);

	// Exit button
	menuButton[2].setFont(font);
	menuButton[2].setFillColor(sf::Color::White);
	menuButton[2].setString("Exit Game");
	menuButton[2].setCharacterSize(25);
	menuButton[2].setOrigin((menuButton[2].getGlobalBounds().width) / 2, 0);
	menuButton[2].setPosition(window.getSize().x / 2, window.getSize().y * 0.75f);

	//Credit
	credit.setFont(font);
	credit.setFillColor(sf::Color::White);
	credit.setString("Paratpanu Pechsaman | 66010542 | Programming Fundamental KMITL");
	credit.setCharacterSize(18);
	credit.setOrigin((credit.getGlobalBounds().width) / 2, 0);
	credit.setPosition(window.getSize().x / 2, window.getSize().y * 0.95f);
	credit.setOutlineColor(sf::Color::Black);
	credit.setOutlineThickness(1);



	MainMenuSelected = 0;

	bgMusic.play();
	bgMusic.setPlayingOffset(sf::seconds(35.0f)); 
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
		//menuButton[MainMenuSelected].setOutlineColor(sf::Color::Blue);
		menuButton[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected--;
		if (MainMenuSelected == -1) {
			MainMenuSelected = 2;
		}
		//menuButton[MainMenuSelected].setOutlineColor(sf::Color(252, 107, 3));
		menuButton[MainMenuSelected].setFillColor(sf::Color(242, 120, 0));
	}
	clickSFX.play();
}

void MainMenu::moveDown()
{
	if (MainMenuSelected + 1 <= 3) {
		//menuButton[MainMenuSelected].setOutlineColor(sf::Color::Blue);
		menuButton[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected++;
		if (MainMenuSelected == 3) {
			MainMenuSelected = 0;
		}
		//menuButton[MainMenuSelected].setOutlineColor(sf::Color(252, 107, 3));
		menuButton[MainMenuSelected].setFillColor(sf::Color(242, 120, 0));
	}

	clickSFX.play();
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

			// Cheat
			if ((event.key.code == sf::Keyboard::C)) {
				window.clear(sf::Color::Black);
				bgMusic.stop();
				GameWin win(800, 600, window, 250);
			}
			

			// Enter
			if (event.key.code == sf::Keyboard::Return) {
				// Play
				if (MainMenuSelected == 0) {
					menuClose = 1;
					window.clear(sf::Color::Black);
					bgMusic.stop();
					Game game(window);
				}
				
				// HighScore
				else if (MainMenuSelected == 1) {
					window.clear(sf::Color::Black);
					bgMusic.stop();
					HighScore scoreboard(window);
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
