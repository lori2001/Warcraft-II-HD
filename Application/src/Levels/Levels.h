#pragma once

// declare enum class for each level used
struct Levels {
	enum class EVENT {
		EVENT_NONE = 0,
		EVENT_MENU,
		EVENT_SETTINGS,
		EVENT_LOBBY,
		EVENT_GAME,
		EVENT_EDITOR
	};

	static EVENT event;
};