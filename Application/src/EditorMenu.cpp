#include "EditorMenu.h"
#include "EditorLevel.h"

EditorMenu::EditorMenu()
{
	// --- File Dropdown ------
	fileDropdown_.setDropString(0, "File");
	fileDropdown_.addDropString("New");
	fileDropdown_.addDropString("Load");
	fileDropdown_.addDropString("Save");
	fileDropdown_.setStatic(true);

	// --- Back Button ---------
	backButton_.setSelectColor({ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B });
	backButton_.setScale(ng::ftovec(0.8F));
	backButton_.setPosition({ 50.0F, 10.0F });
}

void EditorMenu::handleEvents(const sf::Event& event)
{
	backButton_.handleEvents(event, ng::Cursor::getPosition());
	fileDropdown_.handleEvents(event, ng::Cursor::getPosition());

	// --- Editor Navigation -----
	EditorLevel::editorEvent = EditorLevel::EVENT::NONE;

	if (fileDropdown_.getActiveDrop() == 2) {
		EditorLevel::editorEvent = EditorLevel::EVENT::LOAD;
		fileDropdown_.setActiveDrop(0); // since dropdown static -> has to be reset manually
	}
	// --- Editor Navigation -----

	// --- Level Navigation ----------------
	if (backButton_.isActive()) {
		Levels::currentLevel = Levels::LEVEL_TYPES::MENU;
	}
	// -------------------------------
}

void EditorMenu::update()
{
}

void EditorMenu::drawBackground(sf::RenderTarget& target) const
{
	ng::Main::applyDefaultViewToWindow();
	target.draw(header_);
}

void EditorMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ng::Main::applyDefaultViewToWindow();
	target.draw(backButton_);
	target.draw(fileDropdown_);
}
