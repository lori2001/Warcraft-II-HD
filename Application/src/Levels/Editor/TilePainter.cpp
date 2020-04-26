#include "TilePainter.h"
#include "../Common/GameDetails.h"

void TilePainter::setup()
{
	// --- Load Textures -------------------------
	scrollBoxTexture_ = NG_TEXTURE_SPTR("images/ui/scrollbox.png");
	themeTexture_ = NG_TEXTURE_SPTR(GameDetails::mapFile.getThemeLocation());
	// -------------------------------------------

	// --- Set Textures And Fonts ----------------
	scrollBox_.setTexture(*scrollBoxTexture_);
	// -------------------------------------------

	//--- Break texture into tiles ---------------
	sf::Image analyzer; // makes sure no empty tiles are read
	analyzer.loadFromFile(ng::Resources::getLocation() + GameDetails::mapFile.getThemeLocation());

	// make sure tiles' vectors are empty
	tiles_.clear();
	tileIndexes_.clear();
	tileIndexTexts_.clear(); // clear display index texts
	const sf::Vector2f tileSize = GameDetails::mapFile.getTileSize();
	int i = 0;
	for (float y = 0; y <= themeTexture_->getSize().y - tileSize.y; y += tileSize.y + 1)
	{
		for (float x = 0; x <= themeTexture_->getSize().x - tileSize.x; x += tileSize.x + 1)
		{
			// only set if pixels are not empty
			if (static_cast<int>(analyzer.getPixel(static_cast<unsigned>(x), static_cast<unsigned>(y)).a) != 0)
			{
				tiles_.push_back(sf::RectangleShape{});
				tileIndexTexts_.push_back(sf::Text{});
				tileIndexes_.push_back(i);

				tiles_.back().setTexture(&*themeTexture_);
				tiles_.back().setTextureRect({
					static_cast<int>(x),
					static_cast<int>(y),
					static_cast<int>(tileSize.x),
					static_cast<int>(tileSize.y) });
				tiles_.back().setSize(tileSize);
				tiles_.back().setScale({ ng::ftovec(tilesScale_) });
				tiles_.back().setOutlineColor(selectionColor_);

				// inherit text style from title
				tileIndexTexts_.back().setFont(*title_.getFont());
				tileIndexTexts_.back().setCharacterSize(title_.getCharacterSize() - 5);
				tileIndexTexts_.back().setFillColor(title_.getFillColor());
				tileIndexTexts_.back().setString(std::to_string(i)); // set string to index
			}
			i++;
		}
	}
	// -------------------------------------------

	// WARNING: overwrites positon properties
	// WARNING: makes scrollbox responsible for drawing tiles-vector*/
	scrollBox_.clearElements(); // clear non-valid pointers

	// -- Add elements to ScrollBox ------------
	const float tilesHeight = tilesTopGap_ + tilesOffset_.y * ((tiles_.size() - 1) / tilesRows_) +
		(GameDetails::mapFile.getTileSize().y * tilesScale_);

	scrollBox_.setInsideSize({ scrollBox_.getOutsideSize().x, tilesHeight + 50 });

	// Add Title
	title_.setString("Tile Painter");
	ng::centerTextInBounds(title_, scrollBox_.getGlobalBounds(),
		50 - scrollBox_.getGlobalBounds().height / 2);
	scrollBox_.addElement(title_);
	
	for (int i = 0; i < int(tiles_.size()); i++)
	{
		sf::Vector2f currTilePosition =
			   { tilesLeftGap_ + tilesOffset_.x * (i % tilesRows_),
				 tilesTopGap_  + tilesOffset_.y * (i / tilesRows_) };

		scrollBox_.addElement(tiles_[i], currTilePosition); // add tile
		scrollBox_.addElement(tileIndexTexts_[i], { currTilePosition.x, currTilePosition.y - 18 }); // add tile text
	}
	// -------------------------------------------

	// --- Other Properties --------------
	scrollBox_.setScrollSpeed(0.03F);
	// -----------------------------------
}

void TilePainter::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	scrollBox_.setSelectColor(themeColor);
	selectionColor_ = themeColor;

	title_.setFont(font);
	title_.setCharacterSize(fontSize);
	title_.setFillColor(themeColor);
}

void TilePainter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(scrollBox_);
}

void TilePainter::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	scrollBox_.handleEvents(event, mouse);
	
	for (int i = 0; i < static_cast<int>(tiles_.size()); i++) {
		if (tiles_[i].getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }))) {
			tiles_[i].setOutlineThickness(selectionThickness_);

			if (event.mouseButton.button == sf::Mouse::Left &&
				event.type == sf::Event::MouseButtonReleased) {
				usingTile_ = tileIndexes_[i];
			}
		}
		else {
			tiles_[i].setOutlineThickness(0);
		}

		// using tiles
		if (tileIndexes_[i] == usingTile_) {
			tiles_[i].setFillColor({ 255, 255, 0, 255 });
		}
		else {
			tiles_[i].setFillColor({ 255, 255, 255, 255 });
		}
	}
}

void TilePainter::setPosition(const sf::Vector2f& position)
{
	scrollBox_.setPosition(position);
}
