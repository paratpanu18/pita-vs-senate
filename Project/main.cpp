#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pita vs. Senate", sf::Style::Default, settings);
    window.setFramerateLimit(30);

    sf::CircleShape shape(150.0f);
    shape.setPosition(sf::Vector2f(200, 200));
    shape.setFillColor(sf::Color::Green);
    //shape.setRotation(45);
    size_t num = 100;

    std::cout << num;

    // game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }
    return 0;
}