#pragma once
#include "NGin.h"

#include "Common/GameDetails.h"
#include "Common/Map.h"

#include "Editor/EditableMap.h"

class EditorLevel : public ngin::Level {
public:
	EditorLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum RESPONSE {
		NONE = 80, // avoid same-value responses
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
	EditableMap editableMap_;

	float editorMoveSpeed_ = 225.0F;
	float editorZoomSpeed_ = 0.2F;
	float editorZoom_ = 2.0F;
	float editorMaxZoom_ = 5.0F;
	float editorMinZoom_ = 0.5F;

	// Back
	ngin::Button backButton_{ "", { 75, 75 } };
};