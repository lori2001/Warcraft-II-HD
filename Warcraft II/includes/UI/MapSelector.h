#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Loading.h"
#include "..\RW\Settings.h"
#include "..\RW\MapReader.h"

namespace UI
{
	class MapSelector : public sf::Drawable, public sf::Transformable
	{ //Transformable only contains the map itself (not the container)
	private:
		//basic map
		const short *tilesize = new const short{ 32 }; //size of 1 tile
		const sf::Vector2f *minimapsize = new const sf::Vector2f{ 328,284 }; //size of the minimap (exactly fits the in-game UI)
		sf::Vector2i *tilessize = new sf::Vector2i{ 0, 0 }; //number of tiles x and y

		sf::VertexArray *tilesV = new sf::VertexArray;
		sf::Texture *tilesT = new sf::Texture; // the texture used by the map
		sf::Texture *summertilesT = new sf::Texture;
		sf::Texture *wastelandtilesT = new sf::Texture;
		sf::Texture *wintertilesT = new sf::Texture;

		sf::Vector2f *scale = new sf::Vector2f; // holds the last scale inputed in set scale

		//container
		sf::Vector2f *containersize = new sf::Vector2f(418, 297);
		sf::Vector2f *buttonsize = new sf::Vector2f(40, 297);

		sf::RectangleShape *rightbutton = new sf::RectangleShape(*buttonsize);
		sf::RectangleShape *leftbutton = new sf::RectangleShape(*buttonsize);
		sf::RectangleShape *container = new sf::RectangleShape(*containersize);

		bool *islSelected = new bool{ false };
		bool *isrSelected = new bool{ false };
		bool *islActive = new bool{ false };
		bool *isrActive = new bool{ false };
	public:
		MapSelector()
		{
			container->setOrigin(containersize->x / 2, containersize->y / 2);

			leftbutton->setOrigin(buttonsize->x / 2, buttonsize->y / 2);
			leftbutton->setFillColor(sf::Color::Transparent);
			leftbutton->setOutlineColor(sf::Color::Yellow);
			leftbutton->setOutlineThickness(-2);

			rightbutton->setOrigin(buttonsize->x / 2, buttonsize->y / 2);
			rightbutton->setFillColor(sf::Color::Transparent);
			rightbutton->setOutlineColor(sf::Color::Yellow);
			rightbutton->setOutlineThickness(-2);
		}
		~MapSelector()
		{
			//basic map
			delete tilesize;
			delete minimapsize;
			delete tilessize;
			delete tilesV;
			delete tilesT;
			delete summertilesT;
			delete wastelandtilesT;
			delete wintertilesT;

			//container
			delete containersize;
			delete buttonsize;
			delete rightbutton;
			delete leftbutton;
			delete container;
			delete islSelected;
			delete isrSelected;
			delete islActive;
			delete isrActive;
		}
		//used to move minimap with view and interface (in case of in-game minimap only)
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event & event, sf::Sound & pressbutton);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &summertilesT, const sf::Texture &wastelandtilesT, const sf::Texture &wintertilesT, const sf::Texture & mapcontainerT);
		void setTiles(const RW::MapReader &mapreader);
		void setScale(const sf::Vector2f &scale);
		void setPosition(const sf::Vector2f & position);
		void setlActive(bool lactive) { *islActive = lactive; }
		void setrActive(bool ractive) { *isrActive = ractive; }

		//getters
		//returns the size of the currently displayed map right now on screen
		sf::Vector2f getScaledSize() const
		{
			if (tilessize->x > tilessize->y)
				return sf::Vector2f(tilessize->x * (*tilesize) * ((minimapsize->x * scale->x) / (tilessize->x * (*tilesize))), tilessize->y * (*tilesize) * ((minimapsize->x * scale->x) / (tilessize->x * (*tilesize))));
			else
				return sf::Vector2f(tilessize->x * (*tilesize) * ((minimapsize->y * scale->y) / (tilessize->y * (*tilesize))), tilessize->y * (*tilesize) * ((minimapsize->y * scale->y) / (tilessize->y * (*tilesize))));
		}
		sf::Vector2f getScale() const { return *scale; }
		//returns the scaledsize of the currently displayed minimap
		sf::Vector2f getMinimapSize() const { return sf::Vector2f(minimapsize->x * scale->x, minimapsize->y * scale->y); }
		sf::Vector2f getSize() const { return sf::Vector2f((getScaledSize().x / Transformable::getScale().x), (getScaledSize().y / Transformable::getScale().y)); }
		bool getlActive() const { return *islActive; }
		bool getrActive() const { return *isrActive; }
	};
}