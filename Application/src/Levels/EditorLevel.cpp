#include "EditorLevel.h"

void EditorLevel::setup()
{
	buttonTexture_ = ngin::Resources::AcquireTexture("images/ui/button.png");
	font_ = ngin::Resources::AcquireFont("fonts/normal.ttf");

	backButton_.setTexture(*buttonTexture_);

	setupUIStyle(*font_, 40, sf::Color::Yellow);
}

void EditorLevel::handleEvents(const sf::Event& event)
{
	backButton_.handleEvents(event, ngin::Cursor::getPosition());

	if (backButton_.isActive()) {
		response_ = RESPONSE::BACK;
	}
	else {
		response_ = RESPONSE::NONE;
	}
}

void EditorLevel::update()
{
}

void EditorLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backButton_);
}

void EditorLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setTextColor(themeColor);
	backButton_.setSelectColor(themeColor);
}
