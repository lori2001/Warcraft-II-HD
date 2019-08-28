#pragma once
#include "SFML/System.hpp" // for sf::Clock

// to measure time
#include <chrono>
#include <ctime>

namespace ngin {
	class Timer {
	public:
		static void measureSysTime();
		static void measureDeltaTime();

		// returns true if system time was measured
		static bool getSysMeasured() { return sysTime_.tm_year; }
		// get system time as tm object
		static tm getSys() { return sysTime_; }
		// get system time in yyyy.mm.dd hh format as string
		static std::string getSysString() { return year_ + "." + mon_ + "." + day_ + " " + hour_ + ":" + min_ + ":" + sec_; }
		// get system date in yyyy.mm.dd format as string
		static std::string getSysYMDStr() { return year_ + "." + mon_ + "." + day_; }
		// get system time in h::mm:ss format as string
		static std::string getSysHMSStr() { return hour_ + ":" + min_ + ":" + sec_; }
		// get system time in hh:mm format as string
		static std::string getSysHMStr() { return hour_ + ":" + min_; }

		// get the delta time measured
		static float getDeltaTime() { return deltaTime_; }

	private:
		static tm sysTime_; // the system date and time at running

		// hold each important tm time value in a string
		static std::string year_;
		static std::string mon_;
		static std::string day_;
		static std::string hour_;
		static std::string min_;
		static std::string sec_;

		static sf::Clock appClock_; // measures application runtime
		static float deltaTime_; // delta time value for each frame
	};
}
