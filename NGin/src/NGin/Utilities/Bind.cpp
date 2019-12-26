#include "Bind.h"
#include "../System/Console.h"
#include "../Levels/MainLevel.h"

namespace ngin {

	std::unordered_map<std::string, Bindables::Binder> Bindables::bindables;
	unsigned long int Bindables::lastLoopCicle_ = 0;

	void Bindables::create(const std::string key, const sf::Vector2f& positionOfBindable)
	{
		bindables.insert({ key, {positionOfBindable, positionOfBindable} });
	}

	bool Bindables::bindPosition(sf::Vector2f& position, const std::string& keyOfBindable, const sf::Vector2f& positionOfBindable)
	{
		const auto search = bindables.find(keyOfBindable); // search

		// if something is found
		if (search != bindables.end())
		{
			// only once in a loop cicle
			if (lastLoopCicle_ != ngin::MainLevel::getLoopCicleCount())
			{
				lastLoopCicle_ = ngin::MainLevel::getLoopCicleCount();
				// update the saved position to the current one
				search->second.lastPosition_ = search->second.position_;
				search->second.position_ = positionOfBindable;
			}

			// calculate the amount of movement that has happened
			sf::Vector2f offset;
			offset.x = search->second.position_.x - search->second.lastPosition_.x;
			offset.y = search->second.position_.y - search->second.lastPosition_.y;

			// move shape with calculated offset values
			position.x += offset.x;
			position.y += offset.y;

			return true;
		}
		else // if nothing is found
		{
			NG_LOG_WARN("No bindable object with key '", keyOfBindable, "' has been found!");
			return false;
		}
	}

}