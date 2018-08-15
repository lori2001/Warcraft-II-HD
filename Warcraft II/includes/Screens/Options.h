#pragma once
#include "SFML\Graphics.hpp"
#include "../RW/Settings.h"
#include "../RW/Loading.h"
#include "../Others/Gears.h"
#include "../UI/Button.h"
#include "../UI/Dropdown.h"

namespace Screens
{
	class Options : public sf::Drawable
	{
	private:
		sf::Sprite backgroundS;
		Gears gears;

		RW::Loading loading;
		RW::Settings settings;

		UI::Button back{ "Back" };
		UI::Button apply{ "Apply" };

		UI::Dropdown resolution{ 8 };
		UI::Dropdown fullscreen{ 3 };
	public:
		Options()
		{
			backgroundS.setTexture(loading.backgroundT);
			back.setTexture(loading.buttonT, loading.warcraftF);
			apply.setTexture(loading.buttonT, loading.warcraftF);
			resolution.setTexture(loading.dropdownT, loading.warcraftF);
			fullscreen.setTexture(loading.dropdownT, loading.warcraftF);
		}

		bool isActive = false;

		void animateGears() { gears.animate(); }
		void setText(const std::vector<sf::VideoMode> &modes);

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		//setters
		void B0setActive(const bool &active) { back.setActive(active); }
		void B1setActive(const bool &active) { apply.setActive(active); }
		void D0setActive(const unsigned short &i, const bool &active) { resolution.setActive(i, active); }
		void D1setActive(const unsigned short &i, const bool &active) { fullscreen.setActive(i, active); }

		//getters
		const bool B0getActive() { return back.getActive(); }
		const bool B1getActive() { return apply.getActive(); }
		const bool D0getActive(const unsigned short &i) { return resolution.getActive(i); }
		const bool D1getActive(const unsigned short &i) { return fullscreen.getActive(i); }
	};
}