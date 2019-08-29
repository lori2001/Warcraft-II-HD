#pragma once
#include "NGin.h"

class EditorLevel : public ngin::Level {
public:
	EditorLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 80, // avoid samevalue responses
		MAIN_MENU
	};
private:

	void setupUIStyle(const sf::Font& font,
				      const unsigned fontSize,
					  const sf::Color& themeColor);

	std::shared_ptr<sf::Texture> headerTexture_;
	std::shared_ptr<sf::Texture> dropdownTexture_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Font> font_;

	ngin::Button backButton_{ "Back to Menu", { 430, 50 } };

	ngin::Dropdown fileDropdown_{ { 277, 40 } };

	sf::Sprite headerSprite_;
};