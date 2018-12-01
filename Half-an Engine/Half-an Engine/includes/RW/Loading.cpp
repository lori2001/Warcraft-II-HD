#include "Loading.h"

namespace RW
{
	Paths Loading::paths;
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
	sf::Texture Loading::toolbarT;
	sf::Texture Loading::topgearsT[20];
	sf::Texture Loading::botgearsT[20];
	sf::Texture Loading::popupT;
	sf::Texture Loading::borderT;
	sf::Texture Loading::buttonT;
	sf::Texture Loading::undockT;
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

	int Loading::nroffiles = 0;
	const int Loading::progressperfile = 106;

	void Loading::animateBar(Window & window)
	{
		int progress = 1620 / progressperfile; // bar width minus the number of loadings

		progressbar.setSize(sf::Vector2f(progressbar.getSize().x + progress, 35));

		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbg);
		window.draw(progressbar);
		window.display();

		nroffiles++;
	}
	void Loading::loadFile(sf::Texture & texture, const std::string & from, Window & window)
	{
		if (!texture.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::Font & font, const std::string & from, Window & window)
	{
		if (!font.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::Music & music, const std::string & from, Window & window)
	{
		if (!music.openFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::SoundBuffer & soundbuffer, const std::string & from, Window & window)
	{
		if (!soundbuffer.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::setMusicVolume(const unsigned short & in)
	{
		orcsong.setVolume(in);
		humansong.setVolume(in);
		menusong.setVolume(in);
	}
	void Loading::setSFXVolume(const unsigned short & in)
	{
		pressbutton.setVolume(in);
	}
	void Loading::loadFiles(Window &window)
	{
		if (!loadingscreenT.loadFromFile("assets/images/loadingscreen.jpg"))
			std::cout << "error: could not load file from /assets/images/loadingscreen.jpg" << std::endl;

		loadingscreenS.setTexture(loadingscreenT);
		loadingscreenS.setScale(sf::Vector2f(float(window.get1920Scale().x), float(window.get1920Scale().y)));

		progressbg.setFillColor(sf::Color(50, 50, 50, 150));
		progressbg.setScale(window.get1920Scale());
		progressbg.setSize(sf::Vector2f(1620, 35));
		progressbg.setPosition(sf::Vector2f(float(150 * window.get1920Scale().x), float(window.getRes().y - 100 * window.get1920Scale().y)));

		progressbar.setFillColor(sf::Color::Green);
		progressbar.setScale(window.get1920Scale());
		progressbar.setPosition(sf::Vector2f(float(150 * window.get1920Scale().x), float(window.getRes().y - 100 * window.get1920Scale().y)));

		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbg);
		window.display();

		loadFile(orcsong, paths.getGamePath() + "\\assets\\sounds\\Theme\\Orc\\Orc War Room.wav", window);
		loadFile(humansong, paths.getGamePath() + "\\assets\\sounds\\Theme\\Human\\Human War Room.wav", window);
		loadFile(menusong, paths.getGamePath() + "\\assets\\sounds\\Theme\\Menu.wav", window);
		loadFile(pressbuttonSB, paths.getGamePath() + "\\assets\\sounds\\Mouse\\pressbutton.wav", window);
		pressbutton.setBuffer(pressbuttonSB);

		//setMusicVolume(10 * window.getMusic());
		//setSFXVolume(10 * window.getSoundFX());

		loadFile(backgroundT, paths.getGamePath() + "\\assets\\images\\background.jpg", window);
		loadFile(menubackgroundT, paths.getGamePath() + "\\assets\\images\\menubackground.jpg", window);
		loadFile(spbackgroundT, paths.getGamePath() + "\\assets\\images\\startgamebackground.jpg", window);
		loadFile(inworkT, paths.getGamePath() + "\\assets\\images\\in work.jpg", window);
		loadFile(interfaceT, paths.getGamePath() + "\\assets\\images\\interface.png", window);
		loadFile(toolbarT, "assets/images/toolbar.png", window);

		for (unsigned short i = 0; i < 20; i++)
		{
			loadFile(topgearsT[i], paths.getGamePath() + "\\assets\\images\\top gears\\" + std::to_string(i + 1) + ".png", window);
			loadFile(botgearsT[i], paths.getGamePath() + "\\assets\\images\\bot gears\\" + std::to_string(i + 1) + ".png", window);
		}

		loadFile(popupT, paths.getGamePath() + "\\assets\\images\\popup.png", window);
		loadFile(borderT, "assets/images/border.png", window);
		loadFile(buttonT, paths.getGamePath() + "\\assets\\images\\button.png", window);
		loadFile(undockT, "assets/images/undock.png", window);
		loadFile(sliderT, paths.getGamePath() + "\\assets\\images\\slider.png", window);
		loadFile(sliderbuttonT, paths.getGamePath() + "\\assets\\images\\sliderbutton.png", window);
		loadFile(dropdownT, paths.getGamePath() + "\\assets\\images\\dropdown.png", window);
		dropdownT.setRepeated(true);
		loadFile(smalldropdownT, paths.getGamePath() + "\\assets\\images\\smalldropdown.png", window);
		smalldropdownT.setRepeated(true);
		loadFile(textholderT, paths.getGamePath() + "\\assets\\images\\textholder.png", window);
		loadFile(switchT, paths.getGamePath() + "\\assets\\images\\switch.png", window);
		loadFile(mapcontainerT, paths.getGamePath() + "\\assets\\images\\map container.png", window);
		loadFile(cursorT, paths.getGamePath() + "\\assets\\images\\orc cursor.png", window);

		loadFile(warcraftF, paths.getGamePath() + "\\assets\\fonts\\Warcraft.ttf", window);
		loadFile(normalF, paths.getGamePath() + "\\assets\\fonts\\Normal.ttf", window);

		loadFile(summertilesT, paths.getGamePath() + "\\assets\\images\\Summer Tiles.png", window);
		loadFile(wastelandtilesT, paths.getGamePath() + "\\assets\\images\\Wasteland Tiles.png", window);
		loadFile(wintertilesT, paths.getGamePath() + "\\assets\\images\\Winter Tiles.png", window);
		loadFile(ballistaT, paths.getGamePath() + "\\assets\\images\\Ballista.png", window);
		loadFile(battleshipT, paths.getGamePath() + "\\assets\\images\\Battleship.png", window);
		loadFile(catapultT, paths.getGamePath() + "\\assets\\images\\Catapult.png", window);
		loadFile(corpsesT, paths.getGamePath() + "\\assets\\images\\Corpses.png", window);
		loadFile(crittersT, paths.getGamePath() + "\\assets\\images\\Critters.png", window);
		loadFile(daemonT, paths.getGamePath() + "\\assets\\images\\Daemon.png", window);
		loadFile(deathknightT, paths.getGamePath() + "\\assets\\images\\Death Knight.png", window);
		loadFile(dragonT, paths.getGamePath() + "\\assets\\images\\Dragon.png", window);
		loadFile(dwarvendemolitionsquadT, paths.getGamePath() + "\\assets\\images\\Dwarven Demolition Squad.png", window);
		loadFile(elvenarcherT, paths.getGamePath() + "\\assets\\images\\Elven Archer.png", window);
		loadFile(elvendestroyerT, paths.getGamePath() + "\\assets\\images\\Elven Destroyer.png", window);
		loadFile(footmanT, paths.getGamePath() + "\\assets\\images\\Footman.png", window);
		loadFile(giantturtleT, paths.getGamePath() + "\\assets\\images\\Giant Turtle.png", window);
		loadFile(gnomishflyingmachineT, paths.getGamePath() + "\\assets\\images\\Gnomish Flying Machine.png", window);
		loadFile(gnomishsubmarineT, paths.getGamePath() + "\\assets\\images\\Gnomish Submarine.png", window);
		loadFile(goblinsappersT, paths.getGamePath() + "\\assets\\images\\Goblin Sappers.png", window);
		loadFile(goblinzeppelinT, paths.getGamePath() + "\\assets\\images\\Goblin Zeppelin.png", window);
		loadFile(gruntT, paths.getGamePath() + "\\assets\\images\\Grunt.png", window);
		loadFile(gryphonriderT, paths.getGamePath() + "\\assets\\images\\Gryphon Rider.png", window);
		loadFile(humanbuildingssummerT, paths.getGamePath() + "\\assets\\images\\Human Buildings Summer.png", window);
		loadFile(humanbuildingswinterT, paths.getGamePath() + "\\assets\\images\\Human Buildings Winter.png", window);
		loadFile(humanoiltankerT, paths.getGamePath() + "\\assets\\images\\Human Oil Tanker.png", window);
		loadFile(humantransportT, paths.getGamePath() + "\\assets\\images\\Human Transport.png", window);
		loadFile(iconsT, paths.getGamePath() + "\\assets\\images\\Icons.png", window);
		loadFile(knightT, paths.getGamePath() + "\\assets\\images\\Knight.png", window);
		loadFile(mageT, paths.getGamePath() + "\\assets\\images\\Mage.png", window);
		loadFile(magicandmisslesT, paths.getGamePath() + "\\assets\\images\\Magic and Missiles.png", window);
		loadFile(miscT, paths.getGamePath() + "\\assets\\images\\Misc.png", window);
		loadFile(ogrejuggernautT, paths.getGamePath() + "\\assets\\images\\Ogre Juggernaut.png", window);
		loadFile(ogreT, paths.getGamePath() + "\\assets\\images\\Ogre.png", window);
		loadFile(orcbuildingssummerT, paths.getGamePath() + "\\assets\\images\\Orc Buildings Summer.png", window);
		loadFile(orcbuildingswinterT, paths.getGamePath() + "\\assets\\images\\Orc Buildings Winter.png", window);
		loadFile(orcoiltankerT, paths.getGamePath() + "\\assets\\images\\Orc Oil Tanker.png", window);
		loadFile(orctransportT, paths.getGamePath() + "\\assets\\images\\Orc Transport.png", window);
		loadFile(peasantT, paths.getGamePath() + "\\assets\\images\\Peasant.png", window);
		loadFile(peonT, paths.getGamePath() + "\\assets\\images\\Peon.png", window);
		loadFile(skeletonT, paths.getGamePath() + "\\assets\\images\\Skeleton.png", window);
		loadFile(trollaxethrowerT, paths.getGamePath() + "\\assets\\images\\Troll Axethrower.png", window);
		loadFile(trolldestroyerT, paths.getGamePath() + "\\assets\\images\\Troll Destroyer.png", window);

		std::cout << "Files loaded: " << nroffiles << std::endl;

		if (nroffiles != progressperfile)
			std::cout << "NOTE: Progress per file(" << progressperfile << ") isn't equal to the number of files counted." << std::endl;
	}
}