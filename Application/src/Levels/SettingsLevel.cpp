#include "SettingsLevel.h"
#include "NGin/Levels/Main.h"

SettingsLevel::SettingsLevel()
{
	// --- Loading Textures ----------------
	buttonTexture_ = ng::Resources::AcquireTexture("images/ui/button.png");
	dropdownTexture_ = ng::Resources::AcquireTexture("images/ui/dropdown.png");
	sliderTexture_ = ng::Resources::AcquireTexture("images/ui/slider.png");
	confirmDialogTexture_ = ng::Resources::AcquireTexture("images/ui/confirm_dialog.png");
	backgroundTexture_ = ng::Resources::AcquireTexture("images/ui/settings_bg.jpg");
	warcraftFont_ = ng::Resources::AcquireFont("fonts/warcraft.ttf");

	for (int i = 0; i < 20; i++) {
		botGearsTextures_.push_back(ng::Resources::AcquireTexture
		("images/bot_gears/" + std::to_string(i) + ".png"));
	}

	for (int i = 0; i < 20; i++) {
		topGearsTextures_.push_back(ng::Resources::AcquireTexture
		("images/top_gears/" + std::to_string(i) + ".png"));
	}
	// -------------------------------------

	// --- Setting Textures ----------------
	backButton_.setTexture(*buttonTexture_);
	applyButton_.setTexture(*buttonTexture_);
	soundSlider_.setTexture(*sliderTexture_);
	musicSlider_.setTexture(*sliderTexture_);
	background_.setTexture(*backgroundTexture_);
	videoModeDropdown_.setTexture(*dropdownTexture_);
	windowTypeDropdown_.setTexture(*dropdownTexture_);
	confirmDialog_.setTextures(*confirmDialogTexture_, *buttonTexture_);
	// -------------------------------------

	// --- Setting Styles ------------------
	setupUIStyle(*warcraftFont_, 40, sf::Color::Yellow);
	// -------------------------------------

	// --- Setting Scales ------------------
	soundSlider_.setScale({ 1.2F, 1.2F });
	musicSlider_.setScale({ 1.2F, 1.2F });
	// -------------------------------------

	// --- Other Properties ----------------
	soundSlider_.setLevel(ng::Audio::getSoundVolume());
	soundText_.setString("Sound Volume:");
	musicSlider_.setLevel(ng::Audio::getMusicVolume());
	musicText_.setString("Music Volume:");

	confirmDialog_.setString("Are you sure you want to keep these changes?");

	windowModeText_.setString("Window Mode:");
	windowTypeDropdown_.addDropString("Windowed");
	windowTypeDropdown_.addDropString("Borderless");
	windowTypeDropdown_.addDropString("Fullscreen");
	/*windowModeDropdown_ drop nr 0 set in getFromWindow()*/

	resolutionText_.setString("Resolution:");
	addResolutionsTo(videoModeDropdown_);
	/*resolutionDropdown_ drop nr 0 set in getFromWindow()*/
	// -------------------------------------

	// --- Setting Positions ---------------
	backButton_.setPosition({ 105, 965 });
	applyButton_.setPosition({ 735, 965 });
	soundSlider_.setPosition({ 425, 450 });
	musicSlider_.setPosition({ 425, 600 });
	windowTypeDropdown_.setPosition({ 1000, 600 });
	videoModeDropdown_.setPosition({ 1300, 450 });

	confirmDialog_.setPosition({ 960 - confirmDialog_.getGlobalBounds().width / 2,
								 540 - confirmDialog_.getGlobalBounds().height / 2 });
	confirmDialog_.setTextOffset(-40.0F);

	topGears_.setPosition({ 100, 60 });
	botGears_.setPosition({ 1300, 500 });
	ng::centerTextInBounds(soundText_, soundSlider_.getGlobalBounds(), -47);
	ng::centerTextInBounds(musicText_, musicSlider_.getGlobalBounds(), -47);
	ng::centerTextInBounds(windowModeText_, windowTypeDropdown_.getClosedGlobalBounds(), -45);
	ng::centerTextInBounds(resolutionText_, videoModeDropdown_.getClosedGlobalBounds(), -45);
	// -------------------------------------

	// --- Getting Data --------------------
	if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_UNRESIZEABLE)
		windowTypeDropdown_.setActiveDrop(1); // windowed
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_BORDERLESS)
		windowTypeDropdown_.setActiveDrop(2); // borderless
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_FULLSCREEN)
		windowTypeDropdown_.setActiveDrop(3); // fullscreen
	else if (ng::Main::windowType == ng::WINDOW_TYPE::WINDOW_RESIZEABLE)
		NG_LOG_ERROR("Window has unsupported Type!"); /// !!! Resizeable window is considered error

	std::string resolutionString =
		std::to_string(ng::Main::windowVideoMode.width)
		+ " x " +
		std::to_string(ng::Main::windowVideoMode.height);

	videoModeDropdown_.setDropString(0, resolutionString);

	saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
	saveVideoMode_ = ng::Main::windowVideoMode;
	// -------------------------------------
}

void SettingsLevel::handleEvents(const sf::Event& event)
{
	// default response and changeType
	Levels::event = Levels::EVENT::EVENT_NONE;

	if (dialogActive_)
	{
		confirmDialog_.handleEvents(event, ng::Cursor::getPosition());

		if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK ||
			confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
		{
			// OK pressed => make changes permanent
			if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK)
				changeType_ = CHANGE::CHANGE_PERMANENT;
			// CLOSE pressed => reset changes
			else if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
				changeType_ = CHANGE::CHANGE_REVERT;
			else
				changeType_ = CHANGE::CHANGE_NONE;
		}
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
			Levels::event = Levels::EVENT::EVENT_MENU;
	}
}

void SettingsLevel::update()
{
	botGearsAnimation_.update(botGearsTextures_);
	botGears_.setTexture(*botGearsAnimation_.getTexturePointer());

	topGearsAnimation_.update(topGearsTextures_);
	topGears_.setTexture(*topGearsAnimation_.getTexturePointer());

	if (dialogActive_) {
		resetTimer_ += ng::Timer::getDeltaTime();
		int secsRemaining = static_cast<int>(resetLimit_ - resetTimer_);

		std::string confirmDialogString = "Are you sure you want to keep these changes?\n"
			"                    Reverting in " + std::to_string(secsRemaining) + " seconds";

		confirmDialog_.setString(confirmDialogString);

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
	target.draw(windowModeText_);

	target.draw(videoModeDropdown_);
	target.draw(resolutionText_);

	if (dialogActive_)
		target.draw(confirmDialog_);
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
		dialogActive_ = false; // close dialog
	}
	else if (changeType_ == CHANGE::CHANGE_PERMANENT)
	{
		// PERMANENT always runs after TEMPORARY -> very important !
		saveVideoMode_ = ng::Main::windowVideoMode;
		saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		videoMode = ng::Main::windowVideoMode;
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
		dialogActive_ = false; // close dialog
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

	videoModeDropdown_.setDropString(0, resolutionString);

	// only start dialog if changes have been made
	if (changeType_ == CHANGE::CHANGE_TEMPORARY &&
		(tempType != ng::Main::windowType ||
		 tempVideoMode != ng::Main::windowVideoMode)) {
		dialogActive_ = true; // open dialog
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
	
	// important + FullScreenModes ( 5 + 7(max)) = 12MAX DROPDOWNS
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

		if (i <= 7 || isImportant) {
			videoModes_.push_back(fullScreenModes_[i]);
			dropdown.addDropString(resolutionString);
		}
	}
}

void SettingsLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setSelectColor(themeColor);
	backButton_.setTextColor(themeColor);

	applyButton_.setFont(font);
	applyButton_.setCharacterSize(fontSize);
	applyButton_.setSelectColor(themeColor);
	applyButton_.setTextColor(themeColor);

	soundSlider_.setSelectThickness(2.5F);
	soundSlider_.setSelectColor(themeColor);

	soundText_.setFont(font);
	soundText_.setFillColor(themeColor);
	soundText_.setCharacterSize(fontSize);

	musicSlider_.setSelectThickness(2.5F);
	musicSlider_.setSelectColor(themeColor);

	musicText_.setFont(font);
	musicText_.setFillColor(themeColor);
	musicText_.setCharacterSize(fontSize);

	windowTypeDropdown_.setFont(font);
	windowTypeDropdown_.setSelectColor(themeColor);
	windowTypeDropdown_.setTextColor(themeColor);
	windowTypeDropdown_.setCharacterSize(fontSize);
	windowTypeDropdown_.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });

	videoModeDropdown_.setFont(font);
	videoModeDropdown_.setSelectColor(themeColor);
	videoModeDropdown_.setTextColor(themeColor);
	videoModeDropdown_.setCharacterSize(fontSize);
	videoModeDropdown_.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });

	windowModeText_.setFont(font);
	windowModeText_.setFillColor(themeColor);
	windowModeText_.setCharacterSize(fontSize);

	resolutionText_.setFont(font);
	resolutionText_.setFillColor(themeColor);
	resolutionText_.setCharacterSize(fontSize);

	confirmDialog_.setFont(font);
	confirmDialog_.setTextColor(themeColor);
	confirmDialog_.setButtonsCharacterSize(fontSize - 2);
	confirmDialog_.setTextCharacterSize(fontSize + 7);
	confirmDialog_.setSelectColor(themeColor);
}
