#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Settings.h"
#include "..\RW\Loading.h"
#include "..\UI\Button.h"

namespace Screens
{
	class MainMenu : public sf::Drawable
	{
	private:
		sf::Sprite backgroundS;

		RW::Loading loading;
		RW::Settings settings;

		UI::Button singleplayer{ "Single Player" };
		UI::Button multiplayer{ "Multi Player" };
		UI::Button options{ "Options" };
		UI::Button exit{ "Exit Game" };
	public:
		MainMenu()
		{
			backgroundS.setTexture(loading.menubackgroundT);
			singleplayer.setTexture(loading.buttonT, loading.warcraftF);
			multiplayer.setTexture(loading.buttonT, loading.warcraftF);
			options.setTexture(loading.buttonT, loading.warcraftF);
			exit.setTexture(loading.buttonT, loading.warcraftF);
		}

		bool isActive = false;

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//getters
		bool B0getActive() { return singleplayer.hasBeenActivated(); }
		bool B1getActive() { return multiplayer.hasBeenActivated(); }
		bool B2getActive() { return options.hasBeenActivated(); }
		bool B3getActive() { return exit.hasBeenActivated(); }
	};
}