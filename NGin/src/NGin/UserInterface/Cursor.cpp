#include "Cursor.h"

namespace ngin {

	sf::Sprite Cursor::sprite_;
	sf::Sound Cursor::sound_;

	void Cursor::draw(sf::RenderWindow& window)
	{
		window.draw(sprite_);
	}

	void Cursor::setTexture(const sf::Texture& texture)
	{
		sprite_.setTexture(texture);
	}

	void Cursor::followMouse(sf::RenderWindow& window)
	{
		// sets sprite's coordinates to the mouse's position
		sprite_.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		if (sprite_.getTexture() != 0) {
			// disables default Cursor on a given window
			window.setMouseCursorVisible(false);
		}
	}

	void Cursor::setBuffer(sf::SoundBuffer& soundBuffer)
	{
		sound_.setBuffer(soundBuffer);
	}

	void Cursor::playSound()
	{
		// avoid overlapping press sounds
		if (sound_.getStatus() != sf::Music::Status::Playing)
			sound_.play();
	}
}
