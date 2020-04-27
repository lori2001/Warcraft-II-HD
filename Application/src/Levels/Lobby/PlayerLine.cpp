#include "PlayerLine.h"
#include <chrono>
#include <random>

PlayerLine::PlayerLine(const sf::Vector2f& position)
{
	// --- Setup strings -------------------
	nameInput_.setString(GameDetailsFile::getPlayerName());
	nameText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });

	bool found = false;
	for(auto &it: races_)
		if (it.string == GameDetailsFile::getPlayerRace()) {
			raceDropdown_.setDropString(0, it.string);
			raceDropdown_.setDropTextColor(0, it.color);
			found = true;
			break;
		}

	if (!found) NG_LOG_ERROR("Error setting player race! Race in file does not exist!");

	for (int i = 0; i < int(races_.size()); i++) {
		raceDropdown_.addDropString(races_[i].string);
		raceDropdown_.setDropTextColor(i + 1, races_[i].color);
	}
	teamDropdown_.setDropString(0, GameDetailsFile::getPlayerTeam());
	for (int i = 0; i < int(teams_.size()); i++) {
		teamDropdown_.addDropString(teams_[i]);
	}
	colorDropdown_.setDropColor(0, sf::Color{ GameDetailsFile::getPlayerColor() });
	for (int i = 0; i < int(colors_.size()); i++) {
		colorDropdown_.addDropColor(colors_[i]);
	}
	// -------------------------------------

	setPosition(position);
}

void PlayerLine::setPosition(const sf::Vector2f& position)
{
	nameInput_.setPosition(position);

	ng::centerTextInBounds(nameText_, nameInput_.getGlobalBounds(), nameTextOffset_);

	raceDropdown_.setPosition({
		nameInput_.getPosition().x + nameInput_.getGlobalBounds().width + 50, 95 });

	teamDropdown_.setPosition({
		raceDropdown_.getPosition().x + raceDropdown_.getClosedGlobalBounds().width + 50, 95 });

	colorDropdown_.setPosition({
		teamDropdown_.getPosition().x + teamDropdown_.getClosedGlobalBounds().width + 50, 95 });
}

void PlayerLine::correctForRelativeColor()
{
	if (GameDetailsFile::getTeamRelativeColors()) {
		colorDropdown_.setDisabled(true);
		// search for an index number
		auto teamIndex =
			std::find(GameDetailsFile::teams_.begin(),
				GameDetailsFile::teams_.end(),
				teamDropdown_.getDropString(0));

		int teamIndexInt = std::distance(GameDetailsFile::teams_.begin(), teamIndex);
		GameDetailsFile::setPlayerColor(GameDetailsFile::colors_[teamIndexInt].toInteger());
		colorDropdown_.setDropColor(0, sf::Color{ GameDetailsFile::getPlayerColor() });
	}
}

void PlayerLine::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	nameInput_.handleEvents(event, mouse);
	raceDropdown_.handleEvents(event, mouse);
	teamDropdown_.handleEvents(event, mouse);
	colorDropdown_.handleEvents(event, mouse);

	if (nameInput_.getIsActive())
		GameDetailsFile::setPlayerName(nameInput_.getString());

	if (raceDropdown_.hasChanged())
	{
		GameDetailsFile::setPlayerRace(raceDropdown_.getDropString(0));
	}
	else if (teamDropdown_.hasChanged())
	{
		const std::string teamBefore = GameDetailsFile::getPlayerTeam();
		GameDetailsFile::setPlayerTeam(teamDropdown_.getDropString(0));

		// set only if there are at least two active teams
		bool atLeastTwo = false;
		for (int i = 0; i < GameDetailsFile::getNumberOfNPCs(); i++) {
			if (getNPCTeam(i) != getPlayerTeam())
			{
				atLeastTwo = true;
				break;
			}
		}

		if (!atLeastTwo) // set the team back
		{
			GameDetailsFile::setPlayerTeam(teamBefore);
			teamDropdown_.setDropString(0, teamBefore);
		}

		correctForRelativeColor();
	}
	else if (colorDropdown_.hasChanged())
	{
		// if colors are not relative to the team
		if (!GameDetailsFile::getTeamRelativeColors()) {
			const unsigned oldColor = GameDetailsFile::getPlayerColor();
			const unsigned newColor = colorDropdown_.getDropColor(0).toInteger();

			// see if the new color has been already used

			bool alreadyUsed = false;
			for (int i = 0; i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()); i++)
			{
				if (newColor == getNPCColor(i))
				{
					alreadyUsed = true;
					break;
				}
			}

			if (alreadyUsed) // if already used then revert to the one before
				colorDropdown_.setDropColor(0, sf::Color{ oldColor });
			else // if not used just use the new one
				GameDetailsFile::setPlayerColor(newColor);
		}
	}
}

void PlayerLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nameInput_);
	target.draw(raceDropdown_);
	target.draw(teamDropdown_);
	target.draw(colorDropdown_);
	target.draw(nameText_);
}
