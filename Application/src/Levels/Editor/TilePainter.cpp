#include "TilePainter.h"
#include "../Common/GameDetails.h"

void TilePainter::setup()
{
	// --- Load Textures -------------------------
	backgroundTexture_ = ngin::Resources::AcquireTexture("images/ui/orc_clay_bg.png");
	themeTexture_ = ngin::Resources::AcquireTexture(GameDetails::mapFile.getThemeLocation());
	// -------------------------------------------

	// --- Set Sizes -----------------------------
	background_.setSize(backgroundSize_);
	// -------------------------------------------

	// --- Set Textures And Fonts ----------------
	background_.setTexture(&*backgroundTexture_);
	// scale smaller texture to bigger shape to avoid distortion
	background_.setTextureRect({ 0, 0,
		static_cast<int>((backgroundTexture_->getSize().y * backgroundSize_.x) / backgroundSize_.y),
		static_cast<int>(backgroundTexture_->getSize().y)});
	// -------------------------------------------

	//--- Break texture into tiles ---------------
	sf::Image analyzer;
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
			if (analyzer.getPixel(x, y).a != 0)
			{
				sf::RectangleShape temp;
				temp.setTexture(&*themeTexture_);
				temp.setTextureRect({
					static_cast<int>(x),
					static_cast<int>(y),
					static_cast<int>(tileSize.x),
					static_cast<int>(tileSize.y) });
				temp.setSize(tileSize);
				background_.getGlobalBounds().top;
				temp.setScale({ ngin::ftoVec(tilesScale_) });
				temp.setOutlineColor(selectionColor_);

				tiles_.push_back(temp);
				tileIndexes_.push_back(i);
			}
			i++;
		}
	}
	// -------------------------------------------

	// --- Properties ----------------------------
	titleText_.setString("Tile Painter");
	// -------------------------------------------
}

void TilePainter::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	titleText_.setFont(font);
	titleText_.setCharacterSize(fontSize);
	titleText_.setFillColor(themeColor);
}

void TilePainter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_);
	target.draw(titleText_);

	for (int i = 0; i < tiles_.size(); i++) {
		target.draw(tiles_[i]);
	}
}

void TilePainter::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
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
	background_.setPosition(position);

	const float backgroundTop = -background_.getGlobalBounds().height / 2;
	ngin::centerTextInShape(titleText_, background_, backgroundTop + titleTextTopGap_);

	// width of the grid of tiles
	const float tilesWidth = tilesOffset_.x * (tilesRows_ - 1) + (GameDetails::mapFile.getTileSize().x * tilesScale_);
	// x-position of left anchor which leads to centered grid of tiles on background
	const float xPosition = position.x + (background_.getGlobalBounds().width - tilesWidth) / 2;
	// y-position of top anchor with some offset ont background at top for other elements
	const float yPosition = position.y + tilesTopGap_;

	for (int i = 0; i < tiles_.size(); i++)
	{
		tiles_[i].setPosition(
			{ xPosition + (tilesOffset_.x * (i % tilesRows_)),
			  yPosition + (tilesOffset_.y * (i / tilesRows_))});
	}
}
