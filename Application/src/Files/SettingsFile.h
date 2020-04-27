#pragma once
#include "NGin.h"

static constexpr const char* WINDOW_NAME = "Warcraft II HD";

static constexpr const float MAIN_VIEW_WIDTH = 1920.0F;
static constexpr const float MAIN_VIEW_HEIGHT = 1080.0F;
static constexpr const float MAIN_VIEW_XCENTER = MAIN_VIEW_WIDTH / 2;
static constexpr const float MAIN_VIEW_YCENTER = MAIN_VIEW_HEIGHT / 2;

class SettingsFile {
public:
	static void load();
	static void save();

	static float getMusicVolume() { return json_[musicVolumeKey].get<float>(); }
	static float getSoundVolume() { return json_[soundVolumeKey].get<float>(); }
	static ng::WINDOW_TYPE getWindowType() {
		return static_cast<ng::WINDOW_TYPE>(json_[windowTypeKey].get<int>());
	}
	static sf::VideoMode getVideoMode() {
		return sf::VideoMode{
			json_[videoModeKey][widthKey].get<unsigned>(),
			json_[videoModeKey][heightKey].get<unsigned>(),
			json_[videoModeKey][bitsPerPixelKey].get<unsigned>()
		};
	}

protected:
	static void setMusicVolume(const float musicVolume) { json_[musicVolumeKey] = musicVolume; }
	static void setSoundVolume(const float soundVolume) { json_[soundVolumeKey] = soundVolume; }
	static void setWindowType(const ng::WINDOW_TYPE& windowType) {
		json_[windowTypeKey] = static_cast<int>(windowType);
	}
	static void setVideoMode(const sf::VideoMode& videoMode) {
		json_[videoModeKey][widthKey] = videoMode.width;
		json_[videoModeKey][heightKey] = videoMode.height;
		json_[videoModeKey][bitsPerPixelKey] = videoMode.bitsPerPixel;
	}
private:
	static void create(); // gets called if loading fails

	static ng::json json_;

	static constexpr const char* fileName = "settings.json";

#define KEY static constexpr const char*
	KEY	videoModeKey = "videoMode";
	KEY	widthKey = "width";
	KEY	heightKey = "height";
	KEY bitsPerPixelKey = "bitsPerPixel";
	KEY	windowTypeKey = "windowType";
	KEY soundVolumeKey = "soundVolume";
	KEY musicVolumeKey = "musicVolume";
#undef KEY
};