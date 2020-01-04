#include "Resources.h"

namespace ngin {

	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Resources::textures_;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> Resources::fonts_;
	std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> Resources::soundBuffers_;
	std::string Resources::location_ = "";

	std::shared_ptr<sf::Texture> Resources::AcquireTexture(const std::string& name)
	{
		const auto search = textures_.find(location_ + name); // search

		// if something is found
		if (search != textures_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto texture = std::make_shared<sf::Texture>();

			texture->loadFromFile(location_ + name);
			textures_.insert({ location_ + name, texture });

			// NG_LOG_NOTE(location, name, " - Texture Loaded");
			return texture;
		}
	}

	std::shared_ptr<sf::Font> Resources::AcquireFont(const std::string& name)
	{
		const auto search = fonts_.find(location_ + name); // search

		// if something is found
		if (search != fonts_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto font = std::make_shared<sf::Font>();

			font->loadFromFile(location_ + name);
			fonts_.insert({ location_ + name, font });

			// NG_LOG_NOTE(location, name, " - Font Loaded");
			return font;
		}
	}

	std::shared_ptr<sf::SoundBuffer> Resources::AcquireSoundBuffer(const std::string& name)
	{
		const auto search = soundBuffers_.find(location_ + name); // search

		// if something is found
		if (search != soundBuffers_.end()) {
			return search->second; // returns the requested resource
		}
		else {
			// creates a new resource
			auto soundBuffer = std::make_shared<sf::SoundBuffer>();

			soundBuffer->loadFromFile(location_ + name);
			soundBuffers_.insert({ location_ + name, soundBuffer });

			// NG_LOG_NOTE(location, name, " - SoundBuffer Loaded");
			return soundBuffer;
		}
	}

	void Resources::destroyUnusedTextures()
	{
		for (auto it = textures_.begin(); it != textures_.end(); )
		{
			if (it->second.use_count() == 1) {
				// NG_LOG_NOTE((*it).first, " - Texture Destroyed");
				it = textures_.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void Resources::destroyUnusedFonts()
	{
		for (auto it = fonts_.begin(); it != fonts_.end(); )
		{
			if (it->second.use_count() == 1) {
				// NG_LOG_NOTE((*it).first, " - Font Destroyed");
				it = fonts_.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void Resources::destroyUnusedSoundBuffers()
	{
		for (auto it = soundBuffers_.begin(); it != soundBuffers_.end(); )
		{
			if (it->second.use_count() == 1) {
				// NG_LOG_NOTE((*it).first, " - SoundBuffer Destroyed");
				it = soundBuffers_.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void Resources::destroyUnused()
	{
		destroyUnusedTextures();
		destroyUnusedFonts();
		destroyUnusedSoundBuffers();
	}

}