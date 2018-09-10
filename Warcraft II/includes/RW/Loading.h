#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Settings.h"

namespace RW
{
	class Loading
	{
	private:
		static sf::Texture loadingscreenT;
		static sf::Sprite loadingscreenS;

		static sf::RectangleShape progressbar;
		static sf::RectangleShape progressbg;
		static const int progressperfile; // holds the number of files before loading
		static int nroffiles; // counts the number of files loaded while loading

		static sf::SoundBuffer pressbuttonSB;

		static void animateBar(sf::RenderWindow & window);
		static void loadFile(sf::Texture & texture, const std::string & from, sf::RenderWindow & window);
		static void loadFile(sf::Font & font, const std::string & from, sf::RenderWindow & window);
		static void loadFile(sf::Music & music, const std::string & from, sf::RenderWindow & window);
		static void loadFile(sf::SoundBuffer & soundbuffer, const std::string & from, sf::RenderWindow & window);
	public:
		static sf::Sound pressbutton;

		static sf::Music menusong;
		static sf::Music orcsong;
		static sf::Music humansong;

		static sf::Texture backgroundT;
		static sf::Texture menubackgroundT;
		static sf::Texture spbackgroundT;
		static sf::Texture inworkT;
		static sf::Texture interfaceT;

		static sf::Texture topgearsT[20];
		static sf::Texture botgearsT[20];

		static sf::Texture popupT;

		static sf::Texture buttonT;

		static sf::Texture sliderT;
		static sf::Texture sliderbuttonT;

		static sf::Texture dropdownT;

		static sf::Texture smalldropdownT;

		static sf::Texture textholderT;

		static sf::Texture switchT;

		static sf::Texture mapcontainerT;

		static sf::Texture cursorT;

		static sf::Texture summertilesT;
		static sf::Texture wastelandtilesT;
		static sf::Texture wintertilesT;

		static sf::Texture ballistaT;
		static sf::Texture battleshipT;
		static sf::Texture catapultT;
		static sf::Texture corpsesT;
		static sf::Texture crittersT;
		static sf::Texture daemonT;
		static sf::Texture deathknightT;
		static sf::Texture dragonT;
		static sf::Texture dwarvendemolitionsquadT;
		static sf::Texture elvenarcherT;
		static sf::Texture elvendestroyerT;
		static sf::Texture footmanT;
		static sf::Texture giantturtleT;
		static sf::Texture gnomishflyingmachineT;
		static sf::Texture gnomishsubmarineT;
		static sf::Texture goblinsappersT;
		static sf::Texture goblinzeppelinT;
		static sf::Texture gruntT;
		static sf::Texture gryphonriderT;
		static sf::Texture humanbuildingssummerT;
		static sf::Texture humanbuildingswinterT;
		static sf::Texture humanoiltankerT;
		static sf::Texture humantransportT;
		static sf::Texture iconsT;
		static sf::Texture knightT;
		static sf::Texture mageT;
		static sf::Texture magicandmisslesT;
		static sf::Texture miscT;
		static sf::Texture ogrejuggernautT;
		static sf::Texture ogreT;
		static sf::Texture orcbuildingssummerT;
		static sf::Texture orcbuildingswinterT;
		static sf::Texture orcoiltankerT;
		static sf::Texture orctransportT;
		static sf::Texture peasantT;
		static sf::Texture peonT;
		static sf::Texture skeletonT;
		static sf::Texture trollaxethrowerT;
		static sf::Texture trolldestroyerT;

		static sf::Font warcraftF;
		static sf::Font normalF;

		static void setMusicVolume(const unsigned short &in);
		static void setSFXVolume(const unsigned short &in);
		static void loadFiles(sf::RenderWindow & window, RW::Settings & settings);
	};
}