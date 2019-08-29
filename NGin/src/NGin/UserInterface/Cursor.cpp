#include "Cursor.h"

namespace ngin {

	sf::Sprite Cursor::sprite_;
	sf::Sound Cursor::sound_;
	bool Cursor::hasTexture_ = false;

	void Cursor::draw(sf::RenderWindow& window)
	{
		if(hasTexture_)
			window.draw(sprite_);
	}

	void Cursor::setTexture(const sf::Texture& texture)
	{
		sprite_.setTexture(texture);
		hasTexture_ = true;
	}

	void Cursor::followMouse(sf::RenderWindow& window)
	{
		// sets sprite's coordinates to the mouse's position
		sprite_.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		if (hasTexture_) {
			// disables default Cursor on a given window
			window.setMouseCursorVisible(false);
		}
		else {
			window.setMouseCursorVisible(true);
		}
	}

	void Cursor::resetToDefault()
	{
		hasTexture_ = false;
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
