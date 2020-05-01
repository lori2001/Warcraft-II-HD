#pragma once
#include "SFML/Graphics.hpp"
#include "NGin.h"

#include "SettingsFile.h"
#include "MapFile.h"

#include "Style.h"
#include "EditorMenu.h"

#include "Painter.h"

class TilePainter : public Painter {
public:
	TilePainter();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isFocused() const { return scrollBox_.isFocused(); }
	int getChoosen() const { return tileNumbers_[choosenTileIndex_]; }
	bool getChoosenHasChanged() const { return choosenHasChanged_; }
	sf::IntRect getChoosenTextureRect() const;
private:

	ng::TexturePtr themeTexture_ = NG_TEXTURE_SPTR(MapFile::getThemeLocation()); // textue of map theme
	ng::FontPtr secondaryFont_ = NG_FONT_SPTR(location::SECONDARY_FONT);

	sf::Text title_{ "Tile Painter", *secondaryFont_, 40 };

	// counts the number of empty tiles before the first
	// and helps at indexing the ones used
	std::vector<int> tileNumbers_;
	std::vector<sf::Text> tileIndexTexts_;
	std::vector<sf::RectangleShape> tiles_;
	const float tilesScale_ = 2.15F;
	const int tilesRows_ = 4;
	const sf::Vector2f tilesOffset_ = { 83, 83 };
	const float tilesTopGap_ = 100.0F;
	const float tilesLeftGap_ = 30.0F;

	// Selection 
	const float selectionThickness_ = 2.2F;

	// Usage
	int choosenTileIndex_ = 0; // the one that you paint with
	bool choosenHasChanged_ = false;

	int selectedTileIndex_ = 0; // the one that is selected

	const sf::IntRect backgroundTextureRect_ = { 0, 0, 312, 780 };
	ng::ScrollBox scrollBox_{
		{400, 5500}, // inside size
		NG_TEXTURE_SPTR(location::SCROLLBOX),
		{400, 1000}, // outside size
		{200, 35} }; // button size

	const sf::Vector2f scrollBoxPosition =
	{
		 MAIN_VIEW_WIDTH - scrollBox_.getOutsideSize().x,
		 EditorMenu::menuHeightPx
	};
};
