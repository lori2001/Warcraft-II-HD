#include "TilePainter.h"
#include "../Common/GameDetails.h"

void TilePainter::setup()
{
	// --- Load Textures -------------------------
	scrollBoxTexture_ = NG_TEXTURE_PTR("images/ui/scrollbox.png");
	themeTexture_ = ngin::Resources::AcquireTexture(GameDetails::mapFile.getThemeLocation());
	// -------------------------------------------

	// --- Set Textures And Fonts ----------------
	scrollBox_.setTexture(*scrollBoxTexture_);
	// -------------------------------------------

	//--- Break texture into tiles ---------------
	sf::Image analyzer; // makes sure no empty tiles are read
	analyzer.loadFromFile(ngin::Resources::getLocation() + GameDetails::mapFile.getThemeLocation());

	// make sure tiles' vectors are empty
	tiles_.clear();
	tileIndexes_.clear();
	const sf::Vector2f tileSize = GameDetails::mapFile.getTileSize();
	int i = 0;
	for (float y = 0; y <= themeTexture_->getSize().y - tileSize.y; y += tileSize.y + 1)
	{
		for (float x = 0; x <= themeTexture_->getSize().x - tileSize.x; x += tileSize.x + 1)
		{
			// only set if pixels are not empty
			if (static_cast<int>(analyzer.getPixel(x, y).a) != 0)
			{
				tiles_.push_back(sf::RectangleShape{});
				tileIndexes_.push_back(i);

				tiles_.back().setTexture(&*themeTexture_);
				tiles_.back().setTextureRect({
					static_cast<int>(x),
					static_cast<int>(y),
					static_cast<int>(tileSize.x),
					static_cast<int>(tileSize.y) });
				tiles_.back().setSize(tileSize);
				tiles_.back().setScale({ ngin::ftoVec(tilesScale_) });
				tiles_.back().setOutlineColor(selectionColor_);
			}
			i++;
		}
	}
	// -------------------------------------------

	// -- Add tiles to ScrollBox -----------------
	// WARNING: overwrites positon properties
	// WARNING: makes scrollbox responsible for drawing tiles-vector*/
	scrollBox_.clearElements(); // clear non-valid pointers

	const float tilesHeight = tilesTopGap_ + tilesOffset_.y * ((tiles_.size() - 1) / tilesRows_) +
		(GameDetails::mapFile.getTileSize().y * tilesScale_);

	scrollBox_.setInsideSize({ scrollBox_.getOutsideSize().x, tilesHeight + 50 });

	for (int i = 0; i < tiles_.size(); i++) {

		sf::Vector2f currTilePosition =
			   { tilesLeftGap_ + tilesOffset_.x * (i % tilesRows_),
				 tilesTopGap_  + tilesOffset_.y * (i / tilesRows_) };

		scrollBox_.addElement(tiles_[i], currTilePosition);
	}
	scrollBox_.setScrollSpeed(0.05F);
	// -------------------------------------------
}

void TilePainter::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	scrollBox_.setSelectColor(themeColor);
	selectionColor_ = themeColor;
}

void TilePainter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scrollBox_);
}

void TilePainter::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	scrollBox_.handleEvents(event, mouse);
	
	for (auto& it : tiles_) {
		if (it.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }))) {
			it.setOutlineThickness(selectionThickness_);
		}
		else {
			it.setOutlineThickness(0);
		}
	}
}

void TilePainter::setPosition(const sf::Vector2f& position)
{
	scrollBox_.setPosition(position);
}
