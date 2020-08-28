#pragma once
#include "../System/Resources.h"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

namespace ng {
	class Cursor
	{
	public:
		static void draw(sf::RenderWindow& window);

		// texture of the mouse displayed
		static void setTexture(const ng::TexturePtr texture);

		static void setShape(const sf::RectangleShape& shape);

		static sf::RectangleShape getShape() { return shape_; }

		// this function returns the position of an element relative to the window
		// the cursor is set to. (needs void followMouse)
		static sf::Vector2f getPosition() { return shape_.getPosition(); }

		// IMPORTANT !!! ALL UI ELEMENTS DEPEND ON THIS FUNCTION!!!
		// updtates cursor's position relative to window
		// based on where the mouse is at at a given frame
		static void followMouse(sf::RenderWindow& window);

		// resets mouse to the default OS Look
		static void showDefault();
		// shows textured version of the mouse (if set)
		static void showTextured();

		static void setScale(const sf::Vector2f& scale);

		// sets the sound the cursor makes ex. when pressing a button 
		static void setBuffer(const ng::SoundBufferPtr soundBuffer);

		static sf::Sound* getSoundPtr() { return &sound_; }

		// plays the sound avoiding sound overlap with multiple clicks
		static void playSound();

	private:
		static ng::SoundBufferPtr soundBuffer_;
		static ng::TexturePtr texture_; // NOTE: NEVER get this

		static sf::RectangleShape shape_;
		static sf::Sound sound_;

		static bool displayShape_;
	};
}