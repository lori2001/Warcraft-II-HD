#pragma once
#include "NGin.h"

#include "Common/ConfirmDialog.h"

class SettingsLevel : public ngin::Level {
public:
	SettingsLevel() { setup(); }

	void setup();
	void handleEvents(const sf::Event& event);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void changeWindow(sf::VideoMode& windowVideoMode,
					  sf::String& windowName,
					  ngin::WINDOW_TYPE& windowType);

	void getFromWindow(const sf::VideoMode& windowVideoMode,
					   const sf::String& windowName,
		               const ngin::WINDOW_TYPE& windowType);

	enum RESPONSE {
		NONE = 8,
		MAIN_MENU,
		APPLY,
	};
private:
	void setupUIStyle(const sf::Font& font, const unsigned fontSize, const sf::Color& themeColor);
	void addResolutionsTo(ngin::Dropdown& dropdown);
	
	// Navigation buttons 
	ngin::Button backButton_{ "Back", {430, 50} };
	ngin::Button applyButton_{ "Apply", {430, 50} };

	// Settings UI
	ngin::Slider soundSlider_{ {335, 31}, {36, 45}, {33, 27} };
	ngin::Slider musicSlider_{ {335, 31}, {36, 45}, {33, 27} };

	ngin::Dropdown windowTypeDropdown_{ { 277, 40 } };
	ngin::Dropdown videoModeDropdown_{ { 277, 40 } };

	// Confirm Dialog
	ConfirmDialog confirmDialog_;
	
	float resetTimer_ = 0.0F;
	const float resetLimit_ = 10.0F;

	bool dialogActive_ = false;
	bool applyChanges_ = false;
	enum class CHANGE {
		TEMPORARY,
		PERMANENT,
		REVERT
	} changeType_;

	// Properties
	sf::VideoMode saveVideoMode_;
	std::string saveWindowTypeString_;

	std::vector<std::string> windowTypeStrings_ {
		"Windowed",
		"Borderless",
		"Fullscreen"
	};
	std::vector<sf::VideoMode> videoModes_; // constructed in addResolutionsTo()

	// Static stuff
	sf::Text soundText_;
	sf::Text musicText_;
	sf::Text windowModeText_;
	sf::Text resolutionText_;

	// Textures
	std::shared_ptr<sf::Font> warcraftFont_;
	std::shared_ptr<sf::Texture> buttonTexture_;
	std::shared_ptr<sf::Texture> dropdownTexture_;
	std::shared_ptr<sf::Texture> sliderTexture_;
	std::shared_ptr<sf::Texture> confirmDialogTexture_;
	std::shared_ptr<sf::Texture> backgroundTexture_;
	std::vector<std::shared_ptr<sf::Texture>> botGearsTextures_;
	std::vector<std::shared_ptr<sf::Texture>> topGearsTextures_;

	// Background
	ngin::AnimationFile botGearsAnimation_{ 0.1F };
	ngin::AnimationFile topGearsAnimation_{ 0.1F };

	sf::Sprite botGears_;
	sf::Sprite topGears_;
	sf::Sprite background_;
};