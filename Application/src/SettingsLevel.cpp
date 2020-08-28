#include "SettingsLevel.h"

SettingsLevel::SettingsLevel()
{
	// --- Loading Gear Textures ----------------
	std::string botGearsLoc = location::BOT_GEARS;
	for (int i = 0; i < 20; i++) {
		botGearsTextures_.push_back(ng::Resources::AcquireTexture
		(botGearsLoc + std::to_string(i) + ".png"));
	}
	std::string topGearsLoc = location::TOP_GEARS;
	for (int i = 0; i < 20; i++) {
		topGearsTextures_.push_back(ng::Resources::AcquireTexture
		(topGearsLoc + std::to_string(i) + ".png"));
	}
	topGears_.setPosition(topGearsPosition_);
	botGears_.setPosition(botGearsPosition_);
	// -------------------------------------

	// --- Properties ----------------------
	soundSlider_.setLevel(ng::Audio::getSoundVolume());
	musicSlider_.setLevel(ng::Audio::getMusicVolume());

	for (auto& it: windowTypeStrings_) {
		windowTypeDropdown_.addDropString(it);
	}

	addResolutionsTo(videoModeDropdown_);
	// -------------------------------------

	// --- Setting Text Colors/ Positions ----------
	soundText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });
	musicText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });
	windowTypeText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });
	videoModeText_.setFillColor({ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B });

	ng::centerTextInBounds(soundText_, soundSlider_.getGlobalBounds(), soundTextOffset_);
	ng::centerTextInBounds(musicText_, musicSlider_.getGlobalBounds(), musicTextOffset_);
	ng::centerTextInBounds(windowTypeText_, windowTypeDropdown_.getClosedGlobalBounds(), windowTypeTextOffset_);
	ng::centerTextInBounds(videoModeText_, videoModeDropdown_.getClosedGlobalBounds(), videoModeTextOffset_);
	// -------------------------------------

	// --- Getting Outside Data --------------------
	if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_UNRESIZEABLE)
		windowTypeDropdown_.setActiveDrop(1); // windowed
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_BORDERLESS)
		windowTypeDropdown_.setActiveDrop(2); // borderless
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_FULLSCREEN)
		windowTypeDropdown_.setActiveDrop(3); // fullscreen
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_RESIZEABLE)
		NG_LOG_ERROR("Window has unsupported Type!"); /// !!! Resizeable window is considered error
	saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

	std::string resolutionString =
		std::to_string(ng::Main::windowVideoMode.width)
		+ " x " +
		std::to_string(ng::Main::windowVideoMode.height);
	videoModeDropdown_.setDropString(0, resolutionString);
	saveVideoMode_ = ng::Main::windowVideoMode;
	// ---------------------------------------------
}

void SettingsLevel::handleEvents(const sf::Event& event)
{
	if (resetDialog_.isActive())
	{
		resetDialog_.handleEvents(event, ng::Cursor::getPosition());

		// OK pressed => make changes permanent
		if (resetDialog_.getResponse() == ng::ConfirmDialog::RESPONSE::RESPONSE_OK)
			changeType_ = CHANGE::CHANGE_PERMANENT;
		// CLOSE pressed => reset changes
		else if (resetDialog_.getResponse() == ng::ConfirmDialog::RESPONSE::RESPONSE_CLOSE)
			changeType_ = CHANGE::CHANGE_REVERT;
		else
			changeType_ = CHANGE::CHANGE_NONE;
	}
	else
	{
		applyButton_.handleEvents(event, ng::Cursor::getPosition());
		backButton_.handleEvents(event, ng::Cursor::getPosition());
		soundSlider_.handleEvents(event, ng::Cursor::getPosition());
		musicSlider_.handleEvents(event, ng::Cursor::getPosition());
		windowTypeDropdown_.handleEvents(event, ng::Cursor::getPosition());
		videoModeDropdown_.handleEvents(event, ng::Cursor::getPosition());

		ng::Audio::setSoundVolume(soundSlider_.getLevel());
		ng::Audio::setMusicVolume(musicSlider_.getLevel());

		SettingsFile::setMusicVolume(ng::Audio::getMusicVolume());
		SettingsFile::setSoundVolume(ng::Audio::getSoundVolume());

		// fullscreen supports only one resolution
		if (windowTypeDropdown_.getActiveDrop() == 3) {
			videoModeDropdown_.setActiveDrop(1);
			videoModeDropdown_.setDisabled(true);
		}
		else {
			videoModeDropdown_.setDisabled(false);
		}

		if (applyButton_.isActive())
			changeType_ = CHANGE::CHANGE_TEMPORARY;
		else
			changeType_ = CHANGE::CHANGE_NONE;

		if (backButton_.isActive())
			Levels::currentLevel = Levels::LEVEL_TYPES::MENU;
	}
}

void SettingsLevel::update()
{
	botGearsAnimation_.update(botGearsTextures_);
	botGears_.setTexture(*botGearsAnimation_.getTexturePointer());

	topGearsAnimation_.update(topGearsTextures_);
	topGears_.setTexture(*topGearsAnimation_.getTexturePointer());

	if (resetDialog_.isActive()) {
		resetTimer_ += ng::Timer::getDeltaTime();
		int secsRemaining = static_cast<int>(resetLimit_ - resetTimer_);

		std::string confirmDialogString = resetDialogText_ +
			"\n                    Reverting in " + std::to_string(secsRemaining) + " seconds";

		resetDialog_.setString(confirmDialogString);

		if (secsRemaining == 0)
			changeType_ = CHANGE::CHANGE_REVERT; // type of change
	}

	if (changeType_ != CHANGE::CHANGE_NONE) {
		applySettingsToWindow();
	}
}

void SettingsLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);

	target.draw(botGears_);
	target.draw(topGears_);

	target.draw(soundSlider_);
	target.draw(soundText_);

	target.draw(musicSlider_);
	target.draw(musicText_);

	target.draw(backButton_);
	target.draw(applyButton_);

	target.draw(windowTypeDropdown_);
	target.draw(windowTypeText_);

	target.draw(videoModeDropdown_);
	target.draw(videoModeText_);

	target.draw(resetDialog_);
}

void SettingsLevel::applySettingsToWindow()
{
	sf::VideoMode videoMode;
	std::string windowTypeString;

	// --- Change based on changeType_ ------------------------------------------
	if (changeType_ == CHANGE::CHANGE_REVERT)
	{
		videoMode = saveVideoMode_;
		windowTypeString = saveWindowTypeString_;
		resetDialog_.setIsActive(false); // close dialog
	}
	else if (changeType_ == CHANGE::CHANGE_PERMANENT)
	{
		// PERMANENT always runs after TEMPORARY -> very important !
		saveVideoMode_ = ng::Main::windowVideoMode;
		saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		videoMode = ng::Main::windowVideoMode;
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
		resetDialog_.setIsActive(false); // close dialog
	}
	else if (changeType_ == CHANGE::CHANGE_TEMPORARY)
	{
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		if (windowTypeString == windowTypeStrings_[2])
			videoMode = sf::VideoMode::getDesktopMode(); // fullscreen resolution
		else if (videoModeDropdown_.getActiveDrop() != 0)  // if dropdown has one drop selected
			videoMode = videoModes_[videoModeDropdown_.getActiveDrop() - 1]; // apply selected
		else
			videoMode = ng::Main::windowVideoMode; // else use default
	}
	// --------------------------------------------------------------------------

	// --- Apply changes internally and externally ------------------------------
	// check if there is need for a dialog box
	auto tempType = ng::Main::windowType;
	auto tempVideoMode = ng::Main::windowVideoMode;

	if (windowTypeString == windowTypeStrings_[0]) // windowed
	{
		ng::Main::windowType = ng::WINDOW_TYPE::WINDOW_UNRESIZEABLE;
		windowTypeDropdown_.setActiveDrop(1);
	}
	else if (windowTypeString == windowTypeStrings_[1]) // borderless
	{
		ng::Main::windowType = ng::WINDOW_TYPE::WINDOW_BORDERLESS;
		windowTypeDropdown_.setActiveDrop(2);
	}
	else if (windowTypeString == windowTypeStrings_[2]) // fullscreen
	{
		ng::Main::windowType = ng::WINDOW_TYPE::WINDOW_FULLSCREEN;
		windowTypeDropdown_.setActiveDrop(3);
	}

	ng::Main::windowVideoMode = videoMode;

	std::string resolutionString =
		std::to_string(videoMode.width) + " x " + std::to_string(videoMode.height);

	SettingsFile::setVideoMode(ng::Main::windowVideoMode);
	SettingsFile::setWindowType(ng::Main::windowType);

	videoModeDropdown_.setDropString(0, resolutionString);

	// only start dialog if changes have been made
	if (changeType_ == CHANGE::CHANGE_TEMPORARY &&
		(tempType != ng::Main::windowType ||
		 tempVideoMode != ng::Main::windowVideoMode))
	{
		resetDialog_.setIsActive(true);
		resetTimer_ = 0; // start resetTimer_ from 0
	}
	// --------------------------------------------------------------------------
}

void SettingsLevel::addResolutionsTo(ng::Dropdown& dropdown)
{
	videoModes_.clear(); // clear resolution vector
	std::vector<sf::Vector2i> importantResolutions_ = {
	{1920, 1080},
	{1366, 768},
	{1360, 768},
	{1280, 800},
	{800, 600} };
	
	std::vector<sf::VideoMode> fullScreenModes_ = sf::VideoMode::getFullscreenModes();

	for (int i = 0; i < int(fullScreenModes_.size()); i++) {
		std::string resolutionString =
			std::to_string(fullScreenModes_[i].width) + " x " + std::to_string(fullScreenModes_[i].height);

		bool isImportant = false;
		for (int j = 0; j < int(importantResolutions_.size()); j++) {
			if (importantResolutions_[j].x == fullScreenModes_[i].width &&
				importantResolutions_[j].y == fullScreenModes_[i].height) {
				isImportant = true;
				break;
			}
		}

		if (videoModes_.size() < 8 || isImportant) {
			videoModes_.push_back(fullScreenModes_[i]);
			dropdown.addDropString(resolutionString);
		}
	}
}
