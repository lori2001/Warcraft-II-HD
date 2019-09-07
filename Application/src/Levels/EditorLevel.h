#pragma once
#include "NGin.h"
#include "Common/GameDetails.h"
#include "Common/Map.h"

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
	std::shared_ptr<sf::Texture> leaveButtonTexture_;
	std::shared_ptr<sf::Font> font_;

	// Toolbar
	sf::Sprite headerSprite_;
	ngin::Dropdown fileDropdown_{ { 277, 40 } };

	// Types
	bool mapEditor_;
	Map map_;

	// Back
	ngin::Button backButton_{ "", { 50, 50 } };
};