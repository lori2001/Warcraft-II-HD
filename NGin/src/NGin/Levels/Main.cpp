#include "Main.h"
#include <Windows.h>

namespace ng {
	sf::View Main::nginView_ = sf::View{ sf::FloatRect{0, 0, 1920, 1080} }; // default view is full HD
	sf::VideoMode Main::windowVideoMode{ 1000, 600 }; // default window size fits all modern screens
	sf::String Main::windowName = "My Application"; // defualt name
	sf::Color Main::windowClearColor = sf::Color(0, 0, 0); // default screen clear color
	WINDOW_TYPE Main::windowType = WINDOW_TYPE::WINDOW_UNRESIZEABLE; // default window type

	sf::Image Main::icon_;
	bool Main::hasIcon_ = false;
	
	bool Main::closeWindow_ = false;

	sf::RenderWindow Main::window;
	bool Main::hasFocus = true; // assumes window has focus by default
	unsigned long long Main::loopCicles = 0; // counts how many loops have passed

	Main::Main()
	{
		// measure system time for logging and stuff
		ng::Timer::measureSysTime();
	}

	void Main::run()
	{
		applyDefaultViewToWindow();
		// creates window with defined properties
		applySettingsToWindow();

		while (window.isOpen() && !closeWindow_)
		{
			loopCicles++;
			// measure delta time for each iteration
			ng::Timer::measureDeltaTime();
			// update system time
			ng::Timer::measureSysTime();

			while (window.pollEvent(event_))
			{
				// close window on request
				if (event_.type == sf::Event::Closed)
					window.close();
				else if (event_.type == sf::Event::GainedFocus)
					hasFocus = true;
				else if (event_.type == sf::Event::LostFocus)
					hasFocus = false;

				// client's events handling
				handleEvents();

				// enables use of ng::cursor::getPosition()
				ng::Cursor::followMouse(window);
			}

			// clear window of previous bs
			window.clear(windowClearColor);

			// client update
			update();

			// update subscribed audio's states
			ng::Audio::updateSubscriptionsState();

			// if any window settings change
			if (saveName_ != windowName ||
				saveType_ != windowType ||
				saveVideoMode_ != windowVideoMode)
			{
				// Actually change settings
				applySettingsToWindow();
			}

			// draw client's main level
			window.draw(*this);

			// draw cursor on top (if there is any)
			Cursor::draw(window);

			// display drawn things
			window.display();
		}
	}

	unsigned long long Main::getLoopCicleCount()
	{
		return loopCicles;
	}
	
	void Main::setWindowIcon(const std::string& location)
	{
		if (icon_.loadFromFile(location)) {
			window.setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());
			hasIcon_ = true;
		}
		else {
			NG_LOG_WARN("Failed to set Icon!");
			hasIcon_ = false;
		}
	}

	void Main::setWindowView(const sf::View& secondView)
	{
		window.setView(secondView);
	}

	void Main::applyDefaultViewToWindow()
	{
		window.setView(nginView_);
	}

	void Main::applySettingsToWindow()
	{
		sf::View windowView = window.getView();
		sf::Uint32 windowStyle = sf::Style::Titlebar;
		bool isBorderless = false;

		// --- Styling ---------------------------------
		if (windowType == WINDOW_TYPE::WINDOW_RESIZEABLE) {
			windowStyle = sf::Style::Default;
		}
		else if (windowType == WINDOW_TYPE::WINDOW_UNRESIZEABLE) {
			windowStyle = sf::Style::Titlebar | sf::Style::Close;
		}
		else if (windowType == WINDOW_TYPE::WINDOW_FULLSCREEN) {
			windowStyle = sf::Style::Fullscreen;
			windowVideoMode = sf::VideoMode::getDesktopMode();
		}
		else if (windowType == WINDOW_TYPE::WINDOW_BORDERLESS) {
			isBorderless = true;
			windowStyle = sf::Style::Fullscreen;
		}
		// ---------------------------------------------

		if (isBorderless) {
			window.create(windowVideoMode, windowName, sf::Style::Default);
			setWindowStyle(window, windowStyle);
			window.pollEvent(event_); // weird fix for weird bug but works
		}
		else {
			window.create(windowVideoMode, windowName, windowStyle);
		}
		
		// set view (back)
		window.setView(windowView);

		// set icon back
		if(hasIcon_)
			window.setIcon(icon_.getSize().x, icon_.getSize().y, icon_.getPixelsPtr());

		// save settings
		saveName_ = windowName;
		saveVideoMode_ = windowVideoMode;
		saveType_ = windowType;
	}

	void Main::setWindowStyle(sf::Window& window, sf::Uint32 style) const
	{
		HWND handle = window.getSystemHandle();
		DWORD win32Style = WS_VISIBLE;

		if (style == sf::Style::None)
		{
			win32Style |= WS_POPUP;
		}
		else
		{
			if (style & sf::Style::Titlebar) win32Style |= WS_CAPTION | WS_MINIMIZEBOX;
			if (style & sf::Style::Resize)   win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
			if (style & sf::Style::Close)    win32Style |= WS_SYSMENU;
		}

		SetWindowLongPtr(handle, GWL_STYLE, win32Style);

		// Force changes to take effect
		SetWindowPos(handle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
	}
}
