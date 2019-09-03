#include "EditorLevel.h"
#include "nfd.h"

void EditorLevel::setup()
{
	// -- Textures -----------------------------------------------------
	headerTexture_   = ngin::Resources::AcquireTexture("images/ui/header.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/dropdown.png");
	buttonTexture_   = ngin::Resources::AcquireTexture("images/ui/button.png");
	font_ = ngin::Resources::AcquireFont("fonts/normal.ttf");

	// reset cursor to OS-Default
	ngin::Cursor::resetToDefault();

	backButton_.setTexture(*buttonTexture_);
	headerSprite_.setTexture(*headerTexture_);
	fileDropdown_.setTexture(*dropdownTexture_);
	// -----------------------------------------------------------------

	setupUIStyle(*font_, 40, sf::Color::Yellow);

	// --- Strings ---------------------------------
	fileDropdown_.setDropString(0, "File");
	fileDropdown_.addDropString("New");
	fileDropdown_.addDropString("Load");
	fileDropdown_.addDropString("Save");
	fileDropdown_.setStatic(true);
	// ---------------------------------------------

	// --- Positions -------------------------------
	fileDropdown_.setPosition({ 50, 5});
	backButton_.setPosition({ 105, 965 });
	// ---------------------------------------------

	GameDetails::mapFile.scanDir();
}

void EditorLevel::handleEvents(const sf::Event& event)
{
	backButton_.handleEvents(event, ngin::Cursor::getPosition());
	fileDropdown_.handleEvents(event, ngin::Cursor::getPosition());

	if (backButton_.isActive()) {
		response_ = RESPONSE::MAIN_MENU;
	}
	else {
		response_ = RESPONSE::NONE;
	}

	if (fileDropdown_.getActiveDrop() == 2) // Load
	{
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog("mapfile", GameDetails::mapFile.getFolderPath().c_str(), &outPath);

		if (result == NFD_OKAY){
			GameDetails::mapFile.read(outPath);
			NG_LOG_INFO(GameDetails::mapFile.getMapName());
		}
		else if (result == NFD_ERROR) {
			NG_LOG_ERROR("Error: %s\n", NFD_GetError());
		}

		fileDropdown_.setActiveDrop(0);
	}

}

void EditorLevel::update()
{
}

void EditorLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(headerSprite_);
	target.draw(fileDropdown_);
	target.draw(backButton_);
}

void EditorLevel::setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor)
{
	backButton_.setFont(font);
	backButton_.setCharacterSize(fontSize);
	backButton_.setTextColor(themeColor);
	backButton_.setSelectColor(themeColor);

	fileDropdown_.setFont(font);
	fileDropdown_.setCharacterSize(fontSize);
	fileDropdown_.setTextColor(themeColor);
	fileDropdown_.setSelectColor(themeColor);
	fileDropdown_.setHighlightColor({ themeColor.r, themeColor.g, themeColor.b, 80 });
}