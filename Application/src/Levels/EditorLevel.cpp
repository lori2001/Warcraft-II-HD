#include "EditorLevel.h"
#include "NGin/Levels/MainLevel.h"

void EditorLevel::setup()
{
	// -- Textures -----------------------------------------------------
	headerTexture_ = ngin::Resources::AcquireTexture("images/ui/header.png");
	dropdownTexture_ = ngin::Resources::AcquireTexture("images/ui/dropdown.png");
	leaveButtonTexture_ = ngin::Resources::AcquireTexture("images/ui/leave_button.png");
	gridSwitcherTexture_ = ngin::Resources::AcquireTexture("images/ui/grid_switcher.png");
	painterSwitcherTexture_ = ngin::Resources::AcquireTexture("images/ui/paint_switcher.png");
	font_ = ngin::Resources::AcquireFont("fonts/normal.ttf");

	// reset cursor to OS-Default
	ngin::Cursor::resetToDefault();

	tilePainterSwitcher_.setTexture(*painterSwitcherTexture_);
	gridSwitcher_.setTexture(*gridSwitcherTexture_);
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

	// --- Scales ----------------------------------
	gridSwitcher_.setScale(ngin::ftoVec(0.8F));
	backButton_.setScale(ngin::ftoVec(0.8F));
	tilePainterSwitcher_.setScale(ngin::ftoVec(0.8F));
	// ---------------------------------------------

	// --- Positions -------------------------------
	gridSwitcher_.setPosition({ 1795, 10 });
	tilePainterSwitcher_.setPosition({ 1700, 10 });
	backButton_.setPosition({ 50, 10 });
	fileDropdown_.setPosition({ 160 , 20 });
	// ---------------------------------------------

	// (re)set important bools
	mapEditor_ = false;
	gridSwitcher_.setIsActive(true);
	tilePainterSwitcher_.setIsActive(false);

	GameDetails::mapFile.scanDir();

	// change window background to a milder color
	ngin::MainLevel::windowClearColor_ = { 50, 50, 50 };
}

void EditorLevel::handleEvents(const sf::Event& event)
{
	// --- General events -----------------------------
	backButton_.handleEvents(event, ngin::Cursor::getPosition());
	fileDropdown_.handleEvents(event, ngin::Cursor::getPosition());

	if (backButton_.isActive()) {
		ngin::MainLevel::windowClearColor_ = { 0, 0, 0 };
		response_ = RESPONSE::MAIN_MENU;
	}
	else {
		response_ = RESPONSE::NONE;
	}
	// ------------------------------------------------

	// --- Toolbar Focus ------------------------------
	if (headerSprite_.getGlobalBounds().contains(ngin::Cursor::getPosition())) {
		toolbarHasFocus_ = true;
	}
	else {
		toolbarHasFocus_ = false;
	}
	// ------------------------------------------------

	// --- Loading events -----------------------------
	if (fileDropdown_.getActiveDrop() == 2)
	{
		// select and load file, if successful return true
		if (editableMap_.setMapFile(GameDetails::mapFile))
		{
			mapEditor_ = true;

			// make grid active by default
			editableMap_.setGridIsActive(true);

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

			tilePainter_.setup();

			// default position
			tilePainter_.setPosition({ 1520, 80 });
		}
		fileDropdown_.setActiveDrop(0);
	}
	// ------------------------------------------------

	// --- Map editor events --------------------------
	if (mapEditor_) {
		// painting events
		editableMap_.handleEvents(event, tilePainter_);
		
		// map editor zoom
		if (event.type == sf::Event::MouseWheelMoved && editableMap_.isFocused())
		{
			editorZoom_ += event.mouseWheel.delta * editorZoomSpeed_;

			if (editorZoom_ > editorMaxZoom_) {
				editorZoom_ = editorMaxZoom_;
			}
			else if (editorZoom_ < editorMinZoom_) {
				editorZoom_ = editorMinZoom_;
			}

			sf::Vector2f scaleBefore = editableMap_.getScale();
			editableMap_.setScale(ngin::ftoVec(editorZoom_));
		}
		// grid enable/disable logic
		gridSwitcher_.handleEvents(event, ngin::Cursor::getPosition());
		if (gridSwitcher_.isActive()) {
			editableMap_.setGridIsActive(true);
		}
		else {
			editableMap_.setGridIsActive(false);
		}

		// map painter enable/disable logic
		tilePainterSwitcher_.handleEvents(event, ngin::Cursor::getPosition());
		if (tilePainterSwitcher_.isActive()) {
			tilePainter_.handleEvents(event, ngin::Cursor::getPosition());
			// editable map focus
			editableMap_.checkIfFocused(toolbarHasFocus_, tilePainter_.isFocused());
		}
		else {
			editableMap_.checkIfFocused(toolbarHasFocus_);
			tilePainter_.resetUsingTile();
		}
	}
	// ------------------------------------------------
}

void EditorLevel::update()
{
	if (mapEditor_)
	{
		if (ngin::MainLevel::windowHasFocus())
		{
			// "viewport" movement
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

			editableMap_.updateGrid();
		}
	}
}

void EditorLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mapEditor_) {
		target.draw(editableMap_);
	}

	target.draw(headerSprite_);
	target.draw(fileDropdown_);
	target.draw(backButton_);

	if (mapEditor_) {
		target.draw(gridSwitcher_);
		target.draw(tilePainterSwitcher_);
		if (tilePainterSwitcher_.isActive())
		{
			target.draw(tilePainter_);
		}
	}
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

	gridSwitcher_.setSelectColor(themeColor);
	tilePainterSwitcher_.setSelectColor(themeColor);

	tilePainter_.setupUIStyle(font, fontSize, themeColor);
}
