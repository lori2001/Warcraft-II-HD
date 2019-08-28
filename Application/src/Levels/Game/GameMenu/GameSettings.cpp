#include "GameSettings.h"

void GameSettings::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(settingsText_);
	
	target.draw(backButton_);

	target.draw(soundSlider_);
	target.draw(soundText_);

	target.draw(musicSlider_);
	target.draw(musicText_);
}

void GameSettings::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	backButton_ .handleEvents(event, mouse);
	soundSlider_.handleEvents(event, mouse);
	musicSlider_.handleEvents(event, mouse);

	ngin::Audio::setSoundVolume(soundSlider_.getLevel());
	ngin::Audio::setMusicVolume(musicSlider_.getLevel());

	if (backButton_.isActive())
		response_ = RESPONSE::BACK;
	else
		response_ = RESPONSE::NONE;
}

void GameSettings::setTextures(const sf::Texture& sliderTexture, const sf::Texture& buttonTexture)
{
	backButton_ .setTexture(buttonTexture);
	soundSlider_.setTexture(sliderTexture);
	musicSlider_.setTexture(sliderTexture);
}

void GameSettings::setPositionOn(const sf::Sprite& background)
{
	// background size: 540x780
	backButton_.setPosition({
	background.getGlobalBounds().left + (background.getGlobalBounds().width - backButton_.getGlobalBounds().width) / 2 ,
	background.getGlobalBounds().top + 200 });

	soundSlider_.setPosition({
	background.getGlobalBounds().left + (background.getGlobalBounds().width - soundSlider_.getGlobalBounds().width) / 2 ,
	background.getGlobalBounds().top + 400 });

	musicSlider_.setPosition({
	background.getGlobalBounds().left + (background.getGlobalBounds().width - musicSlider_.getGlobalBounds().width) / 2 ,
	background.getGlobalBounds().top + 550 });

	ngin::centerTextInBounds(soundText_, soundSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(musicText_, musicSlider_.getGlobalBounds(), -47);
	ngin::centerTextInBounds(settingsText_, background.getGlobalBounds(), -300);
}

void GameSettings::setScales(const sf::Vector2f& scale)
{
	backButton_.setScale(scale);
	soundSlider_.setScale(scale);
	musicSlider_.setScale(scale);
}

void GameSettings::setupStrings()
{
	settingsText_.setString("In-Game Settings");
	soundText_.setString("Sound Volume:");
	musicText_.setString("Music Volume:");
}

void GameSettings::setupSliders()
{
	soundSlider_.setLevel(ngin::Audio::getSoundVolume());
	musicSlider_.setLevel(ngin::Audio::getMusicVolume());
}

void GameSettings::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	settingsText_.setFont(font);
	settingsText_.setCharacterSize(static_cast<unsigned>(1.5F * fontSize));
	settingsText_.setFillColor(themeColor);

	soundText_.setFont(font);
	soundText_.setCharacterSize(fontSize);
	soundText_.setFillColor(themeColor);

	musicText_.setFont(font);
	musicText_.setCharacterSize(fontSize);
	musicText_.setFillColor(themeColor);

	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setTextColor(themeColor);
	backButton_.setSelectColor(themeColor);

	soundSlider_.setSelectThickness(2.5F);
	soundSlider_.setSelectColor(themeColor);

	soundSlider_.setSelectThickness(2.5F);
	soundSlider_.setSelectColor(themeColor);
}
