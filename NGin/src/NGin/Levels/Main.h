#pragma once
#include "SFML/Graphics.hpp"
#include "../System/Timer.h"
#include "../Audio/Audio.h"
#include "../UserInterface/Cursor.h"
#include"../System/Console.h"

namespace ng {
	enum class WINDOW_TYPE {
		WINDOW_RESIZEABLE = 0, // resizeable windowed
		WINDOW_UNRESIZEABLE, // unresizeable windowed
		WINDOW_BORDERLESS,
		WINDOW_FULLSCREEN
	};

	class Main : public sf::Drawable
	{
	public:
		Main();
		virtual ~Main() = default;
		void run();

		static sf::VideoMode windowVideoMode;
		static sf::String windowName;
		static sf::Color windowClearColor;
		static WINDOW_TYPE windowType;

		static unsigned long long getLoopCicleCount();
		// quickly ad view_ to window_
		static void applyDefaultViewToWindow();
		// returns true if window is in focus
		static bool windowHasFocus() { return hasFocus; }
		// closes app properly from anywhere from program
		// should be called because it calls destructors instead of
		// forcing exit
		static void closeWindow() { window.close(); closeWindow_ = true; }
		static sf::WindowHandle getWindowHandle() { return window.getSystemHandle(); }

		static sf::RenderWindow* getWindowPtr() { return &window; }

		// get window view
		static sf::View getWindowView() { return window.getView(); }

		// add another view (apart from default one)
		static void setWindowView(const sf::View& secondView);

		// use this to set window icon instead of accesing window_ directly
		static void setWindowIcon(const std::string& location);
		static sf::Image* getWinIconPtr() {
			if (hasIcon_) {
				return &icon_;
			}
			else return nullptr;
		}
	protected:
		static sf::View nginView_; // "default view" (full HD)

		// gets called only if there is an ongoing event
		virtual void handleEvents() = 0;
		// gets called every frame but is not constant
		virtual void update() = 0;
		// gets called every frame but should only draw on window
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		static sf::RenderWindow window;
		sf::Event event_;

	private:
		sf::VideoMode saveVideoMode_ = windowVideoMode;
		sf::String saveName_ = windowName;
		WINDOW_TYPE saveType_ = windowType;

		static sf::Image icon_;
		static bool hasIcon_;

		// "closes window" before it even opens itself
		static bool closeWindow_;

		static bool hasFocus;

		static unsigned long long loopCicles; // counts how many loops have passed

		// recreates window with current settings
		void applySettingsToWindow();
		// called by updateWindow to set style
		void setWindowStyle(sf::Window& window, sf::Uint32 style) const;
	};

	// To be defined in client
	ng::Main* setMainLevel();
}
