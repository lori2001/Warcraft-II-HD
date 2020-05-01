#pragma once
#include "NGin.h"
#include "Levels.h"

#include "Style.h"
#include "SettingsFile.h"

class SettingsLevel : private SettingsFile, public ng::Level {
public:
	SettingsLevel();

	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void applySettingsToWindow();

private:
	void addResolutionsTo(ng::Dropdown& dropdown);

	// Textures and fonts
	const ng::FontPtr primaryFont_ = NG_FONT_SPTR(location::PRIMARY_FONT);
	
	// --- Navigation buttons -------
	ng::Button backButton_
	{ 
		primaryFont_, // font
		"Back", // string
		size::MEDIUM_FONT_SIZE, // character size
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B }, // font color
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT },
		NG_TEXTURE_SPTR(location::BUTTON),
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B }, // select color
		{ 105, 965 } // position
	};
	ng::Button applyButton_
	{ 
		"Apply",
		backButton_, // inherit style from backButton_
		{ 735, 965 } // position
	};

	// --- Sound Slider -------
	const float soundTextOffset_ = -47.0F;
	sf::Text soundText_
	{
		"Sound Volume:",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};
	ng::Slider soundSlider_{
		{ 425, 450 }, // position
		NG_TEXTURE_SPTR(location::SLIDER),
		{size::SLIDER_SHAPE_WIDTH, size::SLIDER_SHAPE_HEIGHT},
		{size::SLIDER_ARROW_WIDTH, size::SLIDER_ARROW_HEIGHT},
		{size::SLIDER_MARK_WIDTH, size::SLIDER_MARK_HEIGHT},
		{color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B},
		ng::ftovec(1.2F) // scale
	};

	// --- Music Slider -------
	const float musicTextOffset_ = -47;
	sf::Text musicText_
	{
		"Music Volume:",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};
	ng::Slider musicSlider_{ { 425, 600 }, soundSlider_ };

	// -- Window Type Dropdown ----------------
	ng::Dropdown windowTypeDropdown_{
		primaryFont_,
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B },
		size::MEDIUM_FONT_SIZE,
		{ color::HIGHLIGHT_COLOR_R, color::HIGHLIGHT_COLOR_G,
		  color::HIGHLIGHT_COLOR_B, color::HIGHLIGHT_COLOR_A},
		{ color::SELECT_COLOR_R, color::SELECT_COLOR_G, color::SELECT_COLOR_B },
		{ size::DROPDOWN_WIDTH, size::DROPDOWN_HEIGHT },
		NG_TEXTURE_SPTR(location::DROPDOWN),
		{ 1000, 600 }
	};
	const float windowTypeTextOffset_ = -45;
	sf::Text windowTypeText_
	{
		"Window Mode:",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};
	std::vector<std::string> windowTypeStrings_{
		"Windowed",
		"Borderless",
		"Fullscreen"
	};
	
	// -- Window Video Mode Dropdown ------------ 
	ng::Dropdown videoModeDropdown_{
		windowTypeDropdown_,
		{ 1300, 450 },
	}; // inherit style
	const float videoModeTextOffset_ = -45;
	sf::Text videoModeText_
	{
		"Resolution:",
		*primaryFont_,
		size::MEDIUM_FONT_SIZE
	};
	std::vector<sf::VideoMode> videoModes_; // constructed in addResolutionsTo()

	// --- Animated Gears and Background -------
	std::vector<ng::TexturePtr> botGearsTextures_;
	const sf::Vector2f botGearsPosition_{ 1300, 500 };
	std::vector<ng::TexturePtr> topGearsTextures_;
	const sf::Vector2f topGearsPosition_{ 100, 60 };
	const ng::TexturePtr backgroundTexture_ = NG_TEXTURE_SPTR(location::SETTINGS_BG);

	sf::Sprite botGears_;
	sf::Sprite topGears_;
	sf::Sprite background_{ *backgroundTexture_ };

	ng::AnimationFile botGearsAnimation_{ 0.1F };
	ng::AnimationFile topGearsAnimation_{ 0.1F };
	
	// --- Confirm Dialog -----------------
	const std::string resetDialogText_ = "Are you sure you want to keep these changes?";

	ng::ConfirmDialog resetDialog_ {
		ng::ConfirmDialog::DIALOG_TYPE::DIALOG_YES_OR_CLOSE,
		resetDialogText_,
		{ size::CONFIRM_DIALOG_WIDTH, size::CONFIRM_DIALOG_HEIGHT },
		NG_TEXTURE_SPTR(location::CONFIRM_DIALOG), // texture 1
		NG_TEXTURE_SPTR(location::BUTTON), // texture 2
		{ size::BUTTON_WIDTH, size::BUTTON_HEIGHT }, // sizes
		NG_FONT_SPTR(location::PRIMARY_FONT), // font
		{ MAIN_VIEW_XCENTER - size::CONFIRM_DIALOG_WIDTH / 2, // position
		MAIN_VIEW_YCENTER - size::CONFIRM_DIALOG_HEIGHT / 2 },
		{ color::FONT_COLOR_R, color::FONT_COLOR_G, color::FONT_COLOR_B }, // font color
		{ color::SELECT_COLOR_R,  color::SELECT_COLOR_G,  color::SELECT_COLOR_B } // select color
	};
	float resetTimer_ = 0.0F;
    const float resetLimit_ = 10.0F;

	enum class CHANGE {
		CHANGE_NONE,
		CHANGE_TEMPORARY,
		CHANGE_PERMANENT,
		CHANGE_REVERT
	} changeType_;

	// -- non-permanent settings containers --------
	sf::VideoMode saveVideoMode_;
	std::string saveWindowTypeString_;
};