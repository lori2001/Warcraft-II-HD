#pragma once
#include "NGin.h"
#include "../Style.h"

#include "../Files/MapFile.h"
#include "../Files/SettingsFile.h"
#include "Levels.h"

#include "Editor/EditorMenu.h"
#include "Editor/MapEditor.h"

class EditorLevel : public ng::Level {
public:
	EditorLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// event that triggers change of STATE
	enum class EVENT {
		NONE = 0, // there is no event
		LOAD
	};
	inline static EVENT editorEvent = EVENT::NONE;

	~EditorLevel();
private:
	// current state of editor
	enum class STATE {
		EMPTY,
		MAP_EDITOR
	};
	STATE editorState_ = STATE::EMPTY;

	EditorMenu editorMenu_;
	
	// editors behave just like levels even though technically they are not levels
	ng::Level* activeEditor_ = nullptr;
};