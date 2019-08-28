#include "MainLevel.h"
#include <Windows.h>

namespace ngin {

	void MainLevel::run()
	{
		// creates window with defined preperties
		applySettingsToWindow();

		// measure system time for logging and stuff
		ngin::Timer::measureSysTime();

		// client's setup
		setup();

		while (window_.isOpen())
		{
			// measure delta time for each iteration
			ngin::Timer::measureDeltaTime();

			while (window_.pollEvent(event_))
			{
				// close window on request
				if (event_.type == sf::Event::Closed)
					window_.close();

				// client's events handling
				handleEvents();

				// enables use of ngin::cursor::getPosition()
				ngin::Cursor::followMouse(window_);
			}

			// clear window from previous bs
			window_.clear();

			// client update
			update();

			// update subscribed audio's states
			ngin::Audio::updateSubscriptionsState();

			// if any window settings change
			if (saveName_ != windowName_ ||
				saveType_ != windowType_ ||
				saveVideoMode_ != windowVideoMode_)
			{
				// Actually change settings
				applySettingsToWindow();
			}

			// draw client's main level
			window_.draw(*this);

			// draw cursor on top (if there is any)
			Cursor::draw(window_);

			// display drawn things
			window_.display();
		}
	}

	void MainLevel::applySettingsToWindow()
	{
		// prevents destroying window's view
		const sf::View saveView = window_.getView();

		sf::Uint32 windowStyle = sf::Style::Titlebar;
		bool isBorderless = false;

		// --- Styling ---------------------------------
		if (windowType_ == WINDOW_TYPE::RESIZEABLE) {
			windowStyle = sf::Style::Default;
		}
		else if (windowType_ == WINDOW_TYPE::UNRESIZEABLE) {
			windowStyle = sf::Style::Titlebar | sf::Style::Close;
		}
		else if (windowType_ == WINDOW_TYPE::FULLSCREEN) {
			windowStyle = sf::Style::Fullscreen;
			windowVideoMode_ = sf::VideoMode::getDesktopMode();
		}
		else if (windowType_ == WINDOW_TYPE::BORDERLESS) {
			isBorderless = true;
			windowStyle = sf::Style::Fullscreen;
		}
		// ---------------------------------------------

		if (isBorderless) {
			window_.create(windowVideoMode_, windowName_, sf::Style::Default);
			setWindowStyle(window_, windowStyle);
			window_.pollEvent(event_); // weird fix for weird bug but works
		}
		else {
			window_.create(windowVideoMode_, windowName_, windowStyle);
		}

		// set view back
		window_.setView(saveView);

		// save settings
		saveName_ = windowName_;
		saveVideoMode_ = windowVideoMode_;
		saveType_ = windowType_;
	}

	void MainLevel::setWindowStyle(sf::Window& window, sf::Uint32 style) const
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
