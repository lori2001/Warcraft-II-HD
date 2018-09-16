#pragma once
#include "SFML\Graphics.hpp"
#include "..\Window.h"

namespace Sections 
{
	class MainView
	{
	private:

	public:
		void Setup();
		void handleInput(const sf::Event &event);
		void Update();
		void Compose();
	};
}