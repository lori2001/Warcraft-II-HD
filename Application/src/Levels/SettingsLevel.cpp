#include "SettingsLevel.h"

void SettingsLevel::setup()
{
	// --- Loading Textures ----------------
	buttonTexture_ = ngin::Resources::AcquireTexture("images/ui/button.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/dropdown.png");
	sliderTexture_ = ngin::Resources::AcquireTexture("images/ui/slider.png");
	confirmDialogTexture_ = ngin::Resources::AcquireTexture("images/ui/confirm_dialog.png");
	backgroundTexture_ = ngin::Resources::AcquireTexture("images/ui/settings_bg.jpg");
	warcraftFont_ = ngin::Resources::AcquireFont("fonts/warcraft.ttf");

	for (int i = 0; i < 20; i++) {
		botGearsTextures_.push_back(ngin::Resources::AcquireTexture
		("images/bot_gears/" + std::to_string(i) + ".png"));
	}

	for (int i = 0; i < 20; i++) {
		topGearsTextures_.push_back(ngin::Resources::AcquireTexture
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
	soundSlider_.setLevel(ngin::Audio::getSoundVolume());
	soundText_.setString("Sound Volume:");
	musicSlider_.setLevel(ngin::Audio::getMusicVolume());
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
	ngin::centerTextInBounds(soundText_, soundSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(musicText_, musicSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(windowModeText_, windowTypeDropdown_.getClosedGlobalBounds(), -45);
	ngin::centerTextInBounds(resolutionText_, videoModeDropdown_.getClosedGlobalBounds(), -45);
	// -------------------------------------
}

void SettingsLevel::handleEvents(const sf::Event& event)
{
	// default response
	response_ = RESPONSE::NONE;

	if (dialogActive_)
	{
		confirmDialog_.handleEvents(event, ngin::Cursor::getPosition());

		if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK ||
			confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
		{
			// OK pressed => make chnages permanent
			if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::OK)
				changeType_ = CHANGE::PERMANENT;
			// CLOSE pressed => reset changes
			else if (confirmDialog_.getResponse() == ConfirmDialog::RESPONSE::CLOSE)
				changeType_ = CHANGE::REVERT;

			// type of change
			response_ = RESPONSE::APPLY;
		}
	}
	else
	{
		applyButton_.handleEvents(event, ngin::Cursor::getPosition());
		backButton_.handleEvents(event, ngin::Cursor::getPosition());
		soundSlider_.handleEvents(event, ngin::Cursor::getPosition());
		musicSlider_.handleEvents(event, ngin::Cursor::getPosition());
		windowTypeDropdown_.handleEvents(event, ngin::Cursor::getPosition());
		videoModeDropdown_.handleEvents(event, ngin::Cursor::getPosition());

		ngin::Audio::setSoundVolume(soundSlider_.getLevel());
		ngin::Audio::setMusicVolume(musicSlider_.getLevel());

		// fullscreen supports only one resolution
		if (windowTypeDropdown_.getActiveDrop() == 3) {
			videoModeDropdown_.setActiveDrop(1);
			videoModeDropdown_.setDisabled(true);
		}
		else {
			videoModeDropdown_.setDisabled(false);
		}

		if (applyButton_.isActive()) {
			changeType_ = CHANGE::TEMPORARY;
			response_ = RESPONSE::APPLY;
		}
		else if (backButton_.isActive()) {
			response_ = RESPONSE::MAIN_MENU;
		}
	}
}

void SettingsLevel::update()
{
	botGearsAnimation_.update(botGearsTextures_);
	botGears_.setTexture(*botGearsAnimation_.getTexturePointer());

	topGearsAnimation_.update(topGearsTextures_);
	topGears_.setTexture(*topGearsAnimation_.getTexturePointer());

	if (dialogActive_) {
		resetTimer_ += ngin::Timer::getDeltaTime();
		int secsRemaining = static_cast<int>(resetLimit_ - resetTimer_);

		std::string confirmDialogString = "Are you sure you want to keep these changes?\n"
			"                    Resetting in " + std::to_string(secsRemaining) + " seconds";

		confirmDialog_.setString(confirmDialogString);

		if (resetTimer_ > resetLimit_)
		{
			changeType_ = CHANGE::REVERT;
			// type of change
			response_ = RESPONSE::APPLY;
		}
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

void SettingsLevel::changeWindow(sf::VideoMode& windowVideoMode,
							sf::String& windowName,
							ngin::MainLevel::WINDOW_TYPE& windowType)
{
	sf::VideoMode videoMode;
	std::string windowTypeString;

	// --- Change based on changeType_ ------------------------------------------
	if (changeType_ == CHANGE::REVERT)
	{
		videoMode = saveVideoMode_;
		windowTypeString = saveWindowTypeString_;
		dialogActive_ = false; // close dialog
	}
	else if (changeType_ == CHANGE::PERMANENT)
	{
		// PERMANENT always runs after TEMPORARY -> very important !
		saveVideoMode_ = windowVideoMode;
		saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		videoMode = windowVideoMode;
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
		dialogActive_ = false; // close dialog
	}
	else if (changeType_ == CHANGE::TEMPORARY)
	{
		windowTypeString = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];

		if (windowTypeString == windowTypeStrings_[2])
			videoMode = sf::VideoMode::getDesktopMode(); // fullscreen resolution
		else if (videoModeDropdown_.getActiveDrop() != 0)  // if dropdown has one drop selected
			videoMode = videoModes_[videoModeDropdown_.getActiveDrop() - 1]; // apply selected
		else
			videoMode = windowVideoMode; // else use default
	}
	// --------------------------------------------------------------------------

	// --- Apply changes internally and externally ------------------------------
	// check if there is need for a dialog box
	auto tempType = windowType;
	auto tempVideoMode = windowVideoMode;

	if (windowTypeString == windowTypeStrings_[0]) // windowed
	{
		windowType = ngin::MainLevel::UNRESIZEABLE;
		windowTypeDropdown_.setActiveDrop(1);
	}
	else if (windowTypeString == windowTypeStrings_[1]) // borderless
	{
		windowType = ngin::MainLevel::BORDERLESS;
		windowTypeDropdown_.setActiveDrop(2);
	}
	else if (windowTypeString == windowTypeStrings_[2]) // fullscreen
	{
		windowType = ngin::MainLevel::FULLSCREEN;
		windowTypeDropdown_.setActiveDrop(3);
	}

	windowVideoMode = videoMode;

	std::string resolutionString =
		std::to_string(videoMode.width) + " x " + std::to_string(videoMode.height);

	videoModeDropdown_.setDropString(0, resolutionString);

	// only start dialog if changes have been made
	if (changeType_ == CHANGE::TEMPORARY &&
		(tempType != windowType || tempVideoMode != windowVideoMode)) {
		dialogActive_ = true; // open dialog
		resetTimer_ = 0; // start resetTimer_ from 0
	}
	// --------------------------------------------------------------------------
}

void SettingsLevel::getFromWindow(const sf::VideoMode& windowVideoMode,
							 const sf::String& windowName,
							 const ngin::MainLevel::WINDOW_TYPE& windowType)
{

	if (windowType == ngin::MainLevel::WINDOW_TYPE::UNRESIZEABLE)
		windowTypeDropdown_.setActiveDrop(1); // windowed
	else if (windowType == ngin::MainLevel::WINDOW_TYPE::BORDERLESS)
		windowTypeDropdown_.setActiveDrop(2); // borderless
	else if (windowType == ngin::MainLevel::WINDOW_TYPE::FULLSCREEN)
		windowTypeDropdown_.setActiveDrop(3); // fullscreen
	else if (windowType == ngin::MainLevel::WINDOW_TYPE::RESIZEABLE)
		NG_LOG_ERROR("Window has unsupported Type!"); /// !!! Resizeable window is considered error

	std::string resolutionString =
		std::to_string(windowVideoMode.width) + " x " + std::to_string(windowVideoMode.height);
	videoModeDropdown_.setDropString(0, resolutionString);

	saveWindowTypeString_ = windowTypeStrings_[windowTypeDropdown_.getActiveDrop() - 1];
	saveVideoMode_ = windowVideoMode;
}

void SettingsLevel::addResolutionsTo(ngin::Dropdown& dropdown)
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
