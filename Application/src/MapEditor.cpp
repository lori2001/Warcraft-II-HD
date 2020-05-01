#include "MapEditor.h"

MapEditor::MapEditor(const std::string& filePath)
{
	MapFile::load(filePath);
	Map::setup({ 0, 0 }, Map::MAP_TYPE::EDITABLE);

	// sets the part of window the editor renders on
	editorView_.setViewport(sf::FloatRect(0.0F, EditorMenu::menuHeightPer, 1.0F, 1.0F));
	
	centerEditorOnMap();

	// activate grid by default
	gridSwitcher_.setIsActive(true);
	updateGrid();

	selectionRectTexture_ = NG_TEXTURE_SPTR(MapFile::getThemeLocation());
	selectionRect_.setTexture(&*selectionRectTexture_);
	selectionRect_.setSize(Map::getScaledTileSize());
	selectionRect_.setFillColor({255,255,255, selectionRectAlpha_ });
	selectionRect_.setTextureRect({ 0 , 0, 
		static_cast<int>(MapFile::getTileSize().x),
		static_cast<int>(MapFile::getTileSize().y) });
}

void MapEditor::handleEvents(const sf::Event& event)
{
	gridSwitcher_.handleEvents(event, ng::Cursor::getPosition());
	recenterButton_.handleEvents(event, ng::Cursor::getPosition());
	tilePainterSwitcher_.handleEvents(event, ng::Cursor::getPosition());

	if (recenterButton_.isActive()) {
		centerEditorOnMap();
		editorView_.zoom(1 / editorCurrentZoomFactor_); // reset zoom to 1/1
		editorCurrentZoomFactor_ = 1.0F;
		updateGrid();
	}

	if (gridSwitcher_.hasChanged() && gridSwitcher_.isActive()) {
		updateGrid(); //update grid when first acitvated
	}

	bool zoomIn = zoomInEvent(event);
	bool zoomOut = zoomOutEvent(event);
	if ((zoomIn || zoomOut) && // if zoom is triggered and either
		(currentPainter_ == nullptr || // no editor
		(currentPainter_ != nullptr && !currentPainter_->isFocused()))) // editor is not focused by mouse
	{
		float actualZoomFactor = editorZoomFactor_;

		if (zoomOut) // invert in case of zoom out
			actualZoomFactor = 1 / actualZoomFactor;

		editorCurrentZoomFactor_ *= actualZoomFactor; // keep in mind the current level of zooming
		editorView_.zoom(actualZoomFactor); // actually zoom the view
		
		selectionRect_.setSize(Map::getScaledTileSize()); // scale of selection rect has changed
		updateGrid(); // scale of grid has changed
	}

	// updates position of selection rectangle based cursor position
	updateSelectionPos();

	if (tilePainterSwitcher_.hasChanged()) {
		delete currentPainter_;
		if (tilePainterSwitcher_.isActive()) {
			currentPainter_ = new TilePainter;
		}
		else {
			currentPainter_ = nullptr;
		}
	}

	if (currentPainter_ != nullptr) {
		currentPainter_->handleEvents(event);
		if (tilePainterSwitcher_.isActive())
		{
			if (currentPainter_->isFocused())
			{
				canPlace_ = false;
				if (currentPainter_->getChoosenHasChanged())
				{
					selectionRect_.setTextureRect(currentPainter_->getChoosenTextureRect());
				}
			}
			if (canPlace_ && tilePlaceEvent(event))
			{
				placeTile(currentPainter_->getChoosen());
			}
		}
	}
}

void MapEditor::update()
{
	if (ng::Main::windowHasFocus())
	{
		// --- View movement --------------------------------------------------
		const sf::Vector2f posBefore = editorView_.getCenter();
		if (sf::Keyboard::isKeyPressed(keyNavigateLeft_)) {
			editorView_.move({ -editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
			updateGrid();
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateRight_)) {
			editorView_.move({ editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime(), 0 });
			updateGrid();
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateUp_)) {
			editorView_.move({ 0, -editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
			updateGrid();
		}
		if (sf::Keyboard::isKeyPressed(keyNavigateDown_)) {
			editorView_.move({ 0, editorMoveSpeed_ * editorCurrentZoomFactor_ * ng::Timer::getDeltaTime() });
			updateGrid();
		}
		// --------------------------------------------------------------------
	}
}

void MapEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// ------ Editor view ---------------
	ng::Main::setWindowView(editorView_);

	Map::draw(target, states);

	if(canPlace_) 
		target.draw(selectionRect_);
	
	if (gridSwitcher_.isActive())
		target.draw(gridLines_);

	// ------ Menu view -----------------
	ng::Main::applyDefaultViewToWindow();

	target.draw(gridSwitcher_);

	target.draw(recenterButton_);

	target.draw(tilePainterSwitcher_);

	if (currentPainter_ != nullptr)
		target.draw(*currentPainter_);
}

MapEditor::~MapEditor()
{
	// TODO: confirm dialog!!!!!!
	MapFile::save();
	NG_LOG_INFO("Map file has been saved !");
}

void MapEditor::updateGrid()
{
	// deletes old grid lines before recalculating them
	gridLines_.clear();

	editorViewTopLeft_ = {
		editorView_.getCenter().x - editorView_.getSize().x / 2 ,
		editorView_.getCenter().y - editorView_.getSize().y / 2
	};
	editorViewBottomRight_= {
		editorView_.getCenter().x + editorView_.getSize().x / 2 ,
		editorView_.getCenter().y + editorView_.getSize().y / 2
	};

	// scaled tile size will be the distance between two lines
	firstLineDistance_ = {
		-std::fmod(editorViewTopLeft_.x, Map::getScaledTileSize().x),
		-std::fmod(editorViewTopLeft_.y, Map::getScaledTileSize().y)
	};
	// correct for negative coordinate values
	if (firstLineDistance_.x < 0)
		firstLineDistance_.x += Map::getScaledTileSize().x;
	if (firstLineDistance_.y < 0)
		firstLineDistance_.y += Map::getScaledTileSize().y;

	for (float x = editorViewTopLeft_.x + firstLineDistance_.x; x <= editorViewBottomRight_.x; x += Map::getScaledTileSize().x) {
		sf::Vertex VerticalLine[]{
			sf::Vertex(sf::Vector2f(x, editorViewTopLeft_.y), gridColor_),
			sf::Vertex(sf::Vector2f(x, editorViewBottomRight_.y), gridColor_)
		};

		gridLines_.append(VerticalLine[0]);
		gridLines_.append(VerticalLine[1]);
	}
	for (float y = editorViewTopLeft_.y + firstLineDistance_.y; y <= editorViewBottomRight_.y; y += Map::getScaledTileSize().y) {
		sf::Vertex VerticalLine[] {
			sf::Vertex(sf::Vector2f(editorViewTopLeft_.x, y), gridColor_),
			sf::Vertex(sf::Vector2f(editorViewBottomRight_.x, y), gridColor_)
		};

		gridLines_.append(VerticalLine[0]);
		gridLines_.append(VerticalLine[1]);
	}
}

void MapEditor::updateSelectionPos()
{
	ng::Main::setWindowView(editorView_); // start working in editor view
	sf::Vector2f cursorPos = ng::Main::getWindowPtr()->mapPixelToCoords(sf::Mouse::getPosition(*ng::Main::getWindowPtr()));

	// only work with selected tile if it's withing the bounds of the view
	if (cursorPos.x >= editorViewTopLeft_.x && cursorPos.y >= editorViewTopLeft_.y &&
		cursorPos.x <= editorViewBottomRight_.x && cursorPos.y <= editorViewBottomRight_.y)
	{
		canPlace_ = true;
		
		// cursor position relative to the global position of the first whole square on grid
		sf::Vector2f relativeCursorPos = {
			cursorPos.x - editorViewTopLeft_.x,
			cursorPos.y - editorViewTopLeft_.y
		};

		sf::Vector2i tilesBehindCursor = {
			static_cast<int>((relativeCursorPos.x + Map::getScaledTileSize().x - firstLineDistance_.x) / Map::getScaledTileSize().x),
			static_cast<int>((relativeCursorPos.y + Map::getScaledTileSize().y - firstLineDistance_.y) / Map::getScaledTileSize().y)
		};

		sf::Vector2f selectedPosition = {
			editorViewTopLeft_.x + (tilesBehindCursor.x - 1) * Map::getScaledTileSize().x + firstLineDistance_.x,
			editorViewTopLeft_.y + (tilesBehindCursor.y - 1) * Map::getScaledTileSize().y + firstLineDistance_.y,
		};

		selectionRect_.setPosition(selectedPosition);
	}
	else {
		canPlace_ = false;
	}

	ng::Main::applyDefaultViewToWindow(); // IMPORTANT reset view to default
}

void MapEditor::placeTile(const int tileIndex)
{
	// TODO: Fill
	sf::Vector2i tilePos = {
		static_cast<int>(selectionRect_.getPosition().x / Map::getScaledTileSize().x),
		static_cast<int>(selectionRect_.getPosition().y / Map::getScaledTileSize().y)
	};

	Map::insertTile(tilePos.x, tilePos.y, tileIndex);
}
