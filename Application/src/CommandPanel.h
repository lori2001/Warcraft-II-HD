#pragma once
#include "NGin.h"

#include "Style.h"

class CommandPanel : public sf::Drawable {
public:
	enum class OPTION {
		WORKER
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvents(const sf::Event& event);

	void addOption(const OPTION option);
	void removeOption(const OPTION option);
	void clearAllOptions();

private:
	ng::TexturePtr iconsTexture_ = NG_TEXTURE_SPTR(location::ICONS);
	
	std::unordered_map<OPTION, sf::RectangleShape> icons_;

	sf::FloatRect area_{10.0F, 370.0F, 432.0F, 615.0F};
};