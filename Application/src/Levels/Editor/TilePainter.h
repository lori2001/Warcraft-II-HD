#pragma once
#include "SFML/Graphics.hpp"
#include "NGin.h"

class TilePainter : public sf::Drawable {
public:
	// loads the theme's tiles into the tile painter
	void setupWithTheme(const std::string& themeLocation, const sf::Vector2f& tileSize);
	void setupUIStyle(const sf::Font& font,
		const unsigned fontSize,
		const sf::Color& themeColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	
	void setPosition(const sf::Vector2f& position);
	
	// gets the size of the whole toolbar
	sf::Vector2f getSize() const { return backgroundShape_.getSize(); }
private:
	std::shared_ptr<sf::Texture> backgroundTexture_;

	sf::RectangleShape backgroundShape_;
	sf::Text titleText_;
};