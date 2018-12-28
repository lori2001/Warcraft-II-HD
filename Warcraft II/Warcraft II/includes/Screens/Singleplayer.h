#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Settings.h"
#include "..\RW\Loading.h"
#include "..\RW\MapReader.h"
#include "..\Others\Players.h"
#include "..\UI\Button.h"
#include "..\UI\Dropdown.h"
#include "..\UI\TextHolder.h"
#include "..\UI\Switch.h"
#include "..\UI\MapSelector.h"

namespace Screens
{
	class Singleplayer : public sf::Drawable
	{
	private:
		sf::Sprite backgroundS; //holds background texture

		RW::Loading loading;
		RW::Settings settings;

		Players players;

		UI::Button back{ "Back" }; // back button (sends to mainmenu)
		UI::Button play{ "Play" }; // starts game

		sf::Text player{"Player:", loading.warcraftF, 20 }; // holds text "Player:"
		UI::TextHolder name{ "Name" }; // Holds the name which may be changed

		// 3 dropdowns which hold players details
		UI::Dropdown playerrace{ 4 , "Race"};
		UI::Dropdown playerteam{ 13, "Team"};
		UI::Dropdown playercolor{ 13, "Color" };

		//holds ai's possible colors
		sf::Color colors[12]{ sf::Color(255,0,0), //1.red 
							  sf::Color(0,255,0), //2.green
							  sf::Color(0,0,255), //3.blue
							  sf::Color(255,69,0), //4.orange
							  sf::Color(255,255,0), //5.yellow
							  sf::Color(0,255,255), //6.cyan
							  sf::Color(128,0,128), //7.purple
							  sf::Color(255,255,255), //8.white
							  sf::Color(139,69,19), //9.brown
							  sf::Color(128,128,128), //10.grey
							  sf::Color(255,20,147), //11.pink
							  sf::Color(0,0,0) }; //12.black

		//changes the number of ai's deployed
		UI::Dropdown ais{ 12,sf::Vector2f(69,54) };

		//holds ai's details
		UI::Dropdown aidifficulty[11]{ 4,4,4,4,4,4,4,4,4,4,4 };
		UI::Dropdown airace[11]{ 4,4,4,4,4,4,4,4,4,4,4 };
		UI::Dropdown aiteam[11]{ 13,13,13,13,13,13,13,13,13,13,13 };
		UI::Dropdown aicolor[11]{ 13,13,13,13,13,13,13,13,13,13,13 };

		UI::Switch relativecolors{ 0, "Relative Team Colors ON" };

		UI::MapSelector mapselector;
	public:
		Singleplayer()
		{
			/*sets all the right textures*/
			backgroundS.setTexture(loading.spbackgroundT);
			back.setTexture(loading.buttonT, loading.warcraftF);
			play.setTexture(loading.buttonT, loading.warcraftF);
			name.setTexture(loading.textholderT, loading.warcraftF);
			playerrace.setTexture(loading.dropdownT, loading.warcraftF);
			playerteam.setTexture(loading.dropdownT, loading.warcraftF);
			playercolor.setTexture(loading.dropdownT, loading.warcraftF);
			ais.setTexture(loading.smalldropdownT, loading.warcraftF);

			for (unsigned int i = 0; i < 11; i++)
			{
				aidifficulty[i].setTexture(loading.dropdownT, loading.warcraftF);
				airace[i].setTexture(loading.dropdownT, loading.warcraftF);
				aiteam[i].setTexture(loading.dropdownT, loading.warcraftF);
				aicolor[i].setTexture(loading.dropdownT, loading.warcraftF);
			}

			relativecolors.setTexture(loading.switchT, loading.normalF);
			mapselector.setTexture(loading.summertilesT,loading.wastelandtilesT,loading.wintertilesT,loading.mapcontainerT);
			/******************************/

			player.setFillColor(sf::Color::Yellow); //set color of yellow
			this->player.setOrigin(this->player.getLocalBounds().left + this->player.getLocalBounds().width / 2.0f,
				this->player.getLocalBounds().top + this->player.getLocalBounds().height / 2.0f); //centers text

			TH0setString(settings.getName()); //sets textholders string to the string found in settings file
		}

		bool isActive = false;

		void setTransform();
		void handleInput(const sf::Event & event, const sf::Vector2f & mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setText();
		void setColors();
		void setColorsInactive(const bool &inactive);

		//setters
		void S0setActive(const bool &active) { relativecolors.setActive(active); }
		void TH0setChanged(const bool &changed) { name.setChanged(changed); }
		void TH0setString(const std::string & text) { name.setString(text); }
		void D0setActive(const unsigned int &i, const bool &active) { playerrace.setActive(i, active); }
		void D1setActive(const unsigned int &i, const bool &active) { playerteam.setActive(i, active); }
		void D2setActive(const unsigned int &i, const bool &active) { playercolor.setActive(i, active); }
		void D3setActive(const unsigned int &i, const bool &active) { ais.setActive(i, active); }
		void D4setActive(const unsigned int &i, const unsigned int &j, const bool &active) { aidifficulty[i].setActive(j, active); }
		void D5setActive(const unsigned int &i, const unsigned int &j, const bool &active) { airace[i].setActive(j, active); }
		void D6setActive(const unsigned int &i, const unsigned int &j, const bool &active) { aiteam[i].setActive(j, active); }
		void D7setActive(const unsigned int &i, const unsigned int &j, const bool &active) { aicolor[i].setActive(j, active); }
		void M0setTiles(const RW::MapReader & mapreader) { mapselector.setTiles(mapreader); }
		void M0setlActive(const bool &active) { mapselector.setlActive(active); }
		void M0setrActive(const bool &active) { mapselector.setrActive(active); }

		//getters
		bool S0getActive() const { return relativecolors.getActive(); }
		bool B0getActive() { return back.hasBeenActivated(); }
		bool B1getActive() { return play.hasBeenActivated(); }
		bool TH0getChanged() const { return name.getChanged(); }
		std::string TH0getString() const { return name.getString(); }
		bool D0getActive(const unsigned int &i) const { return playerrace.getActive(i); }
		bool D1getActive(const unsigned int &i) const { return playerteam.getActive(i); }
		bool D2getActive(const unsigned int &i) const { return playercolor.getActive(i); }
		bool D3getActive(const unsigned int &i) const { return ais.getActive(i); }
		bool D4getActive(const unsigned int &i, const unsigned int &j) const { return aidifficulty[i].getActive(j); }
		bool D5getActive(const unsigned int &i, const unsigned int &j) const { return airace[i].getActive(j); }
		bool D6getActive(const unsigned int &i, const unsigned int &j) const { return aiteam[i].getActive(j); }
		bool D7getActive(const unsigned int &i, const unsigned int &j) const { return aicolor[i].getActive(j); }
		bool M0getlActive() { return mapselector.getlActive(); }
		bool M0getrActive() { return mapselector.getrActive(); }
	};
}