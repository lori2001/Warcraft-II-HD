#include "CommandPanel.h"

void CommandPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape test;
	test.setFillColor(sf::Color{ 0, 0, 255, 100 });
	test.setPosition({area_.left, area_.top });
	test.setSize({ area_.width, area_.height});
	
	target.draw(test);

	for (auto &it : icons_) {
		target.draw(it.second);
	}
}

void CommandPanel::handleEvents(const sf::Event& event)
{


}

void CommandPanel::addOption(const OPTION option)
{
	sf::RectangleShape test;
	test.setSize({20, 20});
	test.setFillColor(sf::Color::Red);
	test.setPosition({ area_.left, area_.top});

	icons_.insert({ option , test });
}

void CommandPanel::removeOption(const OPTION option)
{
	icons_.erase(option);
}

void CommandPanel::clearAllOptions()
{
	icons_.clear();
}
