#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "MainMenu.h"


sf::Image icon;

int WinMain() {

    icon.loadFromFile("Assets/bullet.png");

    // ------------- WINDOWS INIT ------------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pita vs. Senate - The battle of the past and the future", sf::Style::Close, settings);
    window.setFramerateLimit(30);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // ------------- WINDOWS INIT ------------------

    // Start game @ Main Menu
    MainMenu menu(window.getSize().x, window.getSize().y, window);
    
    return 0;
}