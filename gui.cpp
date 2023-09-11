#include "gui.h"

#include <iostream>

void gui::Init()
{
	if (!font.loadFromFile("Assets/Font/Anakotmai-Medium.otf")) {
		std::cout << "!!! GUI font failed to load !!!" << std::endl;
	}
	else {
		std::cout << "GUI font loaded succesfully" << std::endl;
	}

	hpBar.setSize(sf::Vector2f(750, 5));
	hpBar.setOrigin(0, 0);
	hpBar.setPosition(25, 570);
	hpBar.setFillColor(sf::Color::Green);

	hpBarBG.setSize(sf::Vector2f(750, 5));
	hpBarBG.setOrigin(0, 0);
	hpBarBG.setPosition(25, 570);
	hpBarBG.setFillColor(sf::Color(153, 151, 151));
	hpBarBG.setOutlineColor(sf::Color::White);
	hpBarBG.setOutlineThickness(2.5f);

	// HP
	hpIconTexture.loadFromFile("Assets/GUI/hp.png");
	hpIcon.setTexture(hpIconTexture);
	hpIcon.setScale(0.4f, 0.4f);
	hpIcon.setPosition(25, 520);

	HP.setFont(font);
	HP.setString("HP : ");
	HP.setCharacterSize(14);
	HP.setPosition(80, 540);
	HP.setFillColor(sf::Color::White);

	// ATK
	atkIconTexture.loadFromFile("Assets/GUI/atk.png");
	atkIcon.setTexture(atkIconTexture);
	atkIcon.setScale(0.4f, 0.4f);
	atkIcon.setPosition(225, 520);

	ATK.setFont(font);
	ATK.setString("ATK : ");
	ATK.setCharacterSize(14);
	ATK.setPosition(280, 540);
	ATK.setFillColor(sf::Color::White);

	// SPD
	spdIconTexture.loadFromFile("Assets/GUI/spd.png");
	spdIcon.setTexture(spdIconTexture);
	spdIcon.setScale(0.4f, 0.4f);
	spdIcon.setPosition(390, 520);

	SPD.setFont(font);
	SPD.setString("SPD : ");
	SPD.setCharacterSize(14);
	SPD.setPosition(445, 540);
	SPD.setFillColor(sf::Color::White);

	// CRIT
	critIconTexture.loadFromFile("Assets/GUI/crit.png");
	critIcon.setTexture(critIconTexture);
	critIcon.setScale(0.4f, 0.4f);
	critIcon.setPosition(570, 525);

	CRITRATE.setFont(font);
	CRITRATE.setString("Crit Rate : ");
	CRITRATE.setCharacterSize(14);
	CRITRATE.setPosition(625, 540);
	CRITRATE.setFillColor(sf::Color::White);

	senateKilled.setFont(font);
	senateKilled.setString("0 / 250");
	senateKilled.setCharacterSize(30);
	senateKilled.setPosition(650, 10);
	senateKilled.setFillColor(sf::Color::Yellow);

	waveDetail.setFont(font);
	waveDetail.setString(" ");
	waveDetail.setCharacterSize(12);
	waveDetail.setPosition(650, 60);
	waveDetail.setFillColor(sf::Color::White);

	// Pop up Text
	popUpText.setFont(font);
	popUpText.setOutlineColor(sf::Color::White);
	popUpText.setOutlineThickness(3);
}

void gui::Update(float hp, int atk, int spd, int critrate, float maxHP, int senateKilledAmout, int wave)
{
	// ------------- HP Bar -------------
	int hpINT = hp;
	int maxHPINT = maxHP;

	if (hp / maxHP >= 0.7f) hpBar.setFillColor(sf::Color::Green);
	else if (hp / maxHP > 0.4f) hpBar.setFillColor(sf::Color::Yellow);
	else if (hp / maxHP <= 0.4f) hpBar.setFillColor(sf::Color::Red);

	hpBar.setSize(sf::Vector2f((hp / maxHP) * 750, 5));

	// ------------- HP Bar -------------

	// ------------- Status Bar -------------
	HP.setString(std::to_string(hpINT) + "/" + std::to_string(maxHPINT));

	ATK.setString(std::to_string(atk));

	SPD.setString(std::to_string(spd));

	CRITRATE.setString(std::to_string(critrate) + "%");
	// ------------- Status Bar -------------

	// ------------- Progress -------------
	senateKilled.setString(std::to_string(senateKilledAmout) + " / 250");
	switch (wave) {
		case 1: waveDetail.setString("    -- Wave 1 of 5 --\nMax Senate : 5\nSenate HP : 100 - 150\nSenate ATK : 3"); 	break;
		case 2: waveDetail.setString("    -- Wave 2 of 5 --\nMax Senate : 10\nSenate HP : 200 - 250\nSenate ATK : 5");	break;
		case 3: waveDetail.setString("    -- Wave 3 of 5 --\nMax Senate : 13\nSenate HP : 300 - 350\nSenate ATK : 7");	break;
		case 4: waveDetail.setString("    -- Wave 4 of 5 --\nMax Senate : 15\nSenate HP : 400 - 450\nSenate ATK : 9");	break;
		case 5: waveDetail.setString("    -- Wave 5 of 5 --\nMax Senate : 20\nSenate HP : 500 - 550\nSenate ATK : 10");	break;
	}

	// ------------- Progress -------------
}

void gui::Draw(sf::RenderWindow& window)
{
	window.draw(hpIcon);
	window.draw(HP);

	window.draw(atkIcon);
	window.draw(ATK);

	window.draw(spdIcon);
	window.draw(SPD);

	window.draw(critIcon);
	window.draw(CRITRATE);

	window.draw(senateKilled); 
	window.draw(waveDetail);

	window.draw(hpBarBG);
	window.draw(hpBar);

	if (clock.getElapsedTime().asSeconds() < 5) {
		window.draw(popUpText);
	}
}

void gui::showText(std::string text, sf::Color color, int fontSize, int x, int y)
{
	popUpText.setString(text);
	popUpText.setCharacterSize(fontSize);
	popUpText.setPosition(x, y);
	popUpText.setFillColor(color);

	clock.restart();
}
