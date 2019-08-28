#include "Audio.h"
#include "../System/Console.h"

namespace ngin {
	std::vector<sf::Sound*> Audio::sounds_;
	std::vector<sf::Music*> Audio::musics_;
	float Audio::soundVolume_ = 1.0F; // 100%
	float Audio::musicVolume_ = 1.0F; // 100%

	void Audio::subscribeSound(sf::Sound* sound)
	{
		sounds_.push_back(sound);
	}

	void Audio::unsubscribeSound(sf::Sound* sound)
	{
		auto it = std::find(sounds_.begin(), sounds_.end(), sound);

		// if found -> delete
		if (it != sounds_.end()) {
			sounds_.erase(it);
		}
		else {
			NG_LOG_WARN("Can not unsubscribe unexisting sound!");
		}
	}

	void Audio::subscribeMusic(sf::Music* music)
	{
		musics_.push_back(music);
	}

	void Audio::unsubscribeMusic(sf::Music* music)
	{
		auto it = std::find(musics_.begin(), musics_.end(), music);

		// if found -> delete
		if (it != musics_.end()) {
			musics_.erase(it);
		}
		else {
			NG_LOG_WARN("Can not unsubscribe unexisting music!");
		}
	}

	void Audio::updateSubscriptionsState()
	{
		for (auto it : sounds_)
			it->setVolume(soundVolume_ * 100);

		for (auto it : musics_)
			it->setVolume(musicVolume_ * 100);
	}
}