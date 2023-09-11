#include "endCredit.h"

endCredit::endCredit(sf::RenderWindow& window, sf::Music& bgm)
{
    // Load Font
    if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
        std::cout << "!!! Credit font failed to load !!!" << std::endl;
    }
    else {
        std::cout << "Credit font loaded succesfully" << std::endl;
    }

    bgTexture.loadFromFile("Assets/creditBG.png");
    bg.setTexture(bgTexture);

    role.setFont(font);
    role.setCharacterSize(16);
    role.setString("Thanks for playing !\n\n\n\nHead Game Developer\n\n\n\nGame Programmer\n\n\n\nBug Fixer\n\n\n\nGame Tester\n\n\n\n\n\nGame Graphics & GUI designer\n\n\n\nExternal Code Contributer\n\n\n\n\n\n\nGraphics\n\n\n\n\nMusic & Sound\n\n\n\n\n\n\nBefore the game really end...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPita VS Senate by...");
    role.setFillColor(sf::Color::Yellow);

    credit.setFont(font);
    credit.setCharacterSize(16);
    credit.setString("I am really appreciated, and hope this project got A\n\n\n\nParatpanu Pechsaman\n\n\n\nParatpanu Pechsaman\n\n\n\nParatpanu Pechsaman\n\n\n\nParatpanu Pechsaman\nPearapat Kumsing\nPipatpong Pnapruake\n\n\n\nParatpanu Pechsaman\n\n\n\nChatGPT 3.5\nGitHub Copilot\nStackOverFlow\nGitHub\n\n\n\nitch.io/game-assets/ (Use for educational purpose)\nHonkai StarRail - Status Icon GUI\n\n\n\nToby Fox - Hope and Dream (Undertale OST)\nHoyomix - Fontaine Battle Theme 2\nThanathorn Juangroongruangkit - 'Thoong Fun Wan Mai'\nPrayuth Chan-o-cha - 'Give happiness back to people'\n\n\n\nI'd like to say 'Thank you' to all the coffee I drank,\nAll the friends who help me on this project (Even they know or not).\n\nLastly... I hope Thailand's political situation goes better than today,\nAnd hope that one day... We'll have something really called 'Democracy'\n\n\n\n\n\n\n\n\n\n\n\nParatpanu Pechsaman\nStudent ID: 66010542\nComputer Engineering (CE62), KMITL.");
    credit.setFillColor(sf::Color::White);

    creditTitle.setFont(font);
    creditTitle.setCharacterSize(48);
    creditTitle.setString("Pita VS Senate");
    creditTitle.setFillColor(sf::Color::Yellow);

    pleaseProceed.setFont(font);
    pleaseProceed.setCharacterSize(18);
    pleaseProceed.setString("Press [ENTER] to proceed");
    pleaseProceed.setFillColor(sf::Color::Yellow);
    pleaseProceed.setPosition(50, 550);


    // Set the initial position of the text
    sf::Vector2f titleTextPosition(50, window.getSize().y);
    sf::Vector2f roleTextPosition(50, window.getSize().y + 130);
    sf::Vector2f textPosition(50, window.getSize().y + 160);

    // Scroll speed in pixels per second
    float scrollSpeed = 35.0f;

    sf::Clock clock;
    bool creditsFinished = false; // Flag to track when credits finish

    while (window.isOpen() && !creditsFinished) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Calculate elapsed time since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the text's position to create scrolling effect
        textPosition.y -= scrollSpeed * deltaTime;
        roleTextPosition.y -= scrollSpeed * deltaTime;
        titleTextPosition.y -= scrollSpeed * deltaTime;

        // If the text has scrolled off the screen, set the flag to true
        if (textPosition.y + credit.getGlobalBounds().height < 350) {
            creditsFinished = true;
        }

        credit.setPosition(textPosition);
        role.setPosition(roleTextPosition);
        creditTitle.setPosition(titleTextPosition);

        window.clear();
        window.draw(bg);
        window.draw(creditTitle);
        window.draw(credit);
        window.draw(role);
        window.display();
    }

    // Credit Finish
    window.draw(pleaseProceed);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape) {
                    bgm.stop();
                    MainMenu menu(800, 600, window);
                }
            }
        }
    }
}
