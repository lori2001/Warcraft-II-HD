#include "Music.h"

sf::Music Music::nowPlaying_;
Music::Theme Music::iPlaying_ = Theme::NONE;
std::vector<std::string> Music::locations_ = {
	"assets/audio/theme/menu.wav",
	"assets/audio/theme/humans/defeat.wav",
	"assets/audio/theme/humans/score_room.wav",
	"assets/audio/theme/humans/theme1.wav",
	"assets/audio/theme/humans/victory.wav",
	"assets/audio/theme/orcs/defeat.wav",
	"assets/audio/theme/orcs/score_room.wav",
	"assets/audio/theme/orcs/theme1.wav",
	"assets/audio/theme/orcs/victory.wav" };

void Music::playTheme(const Theme theme)
{
	if (theme != iPlaying_) {
		nowPlaying_.openFromFile(locations_[theme]);
		iPlaying_ = theme;
	}

	if (nowPlaying_.getStatus() != sf::Music::Status::Playing) {
		nowPlaying_.play();
	}
}
