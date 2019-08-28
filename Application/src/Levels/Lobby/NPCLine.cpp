#include "NPCLine.h"
#include "../Common/GameDetails.h"
#include <chrono>
#include <random>

void NPCLine::setPosition(const sf::Vector2f& position)
{
	difficultyDropdown.setPosition(position);

	raceDropdown.setPosition(
		{ difficultyDropdown.getPosition().x + difficultyDropdown.getClosedGlobalBounds().width + 50,
		  difficultyDropdown.getPosition().y });

	teamDropdown.setPosition(
		{ raceDropdown.getPosition().x + raceDropdown.getClosedGlobalBounds().width + 50,
		  raceDropdown.getPosition().y });

	colorDropdown.setPosition(
		{ teamDropdown.getPosition().x + teamDropdown.getClosedGlobalBounds().width + 50,
		  teamDropdown.getPosition().y });
}

void NPCLine::setTheme(const sf::Font& font, const unsigned fontSize,
	const sf::Color& themeColor, const sf::Vector2f& scale)
{
	raceDropdown.setFont(font);
	raceDropdown.setSelectColor(themeColor);
	raceDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	raceDropdown.setCharacterSize(fontSize - 8);
	raceDropdown.setScale(scale);

	difficultyDropdown.setFont(font);
	difficultyDropdown.setSelectColor(themeColor);
	difficultyDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	difficultyDropdown.setCharacterSize(fontSize - 8);
	difficultyDropdown.setTextColor(themeColor);
	difficultyDropdown.setScale(scale);

	teamDropdown.setFont(font);
	teamDropdown.setSelectColor(themeColor);
	teamDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	teamDropdown.setCharacterSize(fontSize - 8);
	teamDropdown.setTextColor(themeColor);
	teamDropdown.setScale(scale);

	colorDropdown.setSelectColor(themeColor);
	colorDropdown.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	colorDropdown.setCharacterSize(fontSize - 8);
	colorDropdown.setScale(scale);
	colorDropdown.setHighlightColor(sf::Color(240, 230, 140, 180));
}

void NPCLine::setTexture(sf::Texture& dropdown)
{
	raceDropdown.setTexture(dropdown);
	difficultyDropdown.setTexture(dropdown);
	teamDropdown.setTexture(dropdown);
	colorDropdown.setTexture(dropdown);
}

void NPCLine::setupStrings(const std::vector<ColoredString>& races,
	const std::vector<std::string>& teams,
	const std::vector<sf::Color>& colors,
	const std::vector<std::string>& difficulties)
{
	raceDropdown.setDropString(0, races[0].name);
	raceDropdown.setDropTextColor(0, races[0].color);

	for (int j = 0; j < int(races.size()); j++) {
		raceDropdown.addDropString(races[j].name);
		raceDropdown.setDropTextColor(j + 1, races[j].color);
	}

	difficultyDropdown.setDropString(0, difficulties[0]);

	for (int j = 0; j < int(difficulties.size()); j++) {
		difficultyDropdown.addDropString(difficulties[j]);
	}

	teamDropdown.setDropString(0, teams[0]);

	for (int j = 0; j < int(teams.size()); j++) {
		teamDropdown.addDropString(teams[j]);
	}

	colorDropdown.setDropColor(0, colors[0]);

	for (int j = 0; j < int(colors.size()); j++) {
		colorDropdown.addDropColor(colors[j]);
	}
}

void NPCLine::addToPlayers(const std::vector<ColoredString>& races,
	const std::vector<std::string>& teams,
	const std::vector<sf::Color>& colors,
	const std::vector<std::string>& difficulties)
{
	GameDetails::players.push_back(Player{});
	int i = GameDetails::players.size() - 1;

	GameDetails::players[i].title_ = "NPC";

	// Race
	if (raceDropdown.getDropString(0) == races[0].name) {
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
		NG_LOG_ERROR("Error setting up npc (", i, ") race! race ",
			raceDropdown.getDropString(0), "does not exist!");
	}

	// Team
	for (int j = 0; j < int(teams.size()); j++) {
		if (teamDropdown.getDropString(0) == teams[j]) {
			GameDetails::players[i].team_ = static_cast<Player::Team>(j);
			break;
		}
	}

	// Color
	for (int j = 0; j < int(colors.size()); j++) {
		if (colorDropdown.getDropColor(0) == colors[j]) {
			GameDetails::players[i].color_ = colors[j];
		}
	}

	// Difficulty
	for (int j = 0; j < int(difficulties.size()); j++) {
		if (difficultyDropdown.getDropString(0) == difficulties[j]) {
			GameDetails::players[i].difficulty_ = static_cast<Player::Difficulty>(j);
			break;
		}
	}
}

void NPCLine::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	difficultyDropdown.handleEvents(event, mouse);
	raceDropdown.handleEvents(event, mouse);
	teamDropdown.handleEvents(event, mouse);
	colorDropdown.handleEvents(event, mouse);
}

void NPCLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(difficultyDropdown);
	target.draw(raceDropdown);
	target.draw(teamDropdown);
	target.draw(colorDropdown);
}
