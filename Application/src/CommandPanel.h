#pragma once
#include "NGin.h"

#include "Style.h"
#include "GameEntity.h"

class CommandPanel : public sf::Drawable {
public:
	enum class OPTION {
		WARRIOR,
		ARCHER
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);

	void setOptionsFor(GameEntity& gameEntity);
	void clearAllOptions();

private:

	void addOption(const OPTION option, const unsigned slot);
	void removeOption(const OPTION option);

	ng::TexturePtr iconsTexture_ = NG_TEXTURE_SPTR(location::ICONS);
	
	std::unordered_map<OPTION, sf::RectangleShape> icons_;

	sf::FloatRect area_{10.0F, 370.0F, 432.0F, 615.0F};

	const int numberOfSlots_ = 6;
};