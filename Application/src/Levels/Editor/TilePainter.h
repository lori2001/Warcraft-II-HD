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

private:
	std::shared_ptr<sf::Texture> themeTexture_;
	std::shared_ptr<sf::Texture> scrollBoxTexture_;

	// counts the number of empty tiles before the first
	// and helps at indexing the ones used
	std::vector<int> tileIndexes_;
	std::vector<sf::RectangleShape> tiles_;
	const float tilesScale_ = 2.0F;
	const int tilesRows_ = 4;
	const sf::Vector2f tilesOffset_ = { 80, 80 };
	const float tilesTopGap_ = 85.0F;
	const float tilesLeftGap_ = 30.0F;

	// Selection 
	const float selectionThickness_ = 2.5F;
	sf::Color selectionColor_;

	const sf::IntRect backgroundTextureRect_ = { 0, 0, 312, 780 };
	ngin::ScrollBox scrollBox_{ {400, 5500}, {400, 1000}, {200, 35} };
};