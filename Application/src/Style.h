#pragma once

// defines locations of texture files
// and other essential style-related properties

// WARNING resources location is "/assets" so that should be applied

namespace color {
#define COLOR_BYTE static constexpr const unsigned
	
	// yellow
	COLOR_BYTE FONT_COLOR_R = 255;
	COLOR_BYTE FONT_COLOR_G = 255;
	COLOR_BYTE FONT_COLOR_B = 0;

	// yellow
	COLOR_BYTE SELECT_COLOR_R = 255;
	COLOR_BYTE SELECT_COLOR_G = 255;
	COLOR_BYTE SELECT_COLOR_B = 0;

	// yellow (transparent)
	COLOR_BYTE HIGHLIGHT_COLOR_R = 255;
	COLOR_BYTE HIGHLIGHT_COLOR_G = 255;
	COLOR_BYTE HIGHLIGHT_COLOR_B = 0;
	COLOR_BYTE HIGHLIGHT_COLOR_A = 100;

#undef COLOR_BYTE
}

namespace size {
#define FONT_SIZE static constexpr const unsigned 

	FONT_SIZE SMALL_FONT_SIZE = 33;
	FONT_SIZE MEDIUM_FONT_SIZE = 40;

#undef FONT_SIZE

#define FLOAT static constexpr const float

	FLOAT BUTTON_WIDTH = 430.0F;
	FLOAT BUTTON_HEIGHT = 50.0F;

	FLOAT SLIDER_SHAPE_WIDTH = 335.0F;
	FLOAT SLIDER_SHAPE_HEIGHT = 31.0F;
	FLOAT SLIDER_ARROW_WIDTH = 36.0F;
	FLOAT SLIDER_ARROW_HEIGHT = 45.0F;
	FLOAT SLIDER_MARK_WIDTH = 33.0F;
	FLOAT SLIDER_MARK_HEIGHT = 27.0F;

	FLOAT CONFIRM_DIALOG_WIDTH = 700.0F;
	FLOAT CONFIRM_DIALOG_HEIGHT = 220.0F;

	FLOAT DROPDOWN_WIDTH = 277.0F;
	FLOAT DROPDOWN_HEIGHT = 40.0F;

	FLOAT SMALL_DROPDOWN_WIDTH = 69.0F;
	FLOAT SMALL_DROPDOWN_HEIGHT = 54.0F;

	FLOAT INPUT_TEXT_WIDTH = 365.0F;
	FLOAT INPUT_TEXT_HEIGHT = 50.0F;
	
	FLOAT MAP_SELECTOR_BUTTON_WIDTH = 39.0F;
	FLOAT MAP_SELECTOR_BUTTON_HEIGHT = 297.0F;
	FLOAT MAP_SELECTOR_CONTAINER_WIDTH = 340.0F;
	FLOAT MAP_SELECTOR_CONTAINER_HEIGHT = 297.0F;
#undef FLOAT
}

namespace location {
#define LOCATION static constexpr const char*

	LOCATION ASSETS = "assets/";

	// icon location
	LOCATION ICON = "icon.png";

	// UI sprite locations
	LOCATION LOADING_SCREEN = "images/ui/loadingscreen.jpg";
	LOCATION ORC_CURSOR = "images/ui/orc_cursor.png";
	LOCATION HUMAN_CURSOR = "images/ui/human_cursor.png";
	LOCATION BUTTON = "images/ui/button.png";
	LOCATION DROPDOWN = "images/ui/dropdown.png";
	LOCATION SLIDER = "images/ui/slider.png";
	LOCATION CONFIRM_DIALOG = "images/ui/confirm_dialog.png";
	LOCATION BOT_GEARS = "images/ui/bot_gears/";
	LOCATION TOP_GEARS = "images/ui/top_gears/";
	LOCATION MENU_BG = "images/ui/menu_bg.jpg";
	LOCATION SETTINGS_BG = "images/ui/settings_bg.jpg";
	LOCATION MAP_SELECTOR = "images/ui/map_selector.png";
	LOCATION LOBBY_BG = "images/ui/lobby_bg.jpg";
	LOCATION BLOCK_SWTICH = "images/ui/block_switch.png";
	LOCATION CIRCLE_SWTICH = "images/ui/circle_switch.png";
	LOCATION INPUT_TEXT = "images/ui/input_text.png";
	LOCATION SMALL_DROPDOWN = "images/ui/small_dropdown.png";
	LOCATION LEAVE_BUTTON = "images/ui/leave_button.png";
	LOCATION GRID_SWITCHER = "images/ui/grid_switcher.png";
	LOCATION EDITOR_HEADER = "images/ui/header.png";
	LOCATION RECENTER_BUTTON = "images/ui/recenter_button.png";
	LOCATION SCROLLBOX = "images/ui/scrollbox.png";
	LOCATION PAINT_SWITCHER = "images/ui/paint_switcher.png";

	// sound locations
	LOCATION CLICK_SOUND = "audio/click.wav";

	// fonts
	// warcraft font
	LOCATION PRIMARY_FONT = "fonts/warcraft.ttf";
	LOCATION SECONDARY_FONT = "fonts/normal.ttf";
	
#undef LOCATION
}
