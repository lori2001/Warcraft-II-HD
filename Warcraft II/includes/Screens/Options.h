#pragma once
#include "SFML\Graphics.hpp"
#include "../RW/Settings.h"
#include "../RW/Loading.h"
#include "../UI/Button.h"

namespace Screens
{
	class Options : public sf::Drawable
	{
	private:
		sf::Sprite backgroundS;

		RW::Loading loading;
		RW::Settings settings;

		UI::Button back{ "Back" };
		UI::Button apply{ "Apply" };

	public:
		Options()
		{
			backgroundS.setTexture(loading.backgroundT);

			back.setTexture(loading.buttonT, loading.warcraftF);
			apply.setTexture(loading.buttonT, loading.warcraftF);
		}

		bool isActive = false;

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		//setters
		void B0setActive(const bool &active) { back.setActive(active); }
		void B1setActive(const bool &active) { apply.setActive(active); }

		//getters
		const bool B0getActive() { return back.getActive(); }
		const bool B1getActive() { return apply.getActive(); }
	};
}
