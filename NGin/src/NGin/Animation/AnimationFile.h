#pragma once
#include "SFML/Graphics.hpp"

#include "../System/Timer.h"

namespace ngin {
	// Animation using Files
	class AnimationFile {
	public:
		AnimationFile() = default;
		AnimationFile(const float secPerFrame) {
			secPerFrame_ = secPerFrame;
		}
		void update(const std::vector<std::shared_ptr<sf::Texture>>& textureVector);

		void setSecondsPerFrame(const float secPerFrame) { secPerFrame_ = secPerFrame; }

		sf::Texture* getTexturePointer() const { return texture_; }
	private:
		float secsPassed_ = 0.0F;
		float secPerFrame_ = 0.0F;

		sf::Texture *texture_ = 0;
		int iFrame = 0;
	};
}