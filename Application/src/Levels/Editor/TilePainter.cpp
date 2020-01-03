#include "TilePainter.h"

void TilePainter::setupWithTheme(const std::string& themeLocation, const sf::Vector2f& tileSize)
{
	// --- Load Textures -------------------------
	backgroundTexture_ = ngin::Resources::AcquireTexture("images/ui/orc_clay_bg.png");
	// -------------------------------------------

	// --- Set Sizes -----------------------------
	backgroundShape_.setSize({ 400, 1000 });
	// -------------------------------------------

	// --- Set Textures And Fonts ----------------
	backgroundShape_.setTexture(&*backgroundTexture_);
	backgroundShape_.setTextureRect({ 0, 0, 312, 780 });
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
	target.draw(backgroundShape_);
	target.draw(titleText_);
}

void TilePainter::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
}

void TilePainter::setPosition(const sf::Vector2f& position)
{
	backgroundShape_.setPosition(position);
	ngin::centerTextInShape(titleText_, backgroundShape_,
		-backgroundShape_.getGlobalBounds().height / 2 + 40);
}
