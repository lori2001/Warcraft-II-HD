#pragma once
#include "NGin.h"
#include "ColoredString.h"

class PlayerLine : public ngin::UIElement {
public:
	ngin::InputText nameInput;
	ngin::Dropdown raceDropdown{ { 277, 40 } };
	ngin::Dropdown teamDropdown{ { 277, 40 } };
	ngin::Dropdown colorDropdown{ { 277, 40 } };

	void setPosition(const sf::Vector2f& position);
	void setTheme(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);
	// sets dropdown.isRepeated to true
	void setTextures(const sf::Texture& inputText, sf::Texture& dropdown);

	void setupStrings(const std::vector<ColoredString>& races,
					  const std::vector<std::string>& teams,
					  const std::vector<sf::Color>& colors);

	void addToPlayers(const std::vector<ColoredString>& races,
					   const std::vector<std::string>& teams,
					   const std::vector<sf::Color>& colors);

	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};