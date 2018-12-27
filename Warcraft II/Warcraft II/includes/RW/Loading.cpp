#include "Loading.h"

namespace RW
{
	sf::Texture Loading::loadingscreenT;
	sf::Sprite Loading::loadingscreenS;
	sf::RectangleShape Loading::progressbar;
	sf::RectangleShape Loading::progressbg;
	sf::SoundBuffer Loading::pressbuttonSB;
	sf::Sound Loading::pressbutton;
	sf::Music Loading::menusong;
	sf::Music Loading::orcsong;
	sf::Music Loading::humansong;
	sf::Texture Loading::backgroundT;
	sf::Texture Loading::menubackgroundT;
	sf::Texture Loading::spbackgroundT;
	sf::Texture Loading::inworkT;
	sf::Texture Loading::interfaceT;
	sf::Texture Loading::topgearsT[20];
	sf::Texture Loading::botgearsT[20];
	sf::Texture Loading::popupT;
	sf::Texture Loading::buttonT;
	sf::Texture Loading::sliderT;
	sf::Texture Loading::sliderbuttonT;
	sf::Texture Loading::dropdownT;
	sf::Texture Loading::smalldropdownT;
	sf::Texture Loading::textholderT;
	sf::Texture Loading::switchT;
	sf::Texture Loading::mapcontainerT;
	sf::Texture Loading::cursorT;
	sf::Texture Loading::summertilesT;
	sf::Texture Loading::wastelandtilesT;
	sf::Texture Loading::wintertilesT;
	sf::Texture Loading::ballistaT;
	sf::Texture Loading::battleshipT;
	sf::Texture Loading::catapultT;
	sf::Texture Loading::corpsesT;
	sf::Texture Loading::crittersT;
	sf::Texture Loading::daemonT;
	sf::Texture Loading::deathknightT;
	sf::Texture Loading::dragonT;
	sf::Texture Loading::dwarvendemolitionsquadT;
	sf::Texture Loading::elvenarcherT;
	sf::Texture Loading::elvendestroyerT;
	sf::Texture Loading::footmanT;
	sf::Texture Loading::giantturtleT;
	sf::Texture Loading::gnomishflyingmachineT;
	sf::Texture Loading::gnomishsubmarineT;
	sf::Texture Loading::goblinsappersT;
	sf::Texture Loading::goblinzeppelinT;
	sf::Texture Loading::gruntT;
	sf::Texture Loading::gryphonriderT;
	sf::Texture Loading::humanbuildingssummerT;
	sf::Texture Loading::humanbuildingswinterT;
	sf::Texture Loading::humanoiltankerT;
	sf::Texture Loading::humantransportT;
	sf::Texture Loading::iconsT;
	sf::Texture Loading::knightT;
	sf::Texture Loading::mageT;
	sf::Texture Loading::magicandmisslesT;
	sf::Texture Loading::miscT;
	sf::Texture Loading::ogrejuggernautT;
	sf::Texture Loading::ogreT;
	sf::Texture Loading::orcbuildingssummerT;
	sf::Texture Loading::orcbuildingswinterT;
	sf::Texture Loading::orcoiltankerT;
	sf::Texture Loading::orctransportT;
	sf::Texture Loading::peasantT;
	sf::Texture Loading::peonT;
	sf::Texture Loading::skeletonT;
	sf::Texture Loading::trollaxethrowerT;
	sf::Texture Loading::trolldestroyerT;

	sf::Font Loading::warcraftF;
	sf::Font Loading::normalF;

	bool Loading::complete;

	void Loading::loadFile(sf::Texture & texture, const std::string & from)
	{
		if (!texture.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;
	}
	void Loading::loadFile(sf::Font & font, const std::string & from)
	{
		if (!font.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;
	}
	void Loading::loadFile(sf::Music & music, const std::string & from)
	{
		if (!music.openFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;
	}
	void Loading::loadFile(sf::SoundBuffer & soundbuffer, const std::string & from)
	{
		if (!soundbuffer.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;
	}
	int Loading::animateBar(sf::RenderWindow * window)
	{
		for (float i = 0; i <= 1620; i+=1) {
			progressbar.setSize(sf::Vector2f(i, 35));

			window->clear();
			window->draw(loadingscreenS);
			window->draw(progressbg);
			window->draw(progressbar);
			window->display();

			if (complete) {
				break;
			}
		}

		window->setActive(false);
		return 0;
	}
	int Loading::loadTextures(RW::Settings * settings)
	{
		loadFile(orcsong, "assets/sounds/Theme/Orc/Orc War Room.wav");
		loadFile(humansong, "assets/sounds/Theme/Human/Human War Room.wav");
		loadFile(menusong, "assets/sounds/Theme/Menu.wav");
		loadFile(pressbuttonSB, "assets/sounds/Mouse/pressbutton.wav");
		pressbutton.setBuffer(pressbuttonSB);

		setMusicVolume(10 * settings->getMusic());
		setSFXVolume(10 * settings->getSoundFX());

		loadFile(backgroundT, "assets/images/background.jpg");
		loadFile(menubackgroundT, "assets/images/menubackground.jpg");
		loadFile(spbackgroundT, "assets/images/startgamebackground.jpg");
		loadFile(inworkT, "assets/images/in work.jpg");
		loadFile(interfaceT, "assets/images/interface.png");

		for (unsigned int i = 0; i < 20; i++)
		{
			loadFile(topgearsT[i], "assets/images/top gears/" + std::to_string(i + 1) + ".png");
			loadFile(botgearsT[i], "assets/images/bot gears/" + std::to_string(i + 1) + ".png");
		}

		loadFile(popupT, "assets/images/popup.png");
		loadFile(buttonT, "assets/images/button.png");
		loadFile(sliderT, "assets/images/slider.png");
		loadFile(sliderbuttonT, "assets/images/sliderbutton.png");
		loadFile(dropdownT, "assets/images/dropdown.png");
		dropdownT.setRepeated(true);
		loadFile(smalldropdownT, "assets/images/smalldropdown.png");
		smalldropdownT.setRepeated(true);
		loadFile(textholderT, "assets/images/textholder.png");
		loadFile(switchT, "assets/images/switch.png");
		loadFile(mapcontainerT, "assets/images/map container.png");
		loadFile(cursorT, "assets/images/orc cursor.png");

		loadFile(warcraftF, "assets/fonts/Warcraft.ttf");
		loadFile(normalF, "assets/fonts/Normal.ttf");

		loadFile(summertilesT, "assets/images/Summer Tiles.png");
		loadFile(wastelandtilesT, "assets/images/Wasteland Tiles.png");
		loadFile(wintertilesT, "assets/images/Winter Tiles.png");
		loadFile(ballistaT, "assets/images/Ballista.png");
		loadFile(battleshipT, "assets/images/Battleship.png");
		loadFile(catapultT, "assets/images/Catapult.png");
		loadFile(corpsesT, "assets/images/Corpses.png");
		loadFile(crittersT, "assets/images/Critters.png");
		loadFile(daemonT, "assets/images/Daemon.png");
		loadFile(deathknightT, "assets/images/Death Knight.png");
		loadFile(dragonT, "assets/images/Dragon.png");
		loadFile(dwarvendemolitionsquadT, "assets/images/Dwarven Demolition Squad.png");
		loadFile(elvenarcherT, "assets/images/Elven Archer.png");
		loadFile(elvendestroyerT, "assets/images/Elven Destroyer.png");
		loadFile(footmanT, "assets/images/Footman.png");
		loadFile(giantturtleT, "assets/images/Giant Turtle.png");
		loadFile(gnomishflyingmachineT, "assets/images/Gnomish Flying Machine.png");
		loadFile(gnomishsubmarineT, "assets/images/Gnomish Submarine.png");
		loadFile(goblinsappersT, "assets/images/Goblin Sappers.png");
		loadFile(goblinzeppelinT, "assets/images/Goblin Zeppelin.png");
		loadFile(gruntT, "assets/images/Grunt.png");
		loadFile(gryphonriderT, "assets/images/Gryphon Rider.png");
		loadFile(humanbuildingssummerT, "assets/images/Human Buildings Summer.png");
		loadFile(humanbuildingswinterT, "assets/images/Human Buildings Winter.png");
		loadFile(humanoiltankerT, "assets/images/Human Oil Tanker.png");
		loadFile(humantransportT, "assets/images/Human Transport.png");
		loadFile(iconsT, "assets/images/Icons.png");
		loadFile(knightT, "assets/images/Knight.png");
		loadFile(mageT, "assets/images/Mage.png");
		loadFile(magicandmisslesT, "assets/images/Magic and Missiles.png");
		loadFile(miscT, "assets/images/Misc.png");
		loadFile(ogrejuggernautT, "assets/images/Ogre Juggernaut.png");
		loadFile(ogreT, "assets/images/Ogre.png");
		loadFile(orcbuildingssummerT, "assets/images/Orc Buildings Summer.png");
		loadFile(orcbuildingswinterT, "assets/images/Orc Buildings Winter.png");
		loadFile(orcoiltankerT, "assets/images/Orc Oil Tanker.png");
		loadFile(orctransportT, "assets/images/Orc Transport.png");
		loadFile(peasantT, "assets/images/Peasant.png");
		loadFile(peonT, "assets/images/Peon.png");
		loadFile(skeletonT, "assets/images/Skeleton.png");
		loadFile(trollaxethrowerT, "assets/images/Troll Axethrower.png");
		loadFile(trolldestroyerT, "assets/images/Troll Destroyer.png");

		std::cout << "All Files Loaded!" << std::endl;

		complete = true;

		return 0;
	}
	void Loading::setMusicVolume(const unsigned int & in)
	{
		orcsong.setVolume((float)in);
		humansong.setVolume((float)in);
		menusong.setVolume((float)in);
	}
	void Loading::setSFXVolume(const unsigned int & in)
	{
		pressbutton.setVolume((float)in);
	}
	void Loading::loadFiles(sf::RenderWindow & window, RW::Settings & settings)
	{
		if (!loadingscreenT.loadFromFile("assets/images/loadingscreen.jpg"))
			std::cout << "error: could not load file from assets/images/loadingscreen.jpg" << std::endl;

		loadingscreenS.setTexture(loadingscreenT);

		progressbg.setFillColor(sf::Color(50,50,50,150));
		progressbg.setSize(sf::Vector2f(0, 35)); // 1620, 35
		progressbg.setPosition(sf::Vector2f(150, 1080 - 100));

		progressbar.setFillColor(sf::Color::Green);
		progressbar.setPosition(sf::Vector2f(150, 1080 - 100));

		window.setActive(false);
		std::thread textureloading(loadTextures, &settings);
		std::thread animation(animateBar, &window);

		textureloading.join();
		animation.join();
		window.setActive(true);
	}
}