#pragma once
#include "NGin.h"
#include "../Common/Map.h"
#include "../Common/GameDetails.h"

class MapSelector : public ngin::UIElement {
public:
	MapSelector() : MapSelector({ 39, 297 }, { 340, 297 }) {}
	MapSelector(const sf::Vector2f& buttonSize, const sf::Vector2f& containerSize) {
		setSize(buttonSize, containerSize);
		setCharacterSize(30);

		GameDetails::mapFile.scanDir();
		GameDetails::mapFile.read();
		setTitle(GameDetails::mapFile.getMapName());
		map_.setMapFile(GameDetails::mapFile);
		updateMapTransform();
	}

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTexture(const sf::Texture& texture);
	void setTextColor(const sf::Color& color) { mapTitle_.setFillColor(color); }
	void setFont(const sf::Font& font) { mapTitle_.setFont(font); }
	void setCharacterSize(const unsigned characterSize) { mapTitle_.setCharacterSize(characterSize); }
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& buttonSize, const sf::Vector2f& containerSize);
	void setTitle(const std::string& titleString);
	void setSelectColor(const sf::Color& color);
	void setSelectThickness(const float thickness);
	
private:
	void updateMapTransform();

	std::shared_ptr<sf::Texture> texture_;
	sf::RectangleShape container_;
	ngin::Button leftButton_;
	ngin::Button rightButton_;

	sf::Text mapTitle_;
	sf::Vector2f mapPosition_;
	Map map_;
};