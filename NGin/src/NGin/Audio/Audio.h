#pragma once
#include "SFML/Audio.hpp"

namespace ngin {
	class Audio {
	public:
		static void subscribeSound(sf::Sound* sound);
		static void unsubscribeSound(sf::Sound* sound);
		static void subscribeMusic(sf::Music* music);
		static void unsubscribeMusic(sf::Music* music);

		static void setSoundVolume(float soundVolume) { soundVolume_ = soundVolume; }
		static void setMusicVolume(float musicVolume) { musicVolume_ = musicVolume; }

		static void updateSubscriptionsState();
		static float getSoundVolume() { return soundVolume_; }
		static float getMusicVolume() { return musicVolume_; }
	private:

		static std::vector<sf::Sound*> sounds_;
		static std::vector<sf::Music*> musics_;

		static float musicVolume_;
		static float soundVolume_;
	};
}