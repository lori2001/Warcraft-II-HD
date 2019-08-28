#include "ConfirmDialog.h"

void ConfirmDialog::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	okButton_.handleEvents(event, mouse);
	closeButton_.handleEvents(event, mouse);

	if (okButton_.isActive()) {
		response_ = RESPONSE::OK;
	}
	else if (closeButton_.isActive()) {
		response_ = RESPONSE::CLOSE;
	}
	else {
		response_ = RESPONSE::NONE;
	}
}

void ConfirmDialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);
	target.draw(okButton_);
	target.draw(closeButton_);
	target.draw(text_);
}

void ConfirmDialog::setTextures(const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture)
{
	background_.setTexture(&backgroundTexture);
	
	okButton_.setTexture(buttonTexture);
	closeButton_.setTexture(buttonTexture);
}

void ConfirmDialog::setPosition(const sf::Vector2f& position)
{
	background_.setPosition(position);

	ngin::centerTextInShape(text_, background_, textOffset_);

	float padding = 35.0F;

	closeButton_.setPosition({
		position.x + padding,
		position.y + background_.getGlobalBounds().height - closeButton_.getGlobalBounds().height - padding});

	okButton_.setPosition({
		position.x + background_.getGlobalBounds().width  - okButton_.getGlobalBounds().width  - padding,
		position.y + background_.getGlobalBounds().height - okButton_.getGlobalBounds().height - padding });
}

void ConfirmDialog::setSize(const sf::Vector2f& backgroundSize, const sf::Vector2f& buttonSize)
{
	background_.setSize(backgroundSize);
	okButton_.setSize(buttonSize);
	closeButton_.setSize(buttonSize);

	setPosition(background_.getPosition()); // reposition everything internally
}

void ConfirmDialog::setBackgroundScale(const sf::Vector2f& scale)
{
	background_.setScale(scale);
}

void ConfirmDialog::setButtonsScale(const sf::Vector2f& scale)
{
	closeButton_.setScale(scale);
	okButton_.setScale(scale);
}

void ConfirmDialog::setFont(const sf::Font& font)
{
	okButton_.setFont(font);
	closeButton_.setFont(font);
	text_.setFont(font);

	ngin::centerTextInShape(text_, background_, -25.0F); // Reposition
}

void ConfirmDialog::setCharacterSize(const unsigned characterSize)
{
	setButtonsCharacterSize(characterSize);
	setTextCharacterSize(characterSize);
}

void ConfirmDialog::setButtonsCharacterSize(const unsigned characterSize)
{
	okButton_.setCharacterSize(characterSize);
	closeButton_.setCharacterSize(characterSize);
}

void ConfirmDialog::setTextCharacterSize(const unsigned characterSize)
{
	text_.setCharacterSize(characterSize);

	ngin::centerTextInShape(text_, background_, -25.0F); // Reposition
}

void ConfirmDialog::setSelectColor(const sf::Color& color)
{
	okButton_.setSelectColor(color);
	closeButton_.setSelectColor(color);
}

void ConfirmDialog::setTextColor(const sf::Color& color)
{
	okButton_.setTextColor(color);
	closeButton_.setTextColor(color);
	text_.setFillColor(color);
}

void ConfirmDialog::setTextOffset(const float textOffset)
{
	// changes value
	textOffset_ = textOffset;

	// updates position
	setPosition(background_.getPosition());
}
