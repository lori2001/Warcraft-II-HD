#pragma once
#include "NGin.h"

#include "Map.h"
#include "Style.h"

#include "GameEntity.h"
#include "CommandPanel.h"

class Barracks : public sf::Drawable, public GameEntity {
public:
	Barracks(const sf::Vector2i& tilePosition) {
		NG_LOG_ERROR(MapFile::getTileSize());
		shape_.setPosition({ Map::getScaledTileSize().x * tilePosition.x, Map::getScaledTileSize().y * tilePosition.y });
		shape_.setSize({ static_cast<float>(textureRect_.width), static_cast<float>(textureRect_.height) });
		shape_.setTexture(&*texture_);
		shape_.setTextureRect(textureRect_);

		shape_.setOutlineColor({ color::IN_GAME_SELECT_R, color::IN_GAME_SELECT_G, color::IN_GAME_SELECT_B });


		// init game entity
		spawnLocation_ = shape_.getPosition();
		NG_LOG_ERROR(spawnLocation_);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(shape_);
	}

	void handleEvents(const sf::Event& event, const sf::FloatRect& mouseRect, CommandPanel& commandPanel) {

		if (state_ != STATES::ACTIVE) {
			if (shape_.getGlobalBounds().intersects(mouseRect)) {
				shape_.setOutlineThickness(size::IN_GAME_OUTLINE_THICKNESS);

				if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {
					state_ = STATES::ACTIVE;

					// intialize command panel
					// TODO proper
					commandPanel.setOptionsFor(*this);
				}

			}
			else {
				shape_.setOutlineThickness(0);
			}

		}
		else {
			shape_.setOutlineThickness(size::IN_GAME_OUTLINE_THICKNESS);

			if (event.type == sf::Event::MouseButtonPressed && !shape_.getGlobalBounds().intersects(mouseRect)) {
				state_ = STATES::NONE;
			}
		}
		
	}

private:
	const sf::IntRect textureRect_ = { 5, 5, 122, 116 };

	enum class STATES {
		NONE = 0,
		CONSTRUCTION,
		SELECTED,
		ACTIVE,
	} state_ = STATES::NONE;

	const ng::TexturePtr texture_ = NG_TEXTURE_SPTR("images/buildings/human_buildings_summer.png");
};