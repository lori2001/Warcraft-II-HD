#include "Cursor.h"
#include "../System/Console.h"

namespace ng {

	ng::SoundBufferPtr Cursor::soundBuffer_;
	ng::TexturePtr Cursor::texture_;

	sf::Sprite Cursor::sprite_;
	sf::Sound Cursor::sound_;
	bool Cursor::hasTexture_ = false;

	void Cursor::draw(sf::RenderWindow& window)
	{
		if(hasTexture_)
			window.draw(sprite_);
	}

	void Cursor::setTexture(const ng::TexturePtr texture)
	{
		texture_ = texture;
		sprite_.setTexture(*texture_);
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

	void Cursor::showDefault()
	{
		hasTexture_ = false;
	}

	void Cursor::showTextured()
	{
		if (sprite_.getTexture() != nullptr) {
			hasTexture_ = true;
		}
	}

	void Cursor::setBuffer(const ng::SoundBufferPtr soundBuffer)
	{
		soundBuffer_ = soundBuffer;
		sound_.setBuffer(*soundBuffer_);
	}

	void Cursor::playSound()
	{
		// avoid overlapping press sounds
		if (sound_.getStatus() != sf::Music::Status::Playing)
			sound_.play();
	}
}
