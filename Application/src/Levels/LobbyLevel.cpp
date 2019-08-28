#include "LobbyLevel.h"

void LobbyLevel::setup()
{
	// --- Loading Textures ----------------
	buttonTexture_ = ngin::Resources::AcquireTexture("images/ui/button.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/dropdown.png");
	smallDropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/small_dropdown.png");
	inputTexture_ = ngin::Resources::AcquireTexture("images/ui/input_text.png");
	switcherTexture_ = ngin::Resources::AcquireTexture("images/ui/block_switch.png");
	confirmDialogTexture_ = ngin::Resources::AcquireTexture("images/ui/confirm_dialog.png");
	mapContainerTexture_ = ngin::Resources::AcquireTexture("images/ui/map_container.png");
	backgroundTexture_ = ngin::Resources::AcquireTexture("images/ui/lobby_bg.jpg");
	warcraftFont_ = ngin::Resources::AcquireFont("fonts/warcraft.ttf");
	// -------------------------------------

	// --- Setting Textures ----------------
	mapSelector_.setTexture(*mapContainerTexture_);
	background_.setTexture(*backgroundTexture_);
	backButton_.setTexture(*buttonTexture_);
	playButton_.setTexture(*buttonTexture_);
	relativeColorSwitcher_.setTexture(*switcherTexture_);
	npcsDropdown_.setTexture(*smallDropdownTexture_);

	playerLine_.setTextures(*inputTexture_, *dropdownTexture_);
	confirmDialog_.setTextures(*confirmDialogTexture_, *buttonTexture_);

	for (auto& it : npcLines_) it.setTexture(*dropdownTexture_);
	// -------------------------------------

	// --- Setting Styles ------------------
	setupUIStyle(*warcraftFont_, 40, sf::Color::Yellow);
	// -------------------------------------

	// --- Setting Texts -------------------
	// Static texts
	playerText_.setString("Player:");
	nameText_.setString("Name");
	relativeColorText_.setString("Team Relative Colors");

	confirmDialog_.setString("Please create at least two teams \n"
		"in order to start the game!");

	// User
	playerLine_.setupStrings(races_, teams_, colors_);
	playerLine_.nameInput.setString(SettingsFile::getPlayerName());

	// NPC's
	for (int i = 0; i < int(npcLines_.size()); i++) {

		npcLines_[i].setupStrings(races_, teams_, colors_, difficulties_);

		if (npcLines_.size() + 1 != colors_.size()) {
			NG_LOG_ONCE_ERROR("Number of  Player::GameDetails::players (", npcLines_.size() + 1, ")"
				" does not equal number of colors (", colors_.size(), ")");
		}

		npcLines_[i].colorDropdown.setDropColor(0, colors_[i + 1]);
	}

	// Number of NPC's
	npcsDropdown_.setDropString(0, '1');
	for (int i = 0; i < int(npcLines_.size()); i++) {
		npcsDropdown_.addDropString(std::to_string(i + 1));
	}
	// -------------------------------------

	// --- Setting Positions ---------------
	backButton_.setPosition({ 105, 965 });
	playButton_.setPosition({ 735, 965 });
	npcsDropdown_.setPosition({ 45, 175 });
	playerLine_.setPosition({ 60, 95 });
	playerText_.setPosition({ 50, 25 });

	mapSelector_.setPosition({ 1370, 65 });

	ngin::centerTextInBounds(nameText_, playerLine_.nameInput.getGlobalBounds(), -40);

	confirmDialog_.setPosition({ 960 - confirmDialog_.getGlobalBounds().width / 2,
								540 - confirmDialog_.getGlobalBounds().height / 2 });

	relativeColorSwitcher_.setPosition(
		{ npcsDropdown_.getPosition().x + npcsDropdown_.getClosedGlobalBounds().width + 50, 800 });
	relativeColorText_.setPosition(
		{ relativeColorSwitcher_.getPosition().x + relativeColorSwitcher_.getGlobalBounds().width + 15 ,
		  relativeColorSwitcher_.getPosition().y - relativeColorText_.getLocalBounds().top });

	for (int i = 0; i < int(npcLines_.size()); i++) {
		npcLines_[i].setPosition({
			npcsDropdown_.getPosition().x + npcsDropdown_.getClosedGlobalBounds().width + 50,
			i * (npcLines_[i].difficultyDropdown.getClosedSize().y + 5) + 180 });
	}
	// -------------------------------------
}

void LobbyLevel::handleEvents(const sf::Event& event)
{
	if (dialogActive_)
	{
		confirmDialog_.handleEvents(event, ngin::Cursor::getPosition());

		if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK ||
			confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE) {
			dialogActive_ = false;
		}
	} 
	else
	{
		// Navigation
		backButton_.handleEvents(event, ngin::Cursor::getPosition());
		playButton_.handleEvents(event, ngin::Cursor::getPosition());
		relativeColorSwitcher_.handleEvents(event, ngin::Cursor::getPosition());

		// Map Selector
		mapSelector_.handleEvents(event, ngin::Cursor::getPosition());

		// Player
		sf::Color playerColor = playerLine_.colorDropdown.getDropColor(0); // save last color
		playerLine_.handleEvents(event, ngin::Cursor::getPosition());

		// update settings' string for later saving
		if(playerLine_.nameInput.getisActive()) {
			SettingsFile::setPlayerName(playerLine_.nameInput.getString());
		}

		// Number of AIS
		npcsDropdown_.handleEvents(event, ngin::Cursor::getPosition());
		if (npcsDropdown_.getActiveDrop() != 0) {
			npcsNo_ = npcsDropdown_.getActiveDrop(); // change number of active NPC's
		}

		// --- Color Duplicate Check -------------------------
		// don't let duplicate color selection happen
		if (playerLine_.colorDropdown.getActiveDrop() != 0 && !relativeColorSwitcher_.isActive()) {
			for (int i = 0; i < npcsNo_; i++) {
				if (playerLine_.colorDropdown.getDropColor(0) == npcLines_[i].colorDropdown.getDropColor(0))
				{
					playerLine_.colorDropdown.setDropColor(0, playerColor);
					break;
				}
			}
		}
		for (int i = 0; i < npcsNo_; i++) {
			// save selected color
			sf::Color npcColor = npcLines_[i].colorDropdown.getDropColor(0);

			// handle events
			npcLines_[i].handleEvents(event, ngin::Cursor::getPosition());

			// --- Color Duplicate Check -------------------------
			if (npcLines_[i].colorDropdown.getActiveDrop() != 0 && !relativeColorSwitcher_.isActive()) {

				// User
				if (npcLines_[i].colorDropdown.getDropColor(0) == playerLine_.colorDropdown.getDropColor(0))
					npcLines_[i].colorDropdown.setDropColor(0, npcColor);
				else for (int j = 0; j < npcsNo_; j++) { // NPC's
					if (npcLines_[i].colorDropdown.getDropColor(0) == npcLines_[j].colorDropdown.getDropColor(0)
						&& i != j)
					{
						npcLines_[i].colorDropdown.setDropColor(0, npcColor);
						break;
					}
				}
			}
			// ---------------------------------------------------
		}

		// don't let already used colors collide
		if (!relativeColorSwitcher_.isActive()) {

			int iColor = 0; // the index of color replacement
			for (int i = 0; i < npcsNo_; i++) {
				bool isUsed = false;

				// User
				if (npcLines_[i].colorDropdown.getDropColor(0) == playerLine_.colorDropdown.getDropColor(0))
					isUsed = true;
				else for (int j = 0; j < npcsNo_; j++) { // NPC's
					if (npcLines_[i].colorDropdown.getDropColor(0) == npcLines_[j].colorDropdown.getDropColor(0)
						&& i != j)
					{
						isUsed = true;
						break;
					}
				}

				if (isUsed) {
					npcLines_[i].colorDropdown.setDropColor(0, colors_[iColor]);

					iColor++; // step up color number
					if (iColor >= int(colors_.size())) // don't let out of bounds
						iColor = 0;

					i--; // check again
				}
			}
		}
		// ---------------------------------------------------

		// --- Relative Team Colors ----------------
		if (relativeColorSwitcher_.hasChanged()) {
			playerLine_.colorDropdown.setDisabled(relativeColorSwitcher_.isActive());
			for (auto& it : npcLines_)
				it.colorDropdown.setDisabled(relativeColorSwitcher_.isActive());
		}

		if (relativeColorSwitcher_.isActive()) {
			for (int i = 0; i < int(teams_.size()); i++) {
				if (playerLine_.teamDropdown.getActiveDrop() - 1 <= i) {
					playerLine_.colorDropdown.setDropColor(0, colors_[i]);
					break;
				}
			}

			for (auto& it : npcLines_) {
				for (int i = 0; i < int(teams_.size()); i++) {
					if (it.teamDropdown.getActiveDrop() - 1 <= i) {
						it.colorDropdown.setDropColor(0, colors_[i]);
						break;
					}
				}
			}
		}
		// -----------------------------------------

		// --- Navigation ------------------------------
		if (playButton_.isActive()) {
			// applies options to  Player::GameDetails::players' static class
			if (applyToPlayers()) {
				response_ = RESPONSE::PLAY;
			}
		}
		else if (backButton_.isActive()) {
			response_ = RESPONSE::BACK;
		}
		else {
			response_ = RESPONSE::NONE;
		}
		// ---------------------------------------------
	}
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

	for (int i = npcsNo_ - 1; i >= 0; i--) {
		target.draw(npcLines_[i]);
	}

	// Player
	target.draw(playerText_);
	target.draw(nameText_);
	target.draw(playerLine_);

	// Map Selector
	target.draw(mapSelector_);

	// Number of npc's dropdown
	target.draw(npcsDropdown_);

	// RelativeTeamColors
	target.draw(relativeColorSwitcher_);
	target.draw(relativeColorText_);

	if (dialogActive_)
		target.draw(confirmDialog_);
}

void LobbyLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setSelectColor(themeColor);
	backButton_.setTextColor(themeColor);

	playerText_.setFont(font);
	playerText_.setCharacterSize(fontSize);
	playerText_.setFillColor(themeColor);

	nameText_.setFont(font);
	nameText_.setCharacterSize(fontSize);
	nameText_.setFillColor(themeColor);

	playButton_.setFont(font);
	playButton_.setCharacterSize(fontSize);
	playButton_.setSelectColor(themeColor);
	playButton_.setTextColor(themeColor);

	playerLine_.setTheme(font, fontSize, themeColor);

	for (auto& it : npcLines_) {                   // scale
		it.setTheme(font, fontSize, themeColor, { 0.65F, 0.85F });
	}

	npcsDropdown_.setFont(font);
	npcsDropdown_.setTextColor(themeColor);
	npcsDropdown_.setSelectColor(themeColor);
	npcsDropdown_.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
	npcsDropdown_.setCharacterSize(fontSize);

	relativeColorSwitcher_.setScale({0.8F, 0.8F});
	relativeColorSwitcher_.setSelectColor(themeColor);
	relativeColorText_.setFont(font);
	relativeColorText_.setCharacterSize(fontSize + 4);
	relativeColorText_.setFillColor(themeColor);

	confirmDialog_.setFont(font);
	confirmDialog_.setTextColor(themeColor);
	confirmDialog_.setButtonsCharacterSize(fontSize - 2);
	confirmDialog_.setTextCharacterSize(fontSize + 7);
	confirmDialog_.setSelectColor(themeColor);

	mapSelector_.setSelectColor(themeColor);
	mapSelector_.setTextColor(themeColor);
	mapSelector_.setCharacterSize(fontSize - 5);
	mapSelector_.setFont(font);
}

bool LobbyLevel::applyToPlayers()
{
	// make sure vector is empty
	GameDetails::players.clear();

	// User
	playerLine_.addToPlayers(races_, teams_, colors_);

	// NPC's
	for (int i = 0; i < npcsNo_; i++) {
		npcLines_[i].addToPlayers(races_, teams_, colors_, difficulties_);
	}

	// --- Check for at least two teams ----------------------
	Player::Team teamCheck = GameDetails::players[0].team_;
	bool atLeastTwoTeams = false;

	for (int i = 0; i < int(GameDetails::players.size()); i++) {
		if (teamCheck != GameDetails::players[i].team_) {
			atLeastTwoTeams = true;
			break;
		}
	}
	// -------------------------------------------------------

	if (!atLeastTwoTeams) {
		dialogActive_ = true;
		return false; // error
	}
	else {
		for (int i = 0; i < int(GameDetails::players.size()); i++) {
			NG_LOG_INFO("Player", i, ": Race->", GameDetails::players[i].race_, " Team->", GameDetails::players[i].team_,
				" Color->(", int(GameDetails::players[i].color_.r), ", ", int(GameDetails::players[i].color_.g), ", ", int(GameDetails::players[i].color_.b), ")",
				" Difficulty->", GameDetails::players[i].difficulty_);
		}

		NG_LOG_WARN("Number of Players: ", GameDetails::players.size());

		return true;
	}
}
