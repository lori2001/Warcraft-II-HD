#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Button.h"
#include "..\RW\MapReader.h"

//TODO: Fix the texture bleeding once and for all

namespace UI
{
	class MapSelector : public sf::Drawable, public sf::Transformable
	{ //Transformable only affects the map itself (not the container)
	private:
		const int tilesize = 32; //size of one tile
		const sf::Vector2f minimapsize{ 328,284 }; //size of the minimap in pixels (exactly fits the in-game UI)
		sf::Vector2i nroftiles{ 0, 0 }; //number of tiles x and y

		sf::VertexArray tilesV; //vertex to be displayed
		sf::Texture tilesT; // the texture used by the map

		//textures for each theme
		sf::Texture summertilesT;
		sf::Texture wastelandtilesT;
		sf::Texture wintertilesT;

		//container and button sizes
		sf::Vector2f containersize{ 418, 297 };
		sf::Vector2f buttonsize{ 40, 297 };

		//container and button rectagles
		sf::RectangleShape container{ containersize };
		UI::Button rightbutton{ buttonsize };
		UI::Button leftbutton{ buttonsize };
	public:
		MapSelector()
		{
			container.setOrigin(containersize.x / 2, containersize.y / 2);

			rightbutton.setFillColor(sf::Color::Transparent);
			leftbutton.setFillColor(sf::Color::Transparent);
		}
		void checkSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event & event, sf::Sound & pressbutton);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &summertilesT, const sf::Texture &wastelandtilesT, const sf::Texture &wintertilesT, const sf::Texture & mapcontainerT);
		void setTiles(const RW::MapReader &mapreader);
		void setPosition(sf::Vector2f position);

		//getters
		//returns the size of the currently displayed map right now on screen
		sf::Vector2f getScaledSize() const { return sf::Vector2f(getSize().x * Transformable::getScale().x, getSize().y * Transformable::getScale().y); }
		//sf::Vector2f getMinimapSize() const { return sf::Vector2f(minimapsize.x, minimapsize.y); }
		sf::Vector2f getSize() const { return sf::Vector2f(float(nroftiles.x * tilesize), float(nroftiles.y * tilesize)); }
		bool getlActive() { return leftbutton.hasBeenActivated(); }
		bool getrActive() { return rightbutton.hasBeenActivated(); }
	};
}