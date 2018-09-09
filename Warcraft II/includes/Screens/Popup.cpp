#include "Popup.h"

namespace Screens
{
	void Popup::animateCountdown()
	{
		float time = resetclock.getElapsedTime().asSeconds();
		resetclock.restart();
		resettimer += time;

		countdown.setString(std::to_string(int(resetlimit - resettimer)));
		this->countdown.setOrigin(this->countdown.getLocalBounds().left + this->countdown.getLocalBounds().width / 2.0f,
			this->countdown.getLocalBounds().top + this->countdown.getLocalBounds().height / 2.0f);

		if (resetlimit - resettimer <= 0)
		{
			//sends signal that countdown reached 0
			countdownOver = true;

			//resets clock
			resettimer = 0;
			resetclock.restart();
		}
	}
	void Popup::handleInput(const sf::Event & event, const sf::Vector2f & mouse)
	{
		cancel.handleInput(event, loading.pressbutton);
		ok.handleInput(event, loading.pressbutton);

		cancel.setSelected(mouse);
		ok.setSelected(mouse);
	}
	void Popup::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(popupS, states);
		target.draw(cancel, states);
		target.draw(ok, states);

		for(short i = 0; i < descriptionsnr; i++)
			target.draw(descriptions[i], states);

		target.draw(countdown, states);
	}
	void Popup::setPosition(const sf::Vector2f & position)
	{
		//converts (for example) 1920x1080 - scale to 1000x600 | this was used in previous versions in a direct way
		//basically adjusts scale proportinons the right way
		sf::Vector2f scale{ popupS.getScale().x * 1.92f ,popupS.getScale().y * 1.8f};

		popupS.setPosition(position.x, position.y);
		cancel.setPosition(sf::Vector2f(popupS.getPosition().x - 120 * scale.x, popupS.getPosition().y + 23 * scale.y));
		ok.setPosition(sf::Vector2f(popupS.getPosition().x + 120 * scale.x, popupS.getPosition().y + 23 * scale.y));

		//default text positions
		countdown.setPosition(sf::Vector2f(popupS.getPosition().x + 30 * scale.x, popupS.getPosition().y + 23 * scale.y));
		for (short i = 0; i < descriptionsnr; i++)
			descriptions[i].setPosition(sf::Vector2f(popupS.getPosition().x - 10 * scale.x, popupS.getPosition().y - 18 * scale.y));
	}
	void Popup::setScale(const sf::Vector2f & scale)
	{
		//set proper scales
		popupS.setScale(scale);
		cancel.setScale(sf::Vector2f(scale.x / 3, scale.y));
		ok.setScale(sf::Vector2f(scale.x / 3, scale.y));

		countdown.setCharacterSize(int(31 * scale.x));
		//centers text according to the new scale
		this->countdown.setOrigin(this->countdown.getLocalBounds().left + this->countdown.getLocalBounds().width / 2.0f,
			this->countdown.getLocalBounds().top + this->countdown.getLocalBounds().height / 2.0f);

		for (short i = 0; i < descriptionsnr; i++)
		{
			descriptions[i].setCharacterSize(int(31 * scale.x));
			//centers text according to the new scale
			this->descriptions[i].setOrigin(this->descriptions[i].getLocalBounds().left + this->descriptions[i].getLocalBounds().width / 2.0f,
				this->descriptions[i].getLocalBounds().top + this->descriptions[i].getLocalBounds().height / 2.0f);
		}
	}
	void Popup::setDescription(const int & i, const std::string & text)
	{
		descriptions[i].setString(text);
		//centers text according to the new scale
		this->descriptions[i].setOrigin(this->descriptions[i].getLocalBounds().left + this->descriptions[i].getLocalBounds().width / 2.0f,
			this->descriptions[i].getLocalBounds().top + this->descriptions[i].getLocalBounds().height / 2.0f);
	}
	void Popup::setDescriptionPos(const int & i, const sf::Vector2f & relativepos)
	{
		//makes sure values are in the expected area.
		assert(0 <= relativepos.x && relativepos.x <= 1);
		assert(0 <= relativepos.y && relativepos.y <= 1);

		descriptions[i].setPosition((popupS.getPosition().x - (popupS.getSize().x * popupS.getScale().x) / 2) + size.x * popupS.getScale().x * relativepos.x,
									(popupS.getPosition().y - (popupS.getSize().y * popupS.getScale().y) / 2) + size.y * popupS.getScale().y * relativepos.y);
	}
	void Popup::setCountdownPos(const sf::Vector2f & relativepos)
	{
		//makes sure values are in the expected area.
		assert(0 <= relativepos.x && relativepos.x <= 1);
		assert(0 <= relativepos.y && relativepos.y <= 1);

		countdown.setPosition((popupS.getPosition().x - (popupS.getSize().x * popupS.getScale().x) / 2) + size.x * popupS.getScale().x * relativepos.x,
							  (popupS.getPosition().y - (popupS.getSize().y * popupS.getScale().y) / 2) + size.y * popupS.getScale().y * relativepos.y);
	}
}