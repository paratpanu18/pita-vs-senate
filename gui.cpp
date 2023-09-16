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

	hpBar.setSize(sf::Vector2f(1230, 10));
	hpBar.setOrigin(0, 0);
	hpBar.setPosition(25, 690);
	hpBar.setFillColor(sf::Color::Green);

	hpBarBG.setSize(sf::Vector2f(1230, 10));
	hpBarBG.setOrigin(0, 0);
	hpBarBG.setPosition(25, 690);
	hpBarBG.setFillColor(sf::Color(153, 151, 151));
	hpBarBG.setOutlineColor(sf::Color::White);
	hpBarBG.setOutlineThickness(2.5f);

	// HP
	hpIconTexture.loadFromFile("Assets/GUI/hp.png");
	hpIcon.setTexture(hpIconTexture);
	hpIcon.setScale(0.5f, 0.5f);
	hpIcon.setPosition(25, 620);

	HP.setFont(font);
	HP.setString("HP : ");
	HP.setCharacterSize(20);
	HP.setPosition(100, 650);
	HP.setFillColor(sf::Color::White);

	// ATK
	atkIconTexture.loadFromFile("Assets/GUI/atk.png");
	atkIcon.setTexture(atkIconTexture);
	atkIcon.setScale(0.5f, 0.5f);
	atkIcon.setPosition(325, 620);

	ATK.setFont(font);
	ATK.setString("ATK : ");
	ATK.setCharacterSize(20);
	ATK.setPosition(400, 650);
	ATK.setFillColor(sf::Color::White);

	// SPD
	spdIconTexture.loadFromFile("Assets/GUI/spd.png");
	spdIcon.setTexture(spdIconTexture);
	spdIcon.setScale(0.5f, 0.5f);
	spdIcon.setPosition(625, 620);

	SPD.setFont(font);
	SPD.setString("SPD : ");
	SPD.setCharacterSize(20);
	SPD.setPosition(700, 650);
	SPD.setFillColor(sf::Color::White);

	// CRIT
	critIconTexture.loadFromFile("Assets/GUI/crit.png");
	critIcon.setTexture(critIconTexture);
	critIcon.setScale(0.5f, 0.5f);
	critIcon.setPosition(925, 630);

	CRITRATE.setFont(font);
	CRITRATE.setString("Crit Rate : ");
	CRITRATE.setCharacterSize(20);
	CRITRATE.setPosition(990, 650);
	CRITRATE.setFillColor(sf::Color::White);

	senateKilled.setFont(font);
	senateKilled.setString("0");
	senateKilled.setCharacterSize(32);
	senateKilled.setFillColor(sf::Color(242, 120, 0));

	of250.setFont(font);
	of250.setString("of 250");
	of250.setCharacterSize(16);
	of250.setOrigin((of250.getGlobalBounds().width) / 2, 0);
	of250.setPosition(580, 60);
	of250.setFillColor(sf::Color::Black);

	waveDetail.setFont(font);
	waveDetail.setString("");
	waveDetail.setCharacterSize(9);
	waveDetail.setFillColor(sf::Color::Black);

	waveNumber.setFont(font);
	waveNumber.setString("Wave 1");
	waveNumber.setCharacterSize(24);
	waveNumber.setFillColor(sf::Color(242, 120, 0));

	antiStunSkillTexture.loadFromFile("Assets/GUI/antiStun.png");
	antiStunSkill.setTexture(antiStunSkillTexture);
	antiStunSkill.setOrigin(0, 50);
	antiStunSkill.setPosition(1200, 680);

	antiStunSkillCD.setOrigin(0, 50);
	antiStunSkillCD.setFillColor(sf::Color(0, 0, 0, 100));
	antiStunSkillCD.setSize(sf::Vector2f(50, 50));
	antiStunSkillCD.setPosition(1200, 680);

	// Popup Text
	popUpText.setFont(font);

	// Progreession GUI
	progressionGUITexture.loadFromFile("Assets/GUI/progressionGUI.png");
	progressionGUI.setTexture(progressionGUITexture);
	progressionGUI.setOrigin((progressionGUI.getGlobalBounds().width) / 2, 0);
	progressionGUI.setPosition(1280 / 2, 20);

}

void gui::Update(float hp, int atk, int spd, int critrate, float maxHP, int senateKilledAmout, int wave, float antiStunCD)
{
	// ------------- HP Bar -------------
	int hpINT = hp;
	int maxHPINT = maxHP;

	if (hp / maxHP >= 0.7f) hpBar.setFillColor(sf::Color::Green);
	else if (hp / maxHP > 0.4f) hpBar.setFillColor(sf::Color::Yellow);
	else if (hp / maxHP <= 0.4f) hpBar.setFillColor(sf::Color::Red);

	hpBar.setSize(sf::Vector2f((hp / maxHP) * 1230, 10));

	// ------------- HP Bar -------------

	// ------------- Status Bar -------------
	HP.setString(std::to_string(hpINT) + "/" + std::to_string(maxHPINT));

	ATK.setString(std::to_string(atk));

	SPD.setString(std::to_string(spd));

	CRITRATE.setString(std::to_string(critrate) + "%");
	// ------------- Status Bar -------------

	// ------------- Progress -------------
	senateKilled.setString(std::to_string(senateKilledAmout));
	senateKilled.setOrigin((senateKilled.getGlobalBounds().width) / 2, 0);
	senateKilled.setPosition(580, 20);
	switch (wave) {
		case 1: waveDetail.setString("HP : 100 - 150 | ATK : 3"); 	waveNumber.setString ("Wave 1"); break;
		case 2: waveDetail.setString("HP : 200 - 250 | ATK : 5");	waveNumber.setString ("Wave 2"); break;
		case 3: waveDetail.setString("HP : 300 - 350 | ATK : 7");	waveNumber.setString ("Wave 3"); break;
		case 4: waveDetail.setString("HP : 400 - 450 | ATK : 9");	waveNumber.setString ("Wave 4"); break;
		case 5: waveDetail.setString("HP : 500 - 550 | ATK : 10");	waveNumber.setString ("Wave 5"); break;
	}
	waveDetail.setOrigin((waveDetail.getGlobalBounds().width) / 2, 0);
	waveDetail.setPosition(675, 68);
	waveNumber.setOrigin((waveNumber.getGlobalBounds().width) / 2, 0);
	waveNumber.setPosition(675, 30);

	// ------------- Progress -------------

	// ------------ Anti Stun CD ----------
	if (antiStunCD <= 10) {
		this->antiStunSkillCD.setSize(sf::Vector2f(50.f, 50 - (antiStunCD/10.f) * 50.f));	
	}
	else {
		this->antiStunSkillCD.setSize(sf::Vector2f(50.f, 0));
	}
	// ------------ Anti Stun CD -----------

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

	window.draw(progressionGUI);
	window.draw(senateKilled); 
	window.draw(of250);
	window.draw(waveDetail);
	window.draw(waveNumber);

	window.draw(hpBarBG);
	window.draw(hpBar);

	window.draw(antiStunSkill);
	window.draw(antiStunSkillCD);

	if (clock.getElapsedTime().asSeconds() < (int)durationPtr) {
		window.draw(popUpText);
	}

}

void gui::showText(std::string text, sf::Color color, int fontSize, int x, int y, int outLineThickness, sf::Color outlineColor, int duration)
{
	durationPtr = duration;

	popUpText.setString(text);
	popUpText.setCharacterSize(fontSize);
	popUpText.setPosition(x, y);
	popUpText.setFillColor(color);
	popUpText.setOutlineColor(outlineColor);
	popUpText.setOutlineThickness(outLineThickness);


	clock.restart();
}
