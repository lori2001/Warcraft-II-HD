#pragma once
#include "NGin.h"

#include "../../Style.h"

#include "../Common/Map.h"
#include "../../Files/GameDetailsFile.h"

class MapSelector : private GameDetailsFile, public sf::Drawable {
public:
	MapSelector(const sf::Vector2f& position, const sf::Vector2f& scale);

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	void setupNewMap();

	const ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);
	const unsigned fontSize_ = 30;

	const ng::TexturePtr texture_ = NG_TEXTURE_SPTR( location::MAP_SELECTOR );
	sf::RectangleShape container_;

	ng::Button leftButton_{
		{},{},{},{},
		{ size::MAP_SELECTOR_BUTTON_WIDTH, size::MAP_SELECTOR_BUTTON_HEIGHT },
			texture_,
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ 0, 0 } // position depends on constructor
	};
	ng::Button rightButton_{
		"Settings",
		leftButton_,
		{ 0, 0 } // position depends on constructor
	};

	sf::Text mapTitle_{ "Unknown" , *primaryFont_, fontSize_ };

	sf::Vector2f mapPosition_;
};
