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

		for(unsigned int i = 0; i < descriptionsnr; i++)
			target.draw(descriptions[i], states);

		target.draw(countdown, states);
	}
	void Popup::setPosition(const sf::Vector2f & position)
	{
		popupS.setPosition(position.x, position.y);
		cancel.setPosition(sf::Vector2f(popupS.getPosition().x - 240, popupS.getPosition().y + 50));
		ok.setPosition(sf::Vector2f(popupS.getPosition().x + 240, popupS.getPosition().y + 50));

		//default text positions
		countdown.setPosition(sf::Vector2f(popupS.getPosition().x + 30, popupS.getPosition().y + 23));

		for (unsigned int i = 0; i < descriptionsnr; i++) {
			if (descriptions[i].getPosition().x == 0 && descriptions[i].getPosition().y == 0) {
				descriptions[i].setPosition(sf::Vector2f(popupS.getPosition().x - 10, popupS.getPosition().y - 18));
			}
		}
	}
	void Popup::setScale(const sf::Vector2f & scale)
	{
		//set proper scales
		popupS.setScale(scale);
		cancel.setScale(sf::Vector2f(scale.x / 3, scale.y));
		ok.setScale(sf::Vector2f(scale.x / 3, scale.y));

		countdown.setCharacterSize(int(28 * scale.x));
		//centers text according to the new scale
		this->countdown.setOrigin(this->countdown.getLocalBounds().left + this->countdown.getLocalBounds().width / 2.0f,
			this->countdown.getLocalBounds().top + this->countdown.getLocalBounds().height / 2.0f);

		for (unsigned int i = 0; i < descriptionsnr; i++)
		{
			descriptions[i].setCharacterSize(int(28 * scale.x));
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