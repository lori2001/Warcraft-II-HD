#include "EditorLevel.h"
#include "NGin/Levels/MainLevel.h"

void EditorLevel::setup()
{
	// -- Textures -----------------------------------------------------
	headerTexture_   = ngin::Resources::AcquireTexture("images/ui/header.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/dropdown.png");
	leaveButtonTexture_   = ngin::Resources::AcquireTexture("images/ui/leave_button.png");
	font_ = ngin::Resources::AcquireFont("fonts/normal.ttf");

	// reset cursor to OS-Default
	ngin::Cursor::resetToDefault();

	backButton_.setTexture(*leaveButtonTexture_);
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
	backButton_.setPosition({ 30, 980 });
	// ---------------------------------------------

	// --- Scales ----------------------------------
	backButton_.setScale({ 1.5F, 1.5F });
	editableMap_.setScale({ 2, 2 });
	// ---------------------------------------------

	// (re)set important bools
	mapEditor_ = false;

	// Map Editor setup
	editableMap_.setPosition({ 0.0F , headerSprite_.getGlobalBounds().top + headerSprite_.getGlobalBounds().height });
	GameDetails::mapFile.scanDir();

	// make view bindable so ui elements can stay always the same
	ngin::Bindables::create("mainView", ngin::MainLevel::view_.getCenter());
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
		mapEditor_ = true;
		editableMap_.setMapFile(GameDetails::mapFile);
		fileDropdown_.setActiveDrop(0);
	}

}

void EditorLevel::update()
{
	// viewport movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		ngin::MainLevel::view_.move({ -viewMoveSpeed, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		ngin::MainLevel::view_.move({ viewMoveSpeed, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		ngin::MainLevel::view_.move({ 0, -viewMoveSpeed});
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		ngin::MainLevel::view_.move({ 0, viewMoveSpeed});
	}

	ngin::Bindables::bindPosition(fileDropdown_, "mainView", ngin::MainLevel::view_.getCenter());
	ngin::Bindables::bindPosition(headerSprite_, "mainView", ngin::MainLevel::view_.getCenter());
	ngin::Bindables::bindPosition(backButton_, "mainView", ngin::MainLevel::view_.getCenter());
}

void EditorLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mapEditor_)
		target.draw(editableMap_);

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
