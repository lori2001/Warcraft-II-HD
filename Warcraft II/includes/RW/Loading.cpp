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

	int Loading::nroffiles = 0;
	const int Loading::progressperfile = 103;

	void Loading::animateBar(sf::RenderWindow & window)
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
	void Loading::loadFile(sf::Texture & texture, const std::string & from, sf::RenderWindow & window)
	{
		if (!texture.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::Font & font, const std::string & from, sf::RenderWindow & window)
	{
		if (!font.loadFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::Music & music, const std::string & from, sf::RenderWindow & window)
	{
		if (!music.openFromFile(from))
			std::cout << "error: could not load file from " << from << std::endl;

		animateBar(window);
	}
	void Loading::loadFile(sf::SoundBuffer & soundbuffer, const std::string & from, sf::RenderWindow & window)
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
	void Loading::loadFiles(sf::RenderWindow & window, RW::Settings & settings)
	{
		if (!loadingscreenT.loadFromFile("assets/images/loadingscreen.jpg"))
			std::cout << "error: could not load file from assets/images/loadingscreen.jpg" << std::endl;

		loadingscreenS.setTexture(loadingscreenT);
		loadingscreenS.setScale(sf::Vector2f(float(settings.get1920Scale().x), float(settings.get1920Scale().y)));

		progressbg.setFillColor(sf::Color(50,50,50,150));
		progressbg.setScale(settings.get1920Scale());
		progressbg.setSize(sf::Vector2f(1620, 35));
		progressbg.setPosition(sf::Vector2f(float(150 * settings.get1920Scale().x), float(settings.getRes().y - 100 * settings.get1920Scale().y)));

		progressbar.setFillColor(sf::Color::Green);
		progressbar.setScale(settings.get1920Scale());
		progressbar.setPosition(sf::Vector2f(float(150 * settings.get1920Scale().x), float(settings.getRes().y - 100 * settings.get1920Scale().y)));

		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbg);
		window.display();

		loadFile(orcsong, "assets/sounds/Theme/Orc/Orc War Room.wav", window);
		loadFile(humansong, "assets/sounds/Theme/Human/Human War Room.wav", window);
		loadFile(menusong, "assets/sounds/Theme/Menu.wav", window);
		loadFile(pressbuttonSB, "assets/sounds/Mouse/pressbutton.wav", window);
		pressbutton.setBuffer(pressbuttonSB);

		setMusicVolume(10 * settings.getMusic());
		setSFXVolume(10 * settings.getSoundFX());

		loadFile(backgroundT, "assets/images/background.jpg", window);
		loadFile(menubackgroundT, "assets/images/menubackground.jpg", window);
		loadFile(spbackgroundT, "assets/images/startgamebackground.jpg", window);
		loadFile(inworkT, "assets/images/in work.jpg", window);
		loadFile(interfaceT, "assets/images/interface.png", window);

		for (unsigned short i = 0; i < 20; i++)
		{
			loadFile(topgearsT[i], "assets/images/top gears/" + std::to_string(i + 1) + ".png", window);
			loadFile(botgearsT[i], "assets/images/bot gears/" + std::to_string(i + 1) + ".png", window);
		}

		loadFile(popupT, "assets/images/popup.png", window);
		loadFile(buttonT, "assets/images/button.png", window);
		loadFile(sliderT, "assets/images/slider.png", window);
		loadFile(sliderbuttonT, "assets/images/sliderbutton.png", window);
		loadFile(dropdownT, "assets/images/dropdown.png", window);
		dropdownT.setRepeated(true);
		loadFile(smalldropdownT, "assets/images/smalldropdown.png", window);
		smalldropdownT.setRepeated(true);
		loadFile(textholderT, "assets/images/textholder.png", window);
		loadFile(switchT, "assets/images/switch.png", window);
		loadFile(mapcontainerT, "assets/images/map container.png", window);
		loadFile(cursorT, "assets/images/orc cursor.png", window);

		loadFile(warcraftF, "assets/fonts/Warcraft.ttf", window);
		loadFile(normalF, "assets/fonts/Normal.ttf", window);

		loadFile(summertilesT, "assets/images/Summer Tiles.png", window);
		loadFile(wastelandtilesT, "assets/images/Wasteland Tiles.png", window);
		loadFile(wintertilesT, "assets/images/Winter Tiles.png", window);
		loadFile(ballistaT, "assets/images/Ballista.png", window);
		loadFile(battleshipT, "assets/images/Battleship.png", window);
		loadFile(catapultT, "assets/images/Catapult.png", window);
		loadFile(corpsesT, "assets/images/Corpses.png", window);
		loadFile(crittersT, "assets/images/Critters.png", window);
		loadFile(daemonT, "assets/images/Daemon.png", window);
		loadFile(deathknightT, "assets/images/Death Knight.png", window);
		loadFile(dragonT, "assets/images/Dragon.png", window);
		loadFile(dwarvendemolitionsquadT, "assets/images/Dwarven Demolition Squad.png", window);
		loadFile(elvenarcherT, "assets/images/Elven Archer.png", window);
		loadFile(elvendestroyerT, "assets/images/Elven Destroyer.png", window);
		loadFile(footmanT, "assets/images/Footman.png", window);
		loadFile(giantturtleT, "assets/images/Giant Turtle.png", window);
		loadFile(gnomishflyingmachineT, "assets/images/Gnomish Flying Machine.png", window);
		loadFile(gnomishsubmarineT, "assets/images/Gnomish Submarine.png", window);
		loadFile(goblinsappersT, "assets/images/Goblin Sappers.png", window);
		loadFile(goblinzeppelinT, "assets/images/Goblin Zeppelin.png", window);
		loadFile(gruntT, "assets/images/Grunt.png", window);
		loadFile(gryphonriderT, "assets/images/Gryphon Rider.png", window);
		loadFile(humanbuildingssummerT, "assets/images/Human Buildings Summer.png", window);
		loadFile(humanbuildingswinterT, "assets/images/Human Buildings Winter.png", window);
		loadFile(humanoiltankerT, "assets/images/Human Oil Tanker.png", window);
		loadFile(humantransportT, "assets/images/Human Transport.png", window);
		loadFile(iconsT, "assets/images/Icons.png", window);
		loadFile(knightT, "assets/images/Knight.png", window);
		loadFile(mageT, "assets/images/Mage.png", window);
		loadFile(magicandmisslesT, "assets/images/Magic and Missiles.png", window);
		loadFile(miscT, "assets/images/Misc.png", window);
		loadFile(ogrejuggernautT, "assets/images/Ogre Juggernaut.png", window);
		loadFile(ogreT, "assets/images/Ogre.png", window);
		loadFile(orcbuildingssummerT, "assets/images/Orc Buildings Summer.png", window);
		loadFile(orcbuildingswinterT, "assets/images/Orc Buildings Winter.png", window);
		loadFile(orcoiltankerT, "assets/images/Orc Oil Tanker.png", window);
		loadFile(orctransportT, "assets/images/Orc Transport.png", window);
		loadFile(peasantT, "assets/images/Peasant.png", window);
		loadFile(peonT, "assets/images/Peon.png", window);
		loadFile(skeletonT, "assets/images/Skeleton.png", window);
		loadFile(trollaxethrowerT, "assets/images/Troll Axethrower.png", window);
		loadFile(trolldestroyerT, "assets/images/Troll Destroyer.png", window);

		std::cout << "Files loaded: " << nroffiles << std::endl;

		if(nroffiles != progressperfile)
			std::cout << "NOTE: Progress per file("<<progressperfile<<") isn't equal to the number of files counted."<< std::endl;
	}
}