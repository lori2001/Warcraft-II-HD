#include "CommandPanel.h"

void CommandPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape test;
	test.setFillColor(sf::Color{ 0, 0, 255, 100 });
	test.setPosition({area_.left, area_.top });
	test.setSize({ area_.width, area_.height});
	
	target.draw(test);
}

void CommandPanel::handleEvents(const sf::Event& event)
{


}
