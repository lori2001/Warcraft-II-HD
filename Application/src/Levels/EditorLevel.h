#pragma once
#include "NGin.h"
#include "Levels.h"

#include "Common/GameDetails.h"
#include "Common/Map.h"

#include "Editor/EditableMap.h"
#include "Editor/TilePainter.h"

class EditorLevel : public ng::Level {
public:
	EditorLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	void setupUIStyle(const sf::Font& font,
				      const unsigned fontSize,
					  const sf::Color& themeColor);

	std::shared_ptr<sf::Texture> headerTexture_;
	std::shared_ptr<sf::Texture> dropdownTexture_;
	std::shared_ptr<sf::Texture> leaveButtonTexture_;
	std::shared_ptr<sf::Texture> gridSwitcherTexture_;
	std::shared_ptr<sf::Texture> painterSwitcherTexture_;
	std::shared_ptr<sf::Font> font_;

	// Toolbar
	sf::Sprite headerSprite_;
	ng::Dropdown fileDropdown_{ { 277, 40 } };
	bool toolbarHasFocus_ = false;

	// Navigation
	float editorMoveSpeed_ = 225.0F;
	float editorZoomSpeed_ = 0.2F;
	float editorZoom_ = 2.0F;
	float editorMaxZoom_ = 5.0F;
	float editorMinZoom_ = 0.5F;

	// Editables
	bool mapEditor_;
	EditableMap editableMap_;
		// Tools
		TilePainter tilePainter_;

	// goes back to main menu
	ng::Button backButton_{ "", { 75, 75 } };
	// grid enable/disable
	ng::Switcher gridSwitcher_ { { 75, 75 } };
	// tilePainter enable/disable
	ng::Switcher tilePainterSwitcher_{ { 75, 75 } };
};