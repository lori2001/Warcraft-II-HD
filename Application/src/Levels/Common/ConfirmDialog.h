#pragma once
#include "Ngin.h"

class ConfirmDialog : public sf::Drawable {
public:
	ConfirmDialog() : ConfirmDialog({ 700, 220 }) {}
	ConfirmDialog(const sf::Vector2f& backgroundSize)
		: ConfirmDialog(backgroundSize, { 430, 50 }) {}
	ConfirmDialog(const sf::Vector2f& backgroundSize, const sf::Vector2f& buttonSize) {
		okButton_.setString("Ok");
		closeButton_.setString("Close");

		setBackgroundScale({ 1.3F, 1.3F});
		setButtonsScale({ 0.65F, 0.95F});

		setCharacterSize(35);
		setSize(backgroundSize, buttonSize);
	}

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 0,
		OK,
		CLOSE
	};

	void setTextures(const sf::Texture& backgroundTexture, const sf::Texture& buttonTexture);
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& backgroundSize, const sf::Vector2f& buttonSize);
	void setBackgroundScale(const sf::Vector2f& scale);
	void setButtonsScale(const sf::Vector2f& scale);
	void setFont(const sf::Font& font);
	void setString(const std::string& string) { text_.setString(string); }
	void setCharacterSize(const unsigned characterSize);
	void setButtonsCharacterSize(const unsigned characterSize);
	void setTextCharacterSize(const unsigned characterSize);
	void setSelectColor(const sf::Color& color);
	void setTextColor(const sf::Color& color);
	void setTextOffset(const float textOffset);

	RESPONSE getResponse() const { return response_; }
	sf::Vector2f getSize() const { return background_.getSize(); }
	sf::FloatRect getGlobalBounds() const { return background_.getGlobalBounds(); }

private:
	sf::RectangleShape background_;
	sf::Text text_;

	ngin::Button okButton_;
	ngin::Button closeButton_;

	// Properties
	float textOffset_ = -25.0F; // offset in Y axis
	
	// return value
	RESPONSE response_;
};