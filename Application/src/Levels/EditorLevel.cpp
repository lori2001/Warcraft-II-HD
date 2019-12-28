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

	// --- Positions -------------------
	fileDropdown_.setPosition({ 50 , 5 });
	backButton_.setPosition({ 30, 980 });
	// ---------------------------------------------

	// (re)set important bools
	mapEditor_ = false;

	NG_LOG_ERROR(headerSprite_.getGlobalBounds().top +
		headerSprite_.getGlobalBounds().height);

	GameDetails::mapFile.scanDir();

	// change window background to a milder color
	ngin::MainLevel::windowClearColor_ = { 50, 50, 50 };
}

void EditorLevel::handleEvents(const sf::Event& event)
{
	backButton_.handleEvents(event, ngin::Cursor::getPosition());
	fileDropdown_.handleEvents(event, ngin::Cursor::getPosition());

	if (backButton_.isActive()) {
		ngin::MainLevel::windowClearColor_ = { 0, 0, 0 };
		response_ = RESPONSE::MAIN_MENU;
	}
	else {
		response_ = RESPONSE::NONE;
	}

	if (fileDropdown_.getActiveDrop() == 2) // Load
	{
		mapEditor_ = true;
		editableMap_.setMapFile(GameDetails::mapFile);
		
		// (re)set presumably moved map
		editorZoom_ = 2.0F;
		editableMap_.setScale(ngin::ftoVec(editorZoom_));
		editableMap_.setOrigin({ editableMap_.getLocalBounds().width / 2,
			                     editableMap_.getLocalBounds().height / 2 });
		editableMap_.setPosition({
			editableMap_.getScaledSize().x / 2,
			editableMap_.getScaledSize().y / 2 +
			headerSprite_.getGlobalBounds().top +
			headerSprite_.getGlobalBounds().height });

		fileDropdown_.setActiveDrop(0);
	}

	// editor zoom
	if (event.type == sf::Event::MouseWheelMoved)
	{
		editorZoom_ += event.mouseWheel.delta * editorZoomSpeed_;

		if (editorZoom_ > editorMaxZoom_) {
			editorZoom_ = editorMaxZoom_;
		}
		else if(editorZoom_ < editorMinZoom_){
			editorZoom_ = editorMinZoom_;
		}

		editableMap_.setScale(ngin::ftoVec(editorZoom_));
	}

}

void EditorLevel::update()
{
	if (ngin::MainLevel::windowHasFocus())
	{
		// viewport movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			editableMap_.move({ editorMoveSpeed_ * ngin::Timer::getDeltaTime(), 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			editableMap_.move({ -editorMoveSpeed_ * ngin::Timer::getDeltaTime(), 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			editableMap_.move({ 0, editorMoveSpeed_ * ngin::Timer::getDeltaTime() });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			editableMap_.move({ 0, -editorMoveSpeed_ * ngin::Timer::getDeltaTime() });
		}
	}
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
