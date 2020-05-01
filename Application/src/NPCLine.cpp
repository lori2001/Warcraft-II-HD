#include "NPCLine.h"
#include <chrono>
#include <random>

void NPCLine::setPosition(const sf::Vector2f& position)
{
	difficultyDropdown_.setPosition(position);

	raceDropdown_.setPosition(
		{ difficultyDropdown_.getPosition().x + difficultyDropdown_.getClosedGlobalBounds().width + dropdownXOffset_,
		  difficultyDropdown_.getPosition().y });

	teamDropdown_.setPosition(
		{ raceDropdown_.getPosition().x + raceDropdown_.getClosedGlobalBounds().width + dropdownXOffset_,
		  raceDropdown_.getPosition().y });

	colorDropdown_.setPosition(
		{ teamDropdown_.getPosition().x + teamDropdown_.getClosedGlobalBounds().width + dropdownXOffset_,
		  teamDropdown_.getPosition().y });
}

void NPCLine::setupValuesWithIndex(const int index)
{
	bool found = false;
	for (auto& it : races_)
		if (it.string == GameDetailsFile::getNPCRace(index)) {
			raceDropdown_.setDropString(0, it.string);
			raceDropdown_.setDropTextColor(0, it.color);
			found = true;
			break;
		}
	if (!found) throw ("Error setting player race! Race in file does not exist!");

	difficultyDropdown_.setDropString(0, GameDetailsFile::getNPCDifficulty(index));
	teamDropdown_.setDropString(0, GameDetailsFile::getNPCTeam(index));
	
	if (GameDetailsFile::getTeamRelativeColors())
	{
		colorDropdown_.setDisabled(true);
		// search for an index number
		auto teamIndex =
			std::find(GameDetailsFile::teams_.begin(),
				GameDetailsFile::teams_.end(),
				teamDropdown_.getDropString(0));

		int teamIndexInt = std::distance(GameDetailsFile::teams_.begin(), teamIndex);
		GameDetailsFile::setNPCColor(index, GameDetailsFile::colors_[teamIndexInt].toInteger());
	}
	else // if colors are not team relative
	{
		colorDropdown_.setDisabled(false);
		int indexOfColor = 0;
		unsigned choosenColor = GameDetailsFile::colors_[indexOfColor].toInteger();

		// see if the color has been already used
		bool alreadyUsed;
		do {
			alreadyUsed = GameDetailsFile::getPlayerColor() == choosenColor;
			if (!alreadyUsed)
			{
				for (int i = 0; i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()); i++)
				{
					if (index != i && choosenColor == getNPCColor(i))
					{
						alreadyUsed = true;
						break;
					}
				}
			}

			if (!alreadyUsed)
				GameDetailsFile::setNPCColor(index, choosenColor);
			else // try next color
				choosenColor = GameDetailsFile::colors_[++indexOfColor].toInteger();
		}
		while (alreadyUsed);
	}
	colorDropdown_.setDropColor(0, sf::Color{ GameDetailsFile::getNPCColor(index) });
}

NPCLine::NPCLine(const sf::Vector2f& position)
{
	setPosition(position);

	for (int j = 0; j < int(races_.size()); j++) {
		raceDropdown_.addDropString(races_[j].string);
		raceDropdown_.setDropTextColor(j + 1, races_[j].color);
	}
	for (int j = 0; j < int(difficulties_.size()); j++) {
		difficultyDropdown_.addDropString(difficulties_[j]);
	}
	for (int j = 0; j < int(teams_.size()); j++) {
		teamDropdown_.addDropString(teams_[j]);
	}
	for (int j = 0; j < int(colors_.size()); j++) {
		colorDropdown_.addDropColor(colors_[j]);
	}
}

void NPCLine::handleEvents(const sf::Event& event, const sf::Vector2f& mouse, const int index)
{
	difficultyDropdown_.handleEvents(event, mouse);
	raceDropdown_.handleEvents(event, mouse);
	teamDropdown_.handleEvents(event, mouse);
	colorDropdown_.handleEvents(event, mouse);

	if (difficultyDropdown_.hasChanged()) {
		GameDetailsFile::setNPCDifficulty(index, difficultyDropdown_.getDropString(0));
	}
	if (raceDropdown_.hasChanged()) {
		GameDetailsFile::setNPCRace(index, raceDropdown_.getDropString(0));
	}
	else if (teamDropdown_.hasChanged()) {
		const std::string teamBefore = GameDetailsFile::getNPCTeam(index);
		GameDetailsFile::setNPCTeam(index, teamDropdown_.getDropString(0));

		// set only if there are at least two active teams
		bool atLeastTwo = false;
		for (int i = 0; i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()); i++) {
			if (getNPCTeam(i) != getPlayerTeam())
			{
				atLeastTwo = true;
				break;
			}
		}

		if (!atLeastTwo) // set the team back
		{
			GameDetailsFile::setNPCTeam(index, teamBefore);
			teamDropdown_.setDropString(0, teamBefore);
		}

		if (GameDetailsFile::getTeamRelativeColors())
		{
			// search for an index number
			auto teamIndex =
				std::find(GameDetailsFile::teams_.begin(),
					GameDetailsFile::teams_.end(),
					teamDropdown_.getDropString(0));

			int teamIndexInt = std::distance(GameDetailsFile::teams_.begin(), teamIndex);
			GameDetailsFile::setNPCColor(index, GameDetailsFile::colors_[teamIndexInt].toInteger());
			colorDropdown_.setDropColor(0, sf::Color{ GameDetailsFile::getNPCColor(index) });
		}
	}
	else if(colorDropdown_.hasChanged())
	{
		// if colors are NOT relative to the team
		if (!GameDetailsFile::getTeamRelativeColors())
		{
			const unsigned oldColor = GameDetailsFile::getNPCColor(index);
			const unsigned newColor = colorDropdown_.getDropColor(0).toInteger();

			// see if the new color has been already used
			bool alreadyUsed = GameDetailsFile::getPlayerColor() == newColor;
			if (!alreadyUsed)
			{
				for (int i = 0; i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()); i++)
				{
					if (index != i && newColor == getNPCColor(i))
					{
						alreadyUsed = true;
						break;
					}
				}
			}

			if (alreadyUsed) // if already used then revert to the one before
				colorDropdown_.setDropColor(0, sf::Color{ oldColor });
			else // if not used just use the new one
				GameDetailsFile::setNPCColor(index, newColor);
		}
	}
}

void NPCLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(difficultyDropdown_);
	target.draw(raceDropdown_);
	target.draw(teamDropdown_);
	target.draw(colorDropdown_);
}
