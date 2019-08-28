#pragma once
#include "NGin.h"

class SettingsFile {
public:
	void load();
	void save();

	static void setPlayerName(const std::string& playerName) { playerName_ = playerName; }
	static std::string getPlayerName() { return playerName_; }

	void setMusicVolume(const float musicVolume) { json_["Music_Volume"] = musicVolume; }
	void setSoundVolume(const float soundVolume) { json_["Sound_Volume"] = soundVolume; }
	void setWindowType(const ngin::MainLevel::WINDOW_TYPE& windowType) {
		json_["Window_Type"] = static_cast<int>(windowType);
	}
	void setVideoMode(const sf::VideoMode& videoMode) {
		json_["Video_Mode"]["Width"] = videoMode.width;
		json_["Video_Mode"]["Height"] = videoMode.height;
		json_["Video_Mode"]["BitsPerPixel"] = videoMode.bitsPerPixel;
	}

	float getMusicVolume() const { return json_["Music_Volume"].get<float>(); }
	float getSoundVolume() const { return json_["Sound_Volume"].get<float>(); }
	ngin::MainLevel::WINDOW_TYPE getWindowType() const {
		return static_cast<ngin::MainLevel::WINDOW_TYPE>(json_["Window_Type"].get<int>());
	}
	sf::VideoMode getVideoMode() const {
		return sf::VideoMode{
			json_["Video_Mode"]["Width"].get<unsigned>(),
			json_["Video_Mode"]["Height"].get<unsigned>(),
			json_["Video_Mode"]["BitsPerPixel"].get<unsigned>()
		};
	}

private:
	ngin::Json json_;

	static std::string playerName_; // non-ngin property

	void create(); // gets called if loading fails
};