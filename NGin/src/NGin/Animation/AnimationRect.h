#pragma once
#include "SFML/Graphics.hpp"

// TODO: Complete and test this shit!

namespace ngin {
	// Animation using rectangles
	class AnimationRect {
	public:
		AnimationRect() = default;
		AnimationRect(const sf::IntRect textureRect,
			const sf::Vector2i nFrames,
			const float secPerFrame,
			const sf::Texture& texture) {

		}

		void setTexturePosition();
		void setTextureSize();
		void setNumberOfFrames();
		void setSecondsPerFrame();
		void setTexture();

	private:
		float secPerFrame_ = 0.0F;
		std::shared_ptr<sf::Texture> texture_;
		std::vector<sf::IntRect> frames_;
		sf::Vector2i iFrame = {0, 0};
	};
}
