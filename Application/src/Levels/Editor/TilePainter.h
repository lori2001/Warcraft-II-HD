#pragma once
#include "SFML/Graphics.hpp"
#include "NGin.h"

class TilePainter : public sf::Drawable {
public:
	// loads the theme's tiles into the tile painter
	void setup();
	void setupUIStyle(const sf::Font& font,
		const unsigned fontSize,
		const sf::Color& themeColor); // callled outside(in editor)

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	
	void setPosition(const sf::Vector2f& position);
	bool isFocused() const { return scrollBox_.isFocused(); }

	int usingTile() const { return usingTile_; }
	void resetUsingTile() { usingTile_ = -1; }
private:
	std::shared_ptr<sf::Texture> themeTexture_;
	std::shared_ptr<sf::Texture> scrollBoxTexture_;

	sf::Text title_;

	// counts the number of empty tiles before the first
	// and helps at indexing the ones used
	std::vector<int> tileIndexes_;
	std::vector<sf::Text> tileIndexTexts_;
	std::vector<sf::RectangleShape> tiles_;
	const float tilesScale_ = 2.15F;
	const int tilesRows_ = 4;
	const sf::Vector2f tilesOffset_ = { 83, 83 };
	const float tilesTopGap_ = 100.0F;
	const float tilesLeftGap_ = 30.0F;

	// Selection 
	const float selectionThickness_ = 2.2F;
	sf::Color selectionColor_;

	// Usage
	int usingTile_ = -1;

	const sf::IntRect backgroundTextureRect_ = { 0, 0, 312, 780 };
	ngin::ScrollBox scrollBox_{ {400, 5500}, {400, 1000}, {200, 35} };
};