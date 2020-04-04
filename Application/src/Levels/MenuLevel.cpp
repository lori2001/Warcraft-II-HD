#include "MenuLevel.h"

MenuLevel::MenuLevel()
{
	buttonTexture_ = ng::Resources::AcquireTexture("images/ui/button.png");
	font_ = ng::Resources::AcquireFont("fonts/warcraft.ttf");
	backgroundTexture_ = ng::Resources::AcquireTexture("images/ui/menu_bg.jpg");

	// Aquire Texture resource-heavy textures to make a faster menu
	for (int i = 0; i < 20; i++) {
		ng::Resources::AcquireTexture("images/bot_gears/" + std::to_string(i) + ".png");
		ng::Resources::AcquireTexture("images/top_gears/" + std::to_string(i) + ".png");
	}
	// make sure cursor is in orc-mode
	ng::Cursor::setTexture(*ng::Resources::AcquireTexture("images/ui/orc_cursor.png"));

	background_.setTexture(*backgroundTexture_);

	setupButtonsStyle(*buttonTexture_, *font_, 40, sf::Color::Yellow);

	// !! only works for same-size buttons
	float XCenter = 1920 / 2 - startButton_.getSize().x / 2;

	startButton_.setPosition({ XCenter, 1080 / 2 - 3 * startButton_.getSize().y });
	settingsButton_.setPosition({ XCenter, 1080 / 2 - 1.5F * settingsButton_.getSize().y });
	editorButton_.setPosition({ XCenter, 1080 / 2 + 0 * editorButton_.getSize().y });
	exitButton_.setPosition({ XCenter, 1080 / 2 + 1.5F * exitButton_.getSize().y });
}

void MenuLevel::handleEvents(const sf::Event& event)
{
	startButton_.handleEvents(event, ng::Cursor::getPosition());
	settingsButton_.handleEvents(event, ng::Cursor::getPosition());
	editorButton_.handleEvents(event, ng::Cursor::getPosition());
	exitButton_.handleEvents(event, ng::Cursor::getPosition());

	if (startButton_.isActive()) {
		Levels::event = Levels::EVENT::EVENT_LOBBY;
	}
	else if (settingsButton_.isActive()) {
		Levels::event = Levels::EVENT::EVENT_SETTINGS;
	}
	else if (editorButton_.isActive()) {
		Levels::event = Levels::EVENT::EVENT_EDITOR;
	}
	else if (exitButton_.isActive()) {
		// exit
		ng::Main::closeWindow();
	}
	else {
		Levels::event = Levels::EVENT::EVENT_NONE;
	}
}

void MenuLevel::update()
{
	Music::playTheme(Music::Theme::Menu);
}

void MenuLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);
	target.draw(startButton_);
	target.draw(settingsButton_);
	target.draw(editorButton_);
	target.draw(exitButton_);
}

void MenuLevel::setupButtonsStyle(const sf::Texture& texture, const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	startButton_.setCharacterSize(fontSize);
	settingsButton_.setCharacterSize(fontSize);
	editorButton_.setCharacterSize(fontSize);
	exitButton_.setCharacterSize(fontSize);

	startButton_.setTexture(texture);
	settingsButton_.setTexture(texture);
	editorButton_.setTexture(texture);
	exitButton_.setTexture(texture);

	startButton_.setFont(font);
	settingsButton_.setFont(font);
	editorButton_.setFont(font);
	exitButton_.setFont(font);

	startButton_.setTextColor(themeColor);
	settingsButton_.setTextColor(themeColor);
	editorButton_.setTextColor(themeColor);
	exitButton_.setTextColor(themeColor);

	startButton_.setSelectColor(themeColor);
	settingsButton_.setSelectColor(themeColor);
	editorButton_.setSelectColor(themeColor);
	exitButton_.setSelectColor(themeColor);
}
