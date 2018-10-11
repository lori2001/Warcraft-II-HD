#pragma once
#include "SFML\Graphics.hpp"
#include "..\Window.h"
#include "..\RW\Loading.h"
#include "..\RW\FileReader.h"
#include "..\RW\MapReader.h"
#include "..\Display\Map.h"

//TODO: Resize when panels undocked

namespace Sections 
{
	class MainView : public sf::Drawable
	{
	private:
		RW::Loading loading;

		RW::MapReader mapreader;
		RW::FileReader filereader;

		Display::Map map;
	public:
		bool isIntialized = false;

		void readFile();
		void setTransform(const sf::Vector2f & scale);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}