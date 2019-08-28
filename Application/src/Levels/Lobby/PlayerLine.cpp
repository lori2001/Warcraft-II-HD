#include "PlayerLine.h"
#include "../Common/GameDetails.h"
#include <chrono>
#include <random>

void PlayerLine::setPosition(const sf::Vector2f& position) {
	nameInput.setPosition(position);

	raceDropdown.setPosition({
		nameInput.getPosition().x + nameInput.getGlobalBounds().width + 50, 95 });

	teamDropdown.setPosition({
		raceDropdown.getPosition().x + raceDropdown.getClosedGlobalBounds().width + 50, 95 });

	colorDropdown.setPosition({
		teamDropdown.getPosition().x + teamDropdown.getClosedGlobalBounds().width + 50, 95 });
}

void PlayerLine::setTheme(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	raceDropdown.setFont(font);
	raceDropdown.setSelectColor(themeColor);
	raceDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	raceDropdown.setCharacterSize(fontSize - 5);
	raceDropdown.setScale({ 0.65F, 0.85F });

	teamDropdown.setFont(font);
	teamDropdown.setSelectColor(themeColor);
	teamDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	teamDropdown.setCharacterSize(fontSize - 5);
	teamDropdown.setTextColor(themeColor);
	teamDropdown.setScale({ 0.65F, 0.85F });

	colorDropdown.setSelectColor(themeColor);
	colorDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	colorDropdown.setCharacterSize(fontSize - 5);
	colorDropdown.setScale({ 0.65F, 0.85F });
	colorDropdown.setHighlightColor(sf::Color(240, 230, 140, 180));

	nameInput.setCharacterSize(fontSize - 7);
	nameInput.setTextColor(themeColor);
	nameInput.setSelectColor(themeColor);
	nameInput.setFont(font);
}

void PlayerLine::setTextures(const sf::Texture& inputText, sf::Texture& dropdown)
{
	nameInput.setTexture(inputText);
	raceDropdown.setTexture(dropdown);
	teamDropdown.setTexture(dropdown);
	colorDropdown.setTexture(dropdown);
}

void PlayerLine::setupStrings(const std::vector<ColoredString>& races, 
							  const std::vector<std::string>& teams, 
							  const std::vector<sf::Color>& colors)
{							
	raceDropdown.setDropString(0, races[0].name);
	raceDropdown.setDropTextColor(0, races[0].color);
	for (int i = 0; i < int(races.size()); i++) {
		raceDropdown.addDropString(races[i].name);
		raceDropdown.setDropTextColor(i + 1, races[i].color);
	}
	teamDropdown.setDropString(0, teams[0]);
	for (int i = 0; i < int(teams.size()); i++) {
		teamDropdown.addDropString(teams[i]);
	}
	colorDropdown.setDropColor(0, colors[0]);
	for (int i = 0; i < int(colors.size()); i++) {
		colorDropdown.addDropColor(colors[i]);
	}
}

void PlayerLine::addToPlayers(const std::vector<ColoredString>& races,
							   const std::vector<std::string>& teams,
							   const std::vector<sf::Color>& colors)
{
	GameDetails::players.push_back(Player{});
	int i =  GameDetails::players.size() - 1;

	GameDetails::players[i].title_ =  nameInput.getString();
	GameDetails::players[i].difficulty_ = Player::Difficulty::User;

	if (raceDropdown.getDropString(0) == races[0].name) { // Race
		int seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());
		std::minstd_rand0 generator(seed);

		if (generator() % 2)
			GameDetails::players[i].race_ = Player::Race::Orcs;
		else
			GameDetails::players[i].race_ = Player::Race::Humans;
	}
	else if (raceDropdown.getDropString(0) == races[1].name) {
		GameDetails::players[i].race_ = Player::Race::Orcs;
	}
	else if (raceDropdown.getDropString(0) == races[2].name) {
		GameDetails::players[i].race_ = Player::Race::Humans;
	}
	else {
		NG_LOG_ERROR("Error setting up player race! race ",
			raceDropdown.getDropString(0), "does not exist!");
	}

	for (int j = 0; j < int(teams.size()); j++) { // Team
		if (teamDropdown.getDropString(0) == teams[j]) {
			GameDetails::players[i].team_ = static_cast<Player::Team>(j);
			break;
		}
	}

	for (int j = 0; j < int(colors.size()); j++) { // Color
		if (colorDropdown.getDropColor(0) == colors[j]) {
			GameDetails::players[i].color_ = colors[j];
			break;
		}
	}
}

void PlayerLine::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	nameInput.handleEvents(event, mouse);
	raceDropdown.handleEvents(event, mouse);
	teamDropdown.handleEvents(event, mouse);
	colorDropdown.handleEvents(event, mouse);
}

void PlayerLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nameInput);
	target.draw(raceDropdown);
	target.draw(teamDropdown);
	target.draw(colorDropdown);
}



