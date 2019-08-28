#pragma once
#include "SFML/Graphics.hpp"
#include "../System/Timer.h"
#include "../Audio/Audio.h"
#include "../UserInterface/Cursor.h"
#include"../System/Console.h"

namespace ngin {
	class MainLevel : public sf::Drawable
	{
	public:
		virtual ~MainLevel() = default;
		void run();

		enum WINDOW_TYPE {
			RESIZEABLE = 0, // resizeable windowed
			UNRESIZEABLE, // unresizeable windowed
			BORDERLESS,
			FULLSCREEN
		};

	protected:
		// gets called after creating the window
		virtual void setup() = 0;
		// gets called only if there is an ongoing event
		virtual void handleEvents() = 0;
		// gets called every frame but is not constant
		virtual void update() = 0;
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		sf::VideoMode windowVideoMode_{ 1000, 600 };
		sf::String windowName_ = "My Application";
		WINDOW_TYPE windowType_ = WINDOW_TYPE::UNRESIZEABLE;

		sf::RenderWindow window_;
		sf::Event event_;
	private:

		sf::VideoMode saveVideoMode_ = windowVideoMode_;
		sf::String saveName_ = windowName_;
		WINDOW_TYPE saveType_ = windowType_;

		// recreates window with current settings
		void applySettingsToWindow();
		// called by updateWindow to set style
		void setWindowStyle(sf::Window& window, sf::Uint32 style) const;
	};

	// To be defined in client
	ngin::MainLevel* setMainLevel();
}
