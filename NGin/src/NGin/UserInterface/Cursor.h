#pragma once
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

namespace ngin {
	class Cursor
	{
	public:
		static void draw(sf::RenderWindow& window);

		// texture of the mouse displayed
		static void setTexture(const sf::Texture& texture);

		// this function returns the position of an element relative to the window
		// the cursor is set to. (needs void followMouse)
		static sf::Vector2f getPosition() { return sprite_.getPosition(); }

		// IMPORTANT !!! ALL UI ELEMENTS DEPEND ON THIS FUNCTION!!!
		// updtates cursor's position relative to window
		// based on where the mouse is at at a given frame
		static void followMouse(sf::RenderWindow& window);

		// resets mouse to the default OS Look
		static void resetToDefault();

		// sets the sound the cursor makes ex. when pressing a button 
		static void setBuffer(sf::SoundBuffer& soundBuffer);

		static sf::Sound* getSoundPtr() { return &sound_; }

		// plays the sound avoiding sound overlap with multiple clicks
		static void playSound();

	private:
		static sf::Sprite sprite_;
		static sf::Sound sound_;

		static bool hasTexture_;
	};
}