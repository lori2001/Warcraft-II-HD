#pragma once

// declare enum class for each level used
struct Levels {
	enum class LEVEL_TYPES {
		MENU,
		SETTINGS,
		LOBBY,
		GAME,
		EDITOR
	};

	// holds the current active level
	static LEVEL_TYPES currentLevel;

	// returns the level which was last active
	static LEVEL_TYPES changeComesFrom() {
		return prevLevel_;
	}

	// check for changes (once per loop only)
	static void checkForChanges() {
		if (changeChecker_ != currentLevel)
		{
			prevLevel_ = changeChecker_;
			changeChecker_ = currentLevel;
			hasChanged_ = true;
		}
		else {
			hasChanged_ = false;
		}
	}

	// return true if level-change-event should be triggered
	static bool hasChanged() {
		return hasChanged_;
	}

private:
	inline static bool hasChanged_ = false;
	inline static LEVEL_TYPES changeChecker_; // checks for change
	inline static LEVEL_TYPES prevLevel_; // ALWAYS holds previous level
};