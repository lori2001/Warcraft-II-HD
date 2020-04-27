#include "MenuLevel.h"

MenuLevel::MenuLevel()
{
	backgroundTexture = NG_TEXTURE_SPTR(location::MENU_BG);
	background_.setTexture(*backgroundTexture);
}

void MenuLevel::handleEvents(const sf::Event& event)
{
	startButton_.handleEvents(event, ng::Cursor::getPosition());
	settingsButton_.handleEvents(event, ng::Cursor::getPosition());
	editorButton_.handleEvents(event, ng::Cursor::getPosition());
	exitButton_.handleEvents(event, ng::Cursor::getPosition());

	if (startButton_.isActive()) {
		Levels::currentLevel = Levels::LEVEL_TYPES::LOBBY;
	}
	else if (settingsButton_.isActive()) {
		Levels::currentLevel = Levels::LEVEL_TYPES::SETTINGS;
	}
	else if (editorButton_.isActive()) {
		Levels::currentLevel = Levels::LEVEL_TYPES::EDITOR;
	}
	else if (exitButton_.isActive()) {
		ng::Main::closeWindow(); // exit
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