#include "Cursor.h"
#include "../System/Console.h"

#include <memory.h>

namespace ng {

	ng::SoundBufferPtr Cursor::soundBuffer_;
	ng::TexturePtr Cursor::texture_;

	sf::RectangleShape Cursor::shape_;
	sf::Sound Cursor::sound_;
	bool Cursor::displayShape_ = false;

	void Cursor::draw(sf::RenderWindow& window)
	{
		if(displayShape_)
			window.draw(shape_);
	}

	void Cursor::setTexture(const ng::TexturePtr texture)
	{
		texture_ = texture;
		shape_.setTexture(&*texture_);
		shape_.setSize(sf::Vector2f{ texture_->getSize() });

		displayShape_ = true;
	}

	void Cursor::setShape(const sf::RectangleShape& shape)
	{
		shape_ = shape;
		displayShape_ = true;
	}

	void Cursor::followMouse(sf::RenderWindow& window)
	{
		// sets sprite's coordinates to the mouse's position
		shape_.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		if (displayShape_) {
			// disables default Cursor on a given window
			window.setMouseCursorVisible(false);
		}
		else {
			window.setMouseCursorVisible(true);
		}
	}

	void Cursor::showDefault()
	{
		displayShape_ = false;
	}

	void Cursor::showTextured()
	{
		if (shape_.getTexture() != nullptr) {
			displayShape_ = true;
		}
	}

	void Cursor::setScale(const sf::Vector2f& scale)
	{
		shape_.setScale(scale);
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
