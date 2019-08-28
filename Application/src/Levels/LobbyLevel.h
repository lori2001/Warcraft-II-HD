#pragma once
#include "NGin.h"

#include "../Files/SettingsFile.h"

#include "Lobby/ColoredString.h"
#include "Lobby/PlayerLine.h"
#include "Lobby/NPCLine.h"
#include "Lobby/MapSelector.h"

#include "Common/ConfirmDialog.h"
#include "Common/GameDetails.h"

class LobbyLevel : public ngin::Level {
public:
	LobbyLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 5,
		BACK,
		PLAY
	};

private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);
	bool applyToPlayers();

	// Resources
	std::shared_ptr<sf::Font> warcraftFont_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> dropdownTexture_;
	std::shared_ptr<sf::Texture> smallDropdownTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;
	std::shared_ptr<sf::Texture> inputTexture_;
	std::shared_ptr<sf::Texture> switcherTexture_;
	std::shared_ptr<sf::Texture> confirmDialogTexture_;
	std::shared_ptr<sf::Texture> mapContainerTexture_;

	// Background
	sf::Sprite background_;

	// Navigation buttons 
	ngin::Button backButton_{ "Back", {430, 50} };
	ngin::Button playButton_ { "Play", {430, 50} };

	// Static stuff
	sf::Text playerText_;
	sf::Text nameText_;
	sf::Text relativeColorText_;

	// Input Lines
	PlayerLine playerLine_; // object for player
	std::vector<NPCLine> npcLines_{ 11, NPCLine{} }; // objects for NPC's

	// Confirm Dialog to block invalid situations
	ConfirmDialog confirmDialog_;
	bool dialogActive_ = false;

	// Map Selector
	MapSelector mapSelector_;

	// Nr of NPC's dropdown
	ngin::Dropdown npcsDropdown_{ {69, 54} };
	int npcsNo_ = 1; 

	// To toggle team-relative color mode
	ngin::Switcher relativeColorSwitcher_{ { 59 , 54 }, { 71, 80 } };

	// Selectables' Content
	const std::vector<ColoredString> races_
	{	{ "Random" , sf::Color::Yellow},
		{ "Orcs[" , sf::Color::Red},
		{ "Humans]" , sf::Color::Blue}};

	const std::vector<std::string> difficulties_ { "Easy", "Medium", "Hard"};

	const std::vector<std::string> teams_{ "Team 1",  "Team 2",  "Team 3",
				   						   "Team 4",  "Team 5",  "Team 6",
										   "Team 7",  "Team 8",  "Team 9",
										   "Team 10", "Team 11", "Team 12",};
	const std::vector<sf::Color> colors_
	{
		sf::Color(255,   0,   0), // 1.red 
		sf::Color(0, 255,   0), // 2.green
		sf::Color(0,   0, 255), // 3.blue
		sf::Color(255,  69,   0), // 4.orange
		sf::Color(255, 255,   0), // 5.yellow
		sf::Color(0, 255, 255), // 6.cyan
		sf::Color(128,   0, 128), // 7.purple
		sf::Color(255, 255, 255), // 8.white
		sf::Color(139,  69,  19), // 9.brown
		sf::Color(128, 128, 128), // 10.grey
		sf::Color(255,  20, 147), // 11.pink
		sf::Color(0,   0,   0)  // 12.black
	};
};