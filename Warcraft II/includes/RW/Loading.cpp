#include "Loading.h"

namespace RW
{
	sf::Texture Loading::loadingscreenT;
	sf::Sprite Loading::loadingscreenS;
	sf::RectangleShape Loading::progressbar;
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
			std::cout << "error: could not load loadingscreen.jpg" << std::endl;

		loadingscreenS.setTexture(loadingscreenT);
		loadingscreenS.setScale(sf::Vector2f(float(settings.get1920Scale().x), float(settings.get1920Scale().y)));

		progressbar.setFillColor(sf::Color::Green);
		progressbar.setScale(settings.get1000Scale());
		progressbar.setPosition(sf::Vector2f(float(100 * settings.get1000Scale().x), float(settings.getRes().y - 50 * settings.get1000Scale().y)));
		progressbar.setSize(sf::Vector2f(50, 25));

		window.clear();
		window.draw(loadingscreenS);
		window.display();

		if (!orcsong.openFromFile("assets/sounds/Theme/Orc/Orc War Room.wav"))
			std::cout << "error: could not load Orc War Room.wav" << std::endl;

		if (!humansong.openFromFile("assets/sounds/Theme/Human/Human War Room.wav"))
			std::cout << "error: could not load Human War Room.wav" << std::endl;

		if (!menusong.openFromFile("assets/sounds/Theme/Menu.wav"))
			std::cout << "error: could not load Menu.wav" << std::endl;

		if (!pressbuttonSB.loadFromFile("assets/sounds/Mouse/pressbutton.wav"))
			std::cout << "error: could not load pressbutton.wav" << std::endl;
		pressbutton.setBuffer(pressbuttonSB);

		setMusicVolume(10 * settings.getMusic());
		setSFXVolume(10 * settings.getSoundFX());

		progressbar.setSize(sf::Vector2f(100, 25));
		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbar);
		window.display();

		if (!backgroundT.loadFromFile("assets/images/background.jpg"))
			std::cout << "error: could not load background.jpg" << std::endl;

		if (!menubackgroundT.loadFromFile("assets/images/menubackground.jpg"))
			std::cout << "error: could not load menubackground.jpg" << std::endl;

		if (!spbackgroundT.loadFromFile("assets/images/startgamebackground.jpg"))
			std::cout << "error: could not load startgamebackground.jpg" << std::endl;

		if (!inworkT.loadFromFile("assets/images/in work.jpg"))
			std::cout << "error: could not load in work.jpg" << std::endl;

		if (!interfaceT.loadFromFile("assets/images/interface.png"))
			std::cout << "error: could not load interface.png" << std::endl;

		progressbar.setSize(sf::Vector2f(250, 25));
		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbar);
		window.display();

		for (unsigned short i = 0; i < 20; i++)
		{
			if (!topgearsT[i].loadFromFile("assets/images/top gears/" + std::to_string(i + 1) + ".png"))
				std::cout << "error: could not load top gears/" + std::to_string(i + 1) + ".png" << std::endl;
			if (!botgearsT[i].loadFromFile("assets/images/bot gears/" + std::to_string(i + 1) + ".png"))
				std::cout << "error: could not load bot gears/" + std::to_string(i + 1) + ".png" << std::endl;
		}

		if (!popupT.loadFromFile("assets/images/popup.png"))
			std::cout << "error: could not load popup.png" << std::endl;

		if (!buttonT.loadFromFile("assets/images/button.png"))
			std::cout << "error: could not load button.png" << std::endl;

		if (!sliderT.loadFromFile("assets/images/slider.png"))
			std::cout << "error: could not load slider.png" << std::endl;

		if (!sliderbuttonT.loadFromFile("assets/images/sliderbutton.png"))
			std::cout << "error: could not load sliderbutton.png" << std::endl;

		if (!dropdownT.loadFromFile("assets/images/dropdown.png"))
			std::cout << "error: could not load dropdown.png" << std::endl;

		dropdownT.setRepeated(true);

		if (!smalldropdownT.loadFromFile("assets/images/smalldropdown.png"))
			std::cout << "error: could not load smalldropdown.png" << std::endl;

		smalldropdownT.setRepeated(true);

		if (!textholderT.loadFromFile("assets/images/textholder.png"))
			std::cout << "error: could not load textholder.png" << std::endl;

		if (!switchT.loadFromFile("assets/images/switch.png"))
			std::cout << "error: could not load switch.png" << std::endl;

		if (!cursorT.loadFromFile("assets/images/orc cursor.png"))
			std::cout << "error: could not load orc cursor.png" << std::endl;

		progressbar.setSize(sf::Vector2f(400, 25));
		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbar);
		window.display();

		if (!warcraftF.loadFromFile("assets/fonts/Warcraft.ttf"))
			std::cout << "error: could not load Warcraft.tff" << std::endl;

		if (!normalF.loadFromFile("assets/fonts/Normal.ttf"))
			std::cout << "error: could not load Normal.tff" << std::endl;

		progressbar.setSize(sf::Vector2f(450, 25));
		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbar);
		window.display();

		if (!summertilesT.loadFromFile("assets/images/Summer Tiles.png"))
			std::cout << "error: could not load Summer Tiles.png" << std::endl;

		if (!wastelandtilesT.loadFromFile("assets/images/Wasteland Tiles.png"))
			std::cout << "error: could not load Wasteland Tiles.png" << std::endl;

		if (!wintertilesT.loadFromFile("assets/images/Winter Tiles.png"))
			std::cout << "error: could not load Winter Tiles.png" << std::endl;

		if (!ballistaT.loadFromFile("assets/images/Ballista.png"))
			std::cout << "error: could not load Ballista.png" << std::endl;

		if (!battleshipT.loadFromFile("assets/images/Battleship.png"))
			std::cout << "error: could not load Battleship.png" << std::endl;

		if (!catapultT.loadFromFile("assets/images/Catapult.png"))
			std::cout << "error: could not load Catapult.png" << std::endl;

		if (!corpsesT.loadFromFile("assets/images/Corpses.png"))
			std::cout << "error: could not load Corpses.png" << std::endl;

		if (!crittersT.loadFromFile("assets/images/Critters.png"))
			std::cout << "error: could not load Critters.png" << std::endl;

		if (!daemonT.loadFromFile("assets/images/Daemon.png"))
			std::cout << "error: could not load Daemon.png" << std::endl;

		if (!deathknightT.loadFromFile("assets/images/Death Knight.png"))
			std::cout << "error: could not load Death Knight.png" << std::endl;

		if (!dragonT.loadFromFile("assets/images/Dragon.png"))
			std::cout << "error: could not load Dragon.png" << std::endl;

		if (!dwarvendemolitionsquadT.loadFromFile("assets/images/Dwarven Demolition Squad.png"))
			std::cout << "error: could not load Dwarven Demolition Squad.png" << std::endl;

		if (!elvenarcherT.loadFromFile("assets/images/Elven Archer.png"))
			std::cout << "error: could not load Elven Archer.png" << std::endl;

		if (!elvendestroyerT.loadFromFile("assets/images/Elven Destroyer.png"))
			std::cout << "error: could not load Elven Archer.png" << std::endl;

		if (!footmanT.loadFromFile("assets/images/Footman.png"))
			std::cout << "error: could not load Footman.png" << std::endl;

		if (!giantturtleT.loadFromFile("assets/images/Giant Turtle.png"))
			std::cout << "error: could not load Giant Turtle.png" << std::endl;

		if (!gnomishflyingmachineT.loadFromFile("assets/images/Gnomish Flying Machine.png"))
			std::cout << "error: could not load Gnomish Flying Machine.png" << std::endl;

		if (!gnomishsubmarineT.loadFromFile("assets/images/Gnomish Submarine.png"))
			std::cout << "error: could not load Gnomish Submarine.png" << std::endl;

		if (!goblinsappersT.loadFromFile("assets/images/Goblin Sappers.png"))
			std::cout << "error: could not load Goblin Sappers.png" << std::endl;

		if (!goblinzeppelinT.loadFromFile("assets/images/Goblin Zeppelin.png"))
			std::cout << "error: could not load Goblin Zeppelin.png" << std::endl;

		if (!gruntT.loadFromFile("assets/images/Grunt.png"))
			std::cout << "error: could not load Grunt.png" << std::endl;

		if (!gryphonriderT.loadFromFile("assets/images/Gryphon Rider.png"))
			std::cout << "error: could not load Gryphon Rider.png" << std::endl;

		if (!humanbuildingssummerT.loadFromFile("assets/images/Human Buildings Summer.png"))
			std::cout << "error: could not load Human Buildings Summer.png" << std::endl;

		if (!humanbuildingswinterT.loadFromFile("assets/images/Human Buildings Winter.png"))
			std::cout << "error: could not load Human Buildings Winter.png" << std::endl;

		if (!humanoiltankerT.loadFromFile("assets/images/Human Oil Tanker.png"))
			std::cout << "error: could not load Human Oil Tanker.png" << std::endl;

		if (!humantransportT.loadFromFile("assets/images/Human Transport.png"))
			std::cout << "error: could not load Human Transport.png" << std::endl;

		if (!iconsT.loadFromFile("assets/images/Icons.png"))
			std::cout << "error: could not load Icons.png" << std::endl;

		if (!knightT.loadFromFile("assets/images/Knight.png"))
			std::cout << "error: could not load Knight.png" << std::endl;

		if (!mageT.loadFromFile("assets/images/Mage.png"))
			std::cout << "error: could not load Mage.png" << std::endl;

		if (!magicandmisslesT.loadFromFile("assets/images/Magic and Missiles.png"))
			std::cout << "error: could not load Magic and Missiles.png" << std::endl;

		if (!miscT.loadFromFile("assets/images/Misc.png"))
			std::cout << "error: could not load Misc.png" << std::endl;

		if (!ogrejuggernautT.loadFromFile("assets/images/Ogre Juggernaut.png"))
			std::cout << "error: could not load Ogre Juggernaut.png" << std::endl;

		if (!ogreT.loadFromFile("assets/images/Ogre.png"))
			std::cout << "error: could not load Ogre.png" << std::endl;

		if (!orcbuildingssummerT.loadFromFile("assets/images/Orc Buildings Summer.png"))
			std::cout << "error: could not load Orc Buildings Summer.png" << std::endl;

		if (!orcbuildingswinterT.loadFromFile("assets/images/Orc Buildings Winter.png"))
			std::cout << "error: could not load Orc Buildings Winter.png" << std::endl;

		if (!orcoiltankerT.loadFromFile("assets/images/Orc Oil Tanker.png"))
			std::cout << "error: could not load Orc Oil Tanker.png" << std::endl;

		if (!orctransportT.loadFromFile("assets/images/Orc Transport.png"))
			std::cout << "error: could not load Orc Transport.png" << std::endl;

		if (!peasantT.loadFromFile("assets/images/Peasant.png"))
			std::cout << "error: could not load Peasant.png" << std::endl;

		if (!peonT.loadFromFile("assets/images/Peon.png"))
			std::cout << "error: could not load Peon.png" << std::endl;

		if (!skeletonT.loadFromFile("assets/images/Skeleton.png"))
			std::cout << "error: could not load Skeleton.png" << std::endl;

		if (!trollaxethrowerT.loadFromFile("assets/images/Troll Axethrower.png"))
			std::cout << "error: could not load Troll Axethrower.png" << std::endl;

		if (!trolldestroyerT.loadFromFile("assets/images/Troll Destroyer.png"))
			std::cout << "error: could not load Troll Destroyer.png" << std::endl;


		progressbar.setSize(sf::Vector2f(500, 25));
		window.clear();
		window.draw(loadingscreenS);
		window.draw(progressbar);
		window.display();
	}
}