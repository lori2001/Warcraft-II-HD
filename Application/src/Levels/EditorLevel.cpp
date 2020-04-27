#include "EditorLevel.h"
#include "nfd.h"

EditorLevel::EditorLevel()
{
	// change window background to a milder color
	ng::Main::windowClearColor = { 50, 50, 50 };

	// reset cursor to OS-Default
	ng::Cursor::showDefault();

	MapFile::scanDir();
}

void EditorLevel::handleEvents(const sf::Event& event)
{
	if (editorState_ != STATE::EMPTY)
		activeEditor_->handleEvents(event);
	
	editorMenu_.handleEvents(event);

	// if an editor has been opened/closed
	if(editorEvent != EditorLevel::EVENT::NONE)
	{
		delete activeEditor_;

		if (editorEvent == EditorLevel::EVENT::LOAD)
		{
			// creates a file dialog so user can find file to edit
			nfdchar_t* outPath = NULL;
			nfdresult_t result = NFD_OpenDialog(MapFile::MAP_FILE_EXTENSION, MapFile::getFolderPath(), &outPath);

			if (result == NFD_OKAY)
			{
				editorState_ = STATE::MAP_EDITOR;
				activeEditor_ = new MapEditor{ outPath }; // load file (handles possible errors internally)
			}
			else if (result == NFD_ERROR) {
				auto error = NFD_GetError();
				NG_LOG_ERROR("Error: ", error); // notfiy
				throw(error); // exit with error
			}
			else {
				// if closed go back to "no editor" state
				editorState_ = STATE::EMPTY;
				activeEditor_ = nullptr;
			}
		}
		else
		{
			std::string error = "Editor type opened but not specified!";
			NG_LOG_ERROR(error);
			throw(error);
		}
	}
}

void EditorLevel::update()
{
	if (editorState_ != STATE::EMPTY)
		activeEditor_->update();

	editorMenu_.update();
}

void EditorLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	editorMenu_.drawBackground(target);

	if (editorState_ != STATE::EMPTY)
		target.draw(*activeEditor_);

	target.draw(editorMenu_);
}