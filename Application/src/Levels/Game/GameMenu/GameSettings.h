#pragma once
#include "NGin.h"

class GameSettings : public sf::Drawable {
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);

	void setTextures(const sf::Texture& sliderTexture, const sf::Texture& buttonTexture);
	void setPositionOn(const sf::Sprite& background);
	void setScales(const sf::Vector2f& scale);

	void setupStrings();
	void setupSliders();
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);

	enum RESPONSE {
		NONE = 54,
		BACK
	};
	RESPONSE getResponse() { return response_; }
private:
	ngin::Button backButton_{ "Back To In-Game Menu", { 430, 50 } };
	ngin::Slider soundSlider_{ {335, 31}, {36, 45}, {33, 27} };
	ngin::Slider musicSlider_{ {335, 31}, {36, 45}, {33, 27} };

	sf::Text settingsText_;
	sf::Text soundText_;
	sf::Text musicText_;

	RESPONSE response_;
};