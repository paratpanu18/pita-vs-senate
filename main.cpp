#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "MainMenu.h"


sf::Image icon;

int WinMain() {

    icon.loadFromFile("Assets/icon.png");

    // ------------- WINDOWS INIT ------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pita vs. Senate - The battle of the past and the future", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // ------------- WINDOWS INIT ------------------

    window.setMouseCursorVisible(false);


    // Start game @ Main Menu
    MainMenu menu(window.getSize().x, window.getSize().y, window);
    
    return 0;
}