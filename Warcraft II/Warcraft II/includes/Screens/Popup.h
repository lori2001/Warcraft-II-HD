#pragma once
#include <assert.h>
#include "SFML\Graphics.hpp"
#include "..\RW\Settings.h"
#include "..\RW\Loading.h"
#include "..\UI\Button.h"

namespace Screens
{
	class Popup : public sf::Drawable
	{ //TODO: Revise unnecessary sf::Text dynamic pointer
	private:
		const sf::Vector2f size{ 700,220 };
		sf::RectangleShape popupS{ size }; //will hold popup background

		RW::Loading loading; //used only for button and font but NOT for background

		sf::Text *descriptions;
		unsigned int descriptionsnr;

		sf::Text countdown;

		UI::Button cancel{ "Cancel" };
		UI::Button ok{ "OK" };

		// needed for countdown
		sf::Clock resetclock;
		float resettimer = 0;
		float resetlimit = 10;
	public:
		Popup(const unsigned int &descriptionsnr)
		{
			//sets the number of descriptions desired
			descriptions = new sf::Text[descriptionsnr];
			this->descriptionsnr = descriptionsnr;

			//default fonts and textures
			popupS.setTexture(&loading.popupT);
			cancel.setTexture(loading.buttonT, loading.warcraftF);
			ok.setTexture(loading.buttonT, loading.warcraftF);
			countdown.setFont(loading.normalF);

			//default font colors
			countdown.setFillColor(sf::Color::Yellow);

			for (unsigned int i = 0; i < descriptionsnr; i++) {
				descriptions[i].setFont(loading.normalF);
				descriptions[i].setFillColor(sf::Color::Yellow);
				descriptions[i].setPosition({0,0});
			}

			//set backgrounds origin to center
			popupS.setOrigin(size.x / 2, size.y / 2);

			this->setScale({ 1, 1 }); //sets default scales
		}
		~Popup()
		{
			delete[] descriptions;
		}

		bool isActive = false;
		bool countdownOver = false;

		void animateCountdown();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setPosition(const sf::Vector2f &position);
		void setScale(const sf::Vector2f &scale);
		void setDescription(const int &i, const std::string &text);
		void setDescriptionPos(const int &i, const sf::Vector2f &relativepos);
		/*gets values between 1 and 0. THROWS ERRORS if not used properly
		ex. 0,0 means top-left corner of popup window, and 1,1 means bottom-right*/
		void setCountdownPos(const sf::Vector2f &relativepos);
		void B0setActive(const bool &active) { cancel.setActive(active); }
		void B1setActive(const bool &active) { ok.setActive(active); }
		void setResetLimit(const float &resetlimit) { this->resetlimit = resetlimit; }
		void restartTimining() { resetclock.restart();
								 resettimer = 0; };

		//getters
		bool B0getActive() const { return cancel.getActive(); }
		bool B1getActive() const { return ok.getActive(); }
		float getResetLimit() const { return resetlimit; }
		float getResetTimer() const { return resettimer; }
	};
}
