#pragma once
#include "SFML/System.hpp"
#include "Timer.h"
#include <vector>
#include <windows.h> // <- only windows capable
#include <sstream>

namespace ngin
{
	class Console {
	public:
		enum FLAG {
			FLAG_NOTE = 0,
			FLAG_INFO,
			FLAG_WARNING,
			FLAG_ERROR,
			// error must be always last and orders should match
			FLAG_ONCE_NOTE,
			FLAG_ONCE_INFO,
			FLAG_ONCE_WARNING,
			FLAG_ONCE_ERROR,
		};

		// --- Logging functions START ---------------------------------------
		// prints out the given message with given flag
		static void log(const std::string& output, const FLAG& flag = FLAG::FLAG_NOTE);
		template <typename T>
		static void log(const FLAG& flag, T t);
		template<typename T, typename... Args>
		static void log(const FLAG& flag, T t, Args... args);

		// SFML vectors
		template <> static void log<sf::Vector2f>(const FLAG& flag, sf::Vector2f t) {
			log(flag, "x = ", t.x, " y = ", t.y);
		}
		template <> static void log<sf::Vector2i>(const FLAG& flag, sf::Vector2i t) {
			log(flag, "x = ", t.x, " y = ", t.y);
		}
		template <> static void log<sf::Vector2u>(const FLAG& flag, sf::Vector2u t) {
			log(flag, "x = ", t.x, " y = ", t.y);
		}
		template <> static void log<sf::Vector3f>(const FLAG& flag, sf::Vector3f t) {
			log(flag, "x = ", t.x, " y = ", t.y, " z =", t.z);
		}
		template <> static void log<sf::Vector3i>(const FLAG& flag, sf::Vector3i t) {
			log(flag, "x = ", t.x, " y = ", t.y, " z =", t.z);
		}
		// --- Logging functions END ----------------------------------------


		static void setSize(const sf::Vector2u &size);
		// !!! Changes all fonts (even those alredy printed)
		static void setFontStyle(const sf::Vector2i& size, const bool isBold = false);
		static void setName(const LPCSTR name);

	private:
		static HANDLE HConsole_;
		static int defaultColors_; // default background and foreground colors(black/white)

		static std::hash<std::string> strHash_; // generate hashes
		static std::vector<size_t> strHashes_; // store hashes

		// string stream that temporarly stores input for write
		static std::ostringstream outStringStream_;
		
		// gets the current colors of the console
		static WORD GetConsoleTextAttribute(HANDLE hCon) {
			CONSOLE_SCREEN_BUFFER_INFO con_info;
			GetConsoleScreenBufferInfo(hCon, &con_info);
			return con_info.wAttributes;
		}
	};

	template<typename T>
	inline void Console::log(const FLAG& flag, T t)
	{
		outStringStream_ << t;
		log(outStringStream_.str(), flag);
		outStringStream_.str(""); // clear stream
	}
	template<typename T, typename ...Args>
	inline void Console::log(const FLAG& flag, T t, Args ...args)
	{
		const std::size_t n = sizeof...(Args);

		if (n > 0) // grow stream until last value
			outStringStream_ << t;

		log(flag, args...);
	}
}

#ifndef NG_CONSOLE_NOPRINT
#define NG_LOG_NOTE(...) ngin::Console::log(ngin::Console::FLAG_NOTE, __VA_ARGS__ )
#define NG_LOG_INFO(...) ngin::Console::log(ngin::Console::FLAG_INFO, __VA_ARGS__ )
#define NG_LOG_WARN(...) ngin::Console::log(ngin::Console::FLAG_WARNING, __VA_ARGS__ )
#define NG_LOG_ERROR(...) ngin::Console::log(ngin::Console::FLAG_ERROR, __VA_ARGS__ )

#define NG_LOG_ONCE_NOTE(...) ngin::Console::log(ngin::Console::FLAG_ONCE_NOTE, __VA_ARGS__ )
#define NG_LOG_ONCE_INFO(...) ngin::Console::log(ngin::Console::FLAG_ONCE_INFO, __VA_ARGS__ )
#define NG_LOG_ONCE_WARN(...) ngin::Console::log(ngin::Console::FLAG_ONCE_WARNING, __VA_ARGS__ )
#define NG_LOG_ONCE_ERROR(...) ngin::Console::log(ngin::Console::FLAG_ONCE_ERROR, __VA_ARGS__ )
#else
#define NG_LOG_NOTE
#define NG_LOG_INFO
#define NG_LOG_WARN
#define NG_LOG_ERROR

#define NG_LOG_ONCE_NOTE(...)
#define NG_LOG_ONCE_INFO(...)
#define NG_LOG_ONCE_WARN(...)
#define NG_LOG_ONCE_ERROR(...)
#endif // NG_CONSOLE_NOPRINT

// --- call this to disable Console functions ---
/*
#ifndef _DEBUG // limits to release window
ShowWindow(GetConsoleWindow(), SW_HIDE); // hides console
#define NG_CONSOLE_NOPRINT // disables unnecessary printing logic
#endif
*/
// ----------------------------------------------
