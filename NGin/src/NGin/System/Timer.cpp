#include "Timer.h"

namespace ngin {
	tm Timer::sysTime_; // defaults all values to 0
	sf::Clock Timer::appClock_;
	float Timer::deltaTime_ = 0;

	std::string Timer::year_;
	std::string Timer::mon_;
	std::string Timer::day_;
	std::string Timer::hour_;
	std::string Timer::min_;
	std::string Timer::sec_;

	void Timer::measureSysTime()
	{
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		std::time_t start_time = std::chrono::system_clock::to_time_t(now);
		localtime_s(&sysTime_, &start_time);

		/*converts time numbers into calendaristic-format*/
		sysTime_.tm_year += 1900;
		sysTime_.tm_mon += 1;

		year_ = std::to_string(sysTime_.tm_year);

		if (sysTime_.tm_mon < 10) mon_ = "0" + std::to_string(sysTime_.tm_mon);
		else mon_ = std::to_string(sysTime_.tm_mon);

		if (sysTime_.tm_mday < 10) day_ = "0" + std::to_string(sysTime_.tm_mday);
		else day_ = std::to_string(sysTime_.tm_mday);

		if (sysTime_.tm_hour < 10) hour_ = "0" + std::to_string(sysTime_.tm_hour);
		else hour_ = std::to_string(sysTime_.tm_hour);
		
		if (sysTime_.tm_min < 10) min_ = "0" + std::to_string(sysTime_.tm_min);
		else min_ = std::to_string(sysTime_.tm_min);

		if (sysTime_.tm_sec < 10) sec_ = "0" + std::to_string(sysTime_.tm_sec);
		else sec_ = std::to_string(sysTime_.tm_sec);
	}
	void Timer::measureDeltaTime()
	{
		// Resets clock and times each frame
		deltaTime_ = appClock_.getElapsedTime().asSeconds();
		appClock_.restart();
	}
}
