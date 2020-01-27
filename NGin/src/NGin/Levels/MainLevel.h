#pragma once
#include "SFML/Graphics.hpp"
#include "../System/Timer.h"
#include "../Audio/Audio.h"
#include "../UserInterface/Cursor.h"
#include"../System/Console.h"

namespace ngin {
	enum class WINDOW_TYPE {
		WINDOW_RESIZEABLE = 0, // resizeable windowed
		WINDOW_UNRESIZEABLE, // unresizeable windowed
		WINDOW_BORDERLESS,
		WINDOW_FULLSCREEN
	};

	class MainLevel : public sf::Drawable
	{
	public:
		virtual ~MainLevel() = default;
		void run();

		static sf::View view_; // default view is full HD
		static sf::VideoMode windowVideoMode_;
		static sf::String windowName_;
		static sf::Color windowClearColor_;
		static WINDOW_TYPE windowType_;

		static unsigned long int getLoopCicleCount();
		// quickly ad view_ to window_
		static void applyViewToWindow();
		// returns true if window is in focus
		static bool windowHasFocus() { return hasFocus_; }
	protected:
		// gets called after creating the window
		virtual void setup() = 0;
		// gets called only if there is an ongoing event
		virtual void handleEvents() = 0;
		// gets called every frame but is not constant
		virtual void update() = 0;
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		// use this to set window icon instead of accesing window_ directly
		void setWindowIcon(const std::string& location);

		static sf::RenderWindow window_;
		sf::Event event_{};

	private:
		sf::VideoMode saveVideoMode_ = windowVideoMode_;
		sf::String saveName_ = windowName_;
		WINDOW_TYPE saveType_ = windowType_;

		sf::Image icon_;
		bool hasIcon_ = false;

		static bool hasFocus_;

		static unsigned long loopCicles_; // counts how many loops have passed

		// recreates window with current settings
		void applySettingsToWindow();
		// called by updateWindow to set style
		void setWindowStyle(sf::Window& window, sf::Uint32 style) const;
	};

	// To be defined in client
	ngin::MainLevel* setMainLevel();
}
