#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Settings.h"
#include "..\RW\Loading.h"
#include "..\UI\Button.h"

namespace Screens
{
	class Multiplayer : public sf::Drawable
	{
	private:
		sf::Sprite backgroundS;

		RW::Loading loading;
		RW::Settings settings;

		UI::Button back{ "Back" };
	public:
		Multiplayer()
		{
			backgroundS.setTexture(loading.inworkT);
			back.setTexture(loading.buttonT, loading.warcraftF);
		}

		bool isActive = false;

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void B0setActive(const bool &active) { back.setActive(active); }

		//getters
		const bool B0getActive() { return back.getActive(); }
	};
}