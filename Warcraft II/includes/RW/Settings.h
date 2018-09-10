#pragma once
#include <assert.h>
#include <fstream>
#include "SFML\Graphics.hpp"
#include "../../libs/json/json.hpp"

namespace RW
{
	class Settings
	{
	private:
		static io::json jsonfile;
		
		static sf::Vector2i res1920;

		static sf::Vector2i oldres;
		static bool oldfullscreen;

		static void create();
	public:
		static void setWindow(sf::RenderWindow & window);
		static void read();
		static void save();

		//getters
		static const bool getFullscreen() { return jsonfile["fullscreen"]; }
		static const bool getOldFullscreen() { return oldfullscreen; }
		static const sf::Vector2i getRes() { return sf::Vector2i(jsonfile["resolution"]["width"].get<int>(), jsonfile["resolution"]["height"].get<int>()); }
		static const sf::Vector2i getOldRes() { return oldres; }
		static const sf::Vector2f get1920Scale() { return sf::Vector2f(jsonfile["resolution"]["width"].get<float>() / res1920.x, jsonfile["resolution"]["height"].get<float>() / res1920.y); }
		static const unsigned short getMusic() { return jsonfile["music"].get<unsigned short>(); }
		static const unsigned short getSoundFX() { return jsonfile["soundfx"].get<unsigned short>(); }
		static const std::string getName() { return jsonfile["playerName"].get<std::string>(); }
		//holds 1/12th of the screens values
		static const sf::Vector2f unit() { return sf::Vector2f((res1920.x/12) * get1920Scale().x, (res1920.y/12) * get1920Scale().y); }

		//setters
		static void setRes(const sf::Vector2i &res_in) { jsonfile["resolution"]["width"] = res_in.x; jsonfile["resolution"]["height"] = res_in.y;}
		static void setOldRes(const sf::Vector2i &oldres_in) { oldres = oldres_in; }
		static void setFullscreen(const bool &fullscreen_in) { jsonfile["fullscreen"] = fullscreen_in; }
		static void setOldFullscreen(const bool &oldfullscreen_in) { oldfullscreen = oldfullscreen_in; }
		static void setMusic(const unsigned short &music_in) { jsonfile["music"] = music_in; }
		static void setSoundFX(const unsigned short &soundfx_in) { jsonfile["soundfx"] = soundfx_in; }
		static void setName(const std::string & name_in) { jsonfile["playerName"] = name_in; }
	};
}