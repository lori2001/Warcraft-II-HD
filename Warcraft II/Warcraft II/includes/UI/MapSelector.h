#pragma once
#include <math.h>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "..\RW\MapReader.h"

//TODO: Fix the texture bleeding once and for all

namespace UI
{
	class MapSelector : public sf::Drawable, public sf::Transformable
	{ //Transformable only affects the map itself (not the container)
	private:
		//basic map
		const int tilesize = 32; //size of 1 tile
		const sf::Vector2f minimapsize{ 328,284 }; //size of the minimap (exactly fits the in-game UI)
		sf::Vector2i tilessize{ 0, 0 }; //number of tiles x and y

		sf::VertexArray tilesV;
		sf::Texture tilesT; // the texture used by the map
		sf::Texture summertilesT;
		sf::Texture wastelandtilesT;
		sf::Texture wintertilesT;

		sf::Vector2f scale; // holds the last scale inputed in set scale

		//container
		sf::Vector2f containersize{ 418, 297 };
		sf::Vector2f buttonsize{ 40, 297 };

		sf::RectangleShape rightbutton{ buttonsize };
		sf::RectangleShape leftbutton{ buttonsize };
		sf::RectangleShape container{ containersize };

		bool islSelected = false;
		bool isrSelected = false;
		bool islActive = false;
		bool isrActive = false;
	public:
		MapSelector()
		{
			container.setOrigin(containersize.x / 2, containersize.y / 2);

			leftbutton.setOrigin(buttonsize.x / 2, buttonsize.y / 2);
			leftbutton.setFillColor(sf::Color::Transparent);
			leftbutton.setOutlineColor(sf::Color::Yellow);
			leftbutton.setOutlineThickness(-2);

			rightbutton.setOrigin(buttonsize.x / 2, buttonsize.y / 2);
			rightbutton.setFillColor(sf::Color::Transparent);
			rightbutton.setOutlineColor(sf::Color::Yellow);
			rightbutton.setOutlineThickness(-2);
		}
		//used to move minimap with view and interface (in case of in-game minimap only)
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event & event, sf::Sound & pressbutton);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &summertilesT, const sf::Texture &wastelandtilesT, const sf::Texture &wintertilesT, const sf::Texture & mapcontainerT);
		void setTiles(const RW::MapReader &mapreader);
		void setScale(const sf::Vector2f &scale);
		void setPosition(sf::Vector2f position);
		void setlActive(bool lactive) { islActive = lactive; }
		void setrActive(bool ractive) { isrActive = ractive; }

		//getters
		//returns the size of the currently displayed map right now on screen
		sf::Vector2f getScaledSize() const { return sf::Vector2f(getSize().x * Transformable::getScale().x, getSize().y * Transformable::getScale().y); }
		sf::Vector2f getContScale() const { return scale; }
		//sf::Vector2f getMinimapSize() const { return sf::Vector2f(minimapsize.x, minimapsize.y); }
		sf::Vector2f getSize() const { return sf::Vector2f(float(tilessize.x * tilesize), float(tilessize.y * tilesize)); }
		bool getlActive() const { return islActive; }
		bool getrActive() const { return isrActive; }
	};
}