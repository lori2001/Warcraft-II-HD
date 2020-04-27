#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <unordered_map>

namespace ng
{
	typedef std::shared_ptr<sf::Texture> TexturePtr;
	typedef std::shared_ptr<sf::Font> FontPtr;
	typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;

	class Resources
	{
	public:
		// acquires resources either by loading from file or by linking to existing pointer
		static ng::TexturePtr AcquireTexture(const std::string& name);
		static ng::FontPtr AcquireFont(const std::string& name);
		static ng::SoundBufferPtr AcquireSoundBuffer(const std::string& name);

		static void destroyUnusedTextures();
		static void destroyUnusedFonts();
		static void destroyUnusedSoundBuffers();

		// destorys all resources that only point nowhere
		static void destroyUnused();

		// changes default load-in location
		static void setLocation(const std::string& loc) { location_ = loc; }
		static std::string getLocation() { return location_; }

	private:
		static std::unordered_map<std::string, ng::TexturePtr> textures_;
		static std::unordered_map<std::string, ng::FontPtr> fonts_;
		static std::unordered_map<std::string, ng::SoundBufferPtr> soundBuffers_;
		static std::string location_;
	};

#define NG_TEXTURE_SPTR(location) ng::Resources::AcquireTexture(location)
#define NG_FONT_SPTR(location) ng::Resources::AcquireFont(location)
#define NG_SOUNDBUFFER_SPTR(location) ng::Resources::AcquireSoundBuffer(location)
}
