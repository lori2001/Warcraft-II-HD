#pragma once
#include "SFML\Graphics.hpp"
#include "../RW/Settings.h"
#include "../RW/Loading.h"
#include "../Others/Gears.h"
#include "../UI/Button.h"
#include "../UI/Dropdown.h"
#include "../UI/Slider.h"

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

		UI::Slider music;
		UI::Slider soundfx;
	public:
		Options()
		{
			backgroundS.setTexture(loading.backgroundT);
			back.setTexture(loading.buttonT, loading.warcraftF);
			apply.setTexture(loading.buttonT, loading.warcraftF);
			resolution.setTexture(loading.dropdownT, loading.warcraftF);
			fullscreen.setTexture(loading.dropdownT, loading.warcraftF);
			music.setTexture(loading.sliderT, loading.sliderbuttonT, loading.warcraftF);
			soundfx.setTexture(loading.sliderT, loading.sliderbuttonT, loading.warcraftF);
		}

		bool isActive = false;

		void animateGears() { gears.animate(); }
		void setText(const std::vector<sf::VideoMode> &modes);

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		//setters
		void S0setLevel(const unsigned int &level) { music.setLevel(level); }
		void S0setActive(const bool &active) { music.setActive(active); }
		void S1setLevel(const unsigned int &level) { soundfx.setLevel(level); }
		void S1setActive(const bool &active) { soundfx.setActive(active); }
		void D0setActive(const unsigned int &i, const bool &active) { resolution.setActive(i, active); }
		void D1setActive(const unsigned int &i, const bool &active) { fullscreen.setActive(i, active); }

		//getters
		const unsigned int S0getLevel() { return music.getLevel(); }
		const bool S0getActive() { return music.getActive(); }
		const unsigned int S1getLevel() { return soundfx.getLevel(); }
		const bool S1getActive() { return soundfx.getActive(); }
		const bool B0getActive() { return back.hasBeenActivated(); }
		const bool B1getActive() { return apply.hasBeenActivated(); }
		const bool D0getActive(const unsigned int &i) { return resolution.getActive(i); }
		const bool D1getActive(const unsigned int &i) { return fullscreen.getActive(i); }
	};
}
