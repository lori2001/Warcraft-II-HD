#pragma once
#include "SFML/Graphics.hpp"
#include "NGin.h"

class TilePainter : public sf::Drawable {
public:
	// loads the theme's tiles into the tile painter
	void setup();
	void setupUIStyle(const sf::Font& font,
		const unsigned fontSize,
		const sf::Color& themeColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	
	void setPosition(const sf::Vector2f& position);
	
	// gets the size of the whole toolbar
	sf::Vector2f getSize() const { return background_.getSize(); }
private:
	std::shared_ptr<sf::Texture> themeTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;

	// counts the number of empty tiles before the first
	// and helps at indexing the ones used
	std::vector<int> tileIndexes_;
	std::vector<sf::RectangleShape> tiles_;
	const float tilesScale_ = 1.8F;
	const int tilesRows_ = 5;
	const sf::Vector2f tilesOffset_ = { 70, 70 };
	const float tilesTopGap_ = 85.0F;

	// Selection 
	const float selectionThickness_ = 2.45F;
	const sf::Color selectionColor_ = sf::Color::Yellow;

	sf::RectangleShape background_;
	const sf::Vector2f backgroundSize_ = { 400, 1000 };
	const sf::IntRect backgroundTextureRect_ = { 0, 0, 312, 780 };

	sf::Text titleText_;
	const float titleTextTopGap_ = 40.0F;
};