#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>

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
		static void setLocation(const std::string& loc) { location_ = loc; }
		static std::string getLocation() { return location_; }

	private:
		static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;
		static std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts_;
		static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers_;
		static std::string location_;
	};

#define NG_TEXTURE_PTR(location) ngin::Resources::AcquireTexture(location)
#define NG_FONT_PTR(location) ngin::Resources::AcquireFont(location)
#define NG_SOUNDBUFFER_PTR(location) ngin::Resources::AcquireSoundBuffer(location)

#define NG_TEXTURE(location) *ngin::Resources::AcquireTexture(location)
#define NG_FONT(location) *ngin::Resources::AcquireFont(location)
#define NG_SOUNDBUFFER(location) *ngin::Resources::AcquireSoundBuffer(location)
}
