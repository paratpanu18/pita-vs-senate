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

	hpBar.setSize(sf::Vector2f(800, 20));
	hpBar.setOrigin(0, 0);
	hpBar.setPosition(0, 580);
	hpBar.setFillColor(sf::Color::Green);

	hpBarBG.setSize(sf::Vector2f(800, 20));
	hpBarBG.setOrigin(0, 0);
	hpBarBG.setPosition(0, 580);
	hpBarBG.setFillColor(sf::Color(153, 151, 151));

	HP.setFont(font);
	HP.setString("HP : ");
	HP.setCharacterSize(14);
	HP.setPosition(10, 560);
	HP.setFillColor(sf::Color::Black);

	ATK.setFont(font);
	ATK.setString("ATK : ");
	ATK.setCharacterSize(14);
	ATK.setPosition(150, 560);
	ATK.setFillColor(sf::Color::Black);

	SPD.setFont(font);
	SPD.setString("SPD : ");
	SPD.setCharacterSize(14);
	SPD.setPosition(290, 560);
	SPD.setFillColor(sf::Color::Black);

	CRITRATE.setFont(font);
	CRITRATE.setString("Crit Rate : ");
	CRITRATE.setCharacterSize(14);
	CRITRATE.setPosition(430, 560);
	CRITRATE.setFillColor(sf::Color::Black);

	senateKilled.setFont(font);
	senateKilled.setString("0 / 250");
	senateKilled.setCharacterSize(30);
	senateKilled.setPosition(650, 10);
	senateKilled.setFillColor(sf::Color::White);

	waveDetail.setFont(font);
	waveDetail.setString(" ");
	waveDetail.setCharacterSize(12);
	waveDetail.setPosition(650, 60);
	waveDetail.setFillColor(sf::Color::White);
}

void gui::Update(float hp, int atk, int spd, int critrate, float maxHP, int senateKilledAmout, int wave)
{
	// ------------- HP Bar -------------
	int hpINT = hp;
	int maxHPINT = maxHP;

	if (hp / maxHP >= 0.7f) hpBar.setFillColor(sf::Color::Green);
	else if (hp / maxHP > 0.4f) hpBar.setFillColor(sf::Color::Yellow);
	else if (hp / maxHP <= 0.4f) hpBar.setFillColor(sf::Color::Red);

	hpBar.setSize(sf::Vector2f((hp / maxHP) * 800, 20));

	// ------------- HP Bar -------------

	// ------------- Status Bar -------------
	HP.setString("HP : " + std::to_string(hpINT) + "/" + std::to_string(maxHPINT));

	ATK.setString("ATK : " + std::to_string(atk));

	SPD.setString("SPD : " + std::to_string(spd));

	CRITRATE.setString("Crit Rate : " + std::to_string(critrate) + "%");
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
	window.draw(HP);
	window.draw(ATK);
	window.draw(SPD);
	window.draw(CRITRATE);
	window.draw(senateKilled); 
	window.draw(waveDetail);

	window.draw(hpBarBG);
	window.draw(hpBar);

}
