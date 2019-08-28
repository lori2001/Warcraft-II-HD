#include "AnimationFile.h"

namespace ngin {
	void AnimationFile::update(const std::vector<std::shared_ptr<sf::Texture>>& textureVector)
	{
		secsPassed_ += Timer::getDeltaTime();

		if (secsPassed_ > secPerFrame_) {
			secsPassed_ -= secPerFrame_;

			// Makes up for big delays
			if (secsPassed_ > secPerFrame_)
				secsPassed_ = 0;

			if (++iFrame >= int(textureVector.size()))
				iFrame = 0;
		}

		texture_ = textureVector[iFrame].get();
	}
}