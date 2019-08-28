#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>


#include "Console.h"
namespace ngin
{
	class Resources
	{
	public:
		// acquires resources either by loading from file or by linking to existing pointer
		static std::shared_ptr<sf::Texture> AcquireTexture(const std::string& name);
		static std::shared_ptr<sf::Font> AcquireFont(const std::string& name);
		static std::shared_ptr<sf::SoundBuffer> AcquireSoundBuffer(const std::string& name);

		static void destroyUnusedTextures();
		static void destroyUnusedFonts();
		static void destroyUnusedSoundBuffers();

		// destorys all resources that only point nowhere
		static void destroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location = loc; }

	private:
		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;
		static std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts_;
		static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers_;
		static std::string location;
	};
}
