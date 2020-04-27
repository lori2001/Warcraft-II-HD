#include "LobbyLevel.h"

LobbyLevel::LobbyLevel()
{
	// -- set text color and position ----
	playerText_.setPosition({ 50.0F, 25.0F });
	playerText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });

	relativeColorSwitcher_.setIsActive(GameDetailsFile::getTeamRelativeColors());
	ng::centerTextInBounds(190, relativeColorText_, relativeColorSwitcher_.getGlobalBounds());
	relativeColorText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });

	// -- Number of NPCs' dropdown ------------------
	npcsDropdown_.setDropString(0, std::to_string(GameDetailsFile::getNumberOfNPCs()));
	for (int i = 0; i < int(npcLines_.size()); i++)
		npcsDropdown_.addDropString(std::to_string(i + 1));

	// -- NPC Line's Position ----------------------
	for (int i = 0; i < static_cast<int>(GameDetailsFile::maxNumberOfNPCs); i++)
	{
		if (i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()))
			npcLines_[i].setupValuesWithIndex(i);

		npcLines_[i].setPosition({
			npcsDropdown_.getPosition().x + npcsDropdown_.getClosedGlobalBounds().width + 50,
			i * (npcLines_[i].getHeight() + 5) + npcLineYOffset_ });
	}
}

LobbyLevel::~LobbyLevel()
{
	GameDetailsFile::save();
}

void LobbyLevel::handleEvents(const sf::Event& event)
{
	relativeColorSwitcher_.handleEvents(event, ng::Cursor::getPosition());
	if (relativeColorSwitcher_.hasChanged()) {
		GameDetailsFile::setTeamRelativeColors(relativeColorSwitcher_.isActive());
		for (int i = 0; i < static_cast<int>(GameDetailsFile::getNumberOfNPCs()); i++) {
			npcLines_[i].setupValuesWithIndex(i);
		}
		playerLine_.correctForRelativeColor();
	}

	npcsDropdown_.handleEvents(event, ng::Cursor::getPosition()); // number of npc-s
	if (npcsDropdown_.hasChanged()) // forward selected number to game details
	{
		// setup new Ai slots if number of ai's inceases
		unsigned prevNum = GameDetailsFile::getNumberOfNPCs();
		GameDetailsFile::setNumberOfNPCs(std::stoi(npcsDropdown_.getDropString(0)));
		if (prevNum < GameDetailsFile::getNumberOfNPCs()) {
			for (unsigned i = prevNum; i < GameDetailsFile::getNumberOfNPCs(); i++) {
				npcLines_[i].setupValuesWithIndex(i);
			}
		}
	}
	
	mapSelector_.handleEvents(event, ng::Cursor::getPosition());

	playerLine_.handleEvents(event, ng::Cursor::getPosition()); // player-line events
	for(unsigned i = 0; i < GameDetailsFile::getNumberOfNPCs(); i++) // handle events of active npc-lines
		npcLines_[i].handleEvents(event, ng::Cursor::getPosition(), i);

	// --- Level navigation -------------------
	backButton_.handleEvents(event, ng::Cursor::getPosition());
	playButton_.handleEvents(event, ng::Cursor::getPosition());

	if (backButton_.isActive()) {
		Levels::currentLevel = Levels::LEVEL_TYPES::MENU;
	}
	else if (playButton_.isActive()) {
		NG_LOG_ERROR("Nothin' here!");
		// Levels::currentLevel = Levels::LEVEL_TYPES::GAME;
		GameDetailsFile::getActualNPCRace(0);
		GameDetailsFile::getActualNPCRace(1);
		GameDetailsFile::getActualNPCRace(2);
		GameDetailsFile::getActualNPCRace(3);
	}
	// ----------------------------------------
}

void LobbyLevel::update()
{
}

void LobbyLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Backgrounnd
	target.draw(background_);

	// Navigation
	target.draw(backButton_);
	target.draw(playButton_);

	// RelativeTeamColors
	target.draw(relativeColorSwitcher_);
	target.draw(relativeColorText_);

	// NPC Lines
	for (int i = GameDetailsFile::getNumberOfNPCs()-1; i >= 0 ; i--) // draw backwards
		target.draw(npcLines_[i]);

	// Number of npc's dropdown
	target.draw(npcsDropdown_);

	// Player
	target.draw(playerText_);
	target.draw(playerLine_);

	// Map Selector
	target.draw(mapSelector_);
} 