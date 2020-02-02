#include "ScrollBox.h"
#include "Cursor.h"

namespace ngin {

	void ScrollBox::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		if (!isDisabled_)
		{
			isFocused_ = container_.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));

			XisActive_ = false;
			XisSelected_ = Xscroller_.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));

			YisActive_ = false;
			YisSelected_ = Yscroller_.getGlobalBounds().intersects(sf::FloatRect(mouse, { 1,1 }));

			/// --- Scroll Logic START ----------------------------------------
			// TODO: scroll by wheel logic
			if (isFocused_ && event.type == sf::Event::MouseWheelMoved) {
				if (YisUsed_) {
					scrollPercent_.y += event.mouseWheel.delta * (-1) * scrollSpeed_;
					if (scrollPercent_.y > 1) scrollPercent_.y = 1;
					else if (scrollPercent_.y < 0) scrollPercent_.y = 0;

					setPosition(getPosition());
				}
			}

			// move by scrollers
			if (XisPressed_) {
				float deltaMouseX = mouse.x - savedMousePosition_.x;
				savedMousePosition_.x = mouse.x;

				float minPosition = container_.getPosition().x;
				float maxPosition =
					container_.getPosition().x +
					container_.getGlobalBounds().width -
					Xscroller_.getGlobalBounds().width;
				
				if (YisUsed_) {
					// avoid scroller collision
					maxPosition -= Yscroller_.getGlobalBounds().width;
				}

				float newPosition = Xscroller_.getPosition().x + deltaMouseX;

				scrollPercent_.x = (newPosition - minPosition) / (maxPosition - minPosition);
				if (scrollPercent_.x > 1) scrollPercent_.x = 1;
				else if (scrollPercent_.x < 0) scrollPercent_.x = 0;
				
				// set the position of scrollers properly
				setPosition(getPosition());
			}
			else if (YisPressed_) {
				float deltaMouseY = mouse.y - savedMousePosition_.y;
				savedMousePosition_.y = mouse.y;

				float minPosition = container_.getPosition().y;
				float maxPosition =
					container_.getPosition().y +
					container_.getGlobalBounds().height -
					Yscroller_.getGlobalBounds().height;
				
				if (XisUsed_) {
					// avoid scroller collision
					maxPosition -= Xscroller_.getGlobalBounds().height;
				}

				float newPosition = Yscroller_.getPosition().y + deltaMouseY;

				scrollPercent_.y = (newPosition - minPosition) / (maxPosition - minPosition);
				if (scrollPercent_.y > 1) scrollPercent_.y = 1;
				else if (scrollPercent_.y < 0) scrollPercent_.y = 0;

				// set the position of scrollers properly
				setPosition(getPosition());
			}
			/// --- Scroll Logic END ------------------------------------------

			// --- X scroller START -------------------------------------------
			if (XisSelected_) {
				Xscroller_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.type == sf::Event::MouseButtonPressed)
					{
						XisPressed_ = true;

						// used to caluclate offset when moving scrollers
						savedMousePosition_ = mouse;

						// audio feedback for pressing
						Cursor::playSound();

						// create the "pressed in" visual feedback
						Xscroller_.setTextureRect({
							static_cast<int>(Xscroller_.getSize().x),
							static_cast<int>(outsideSize_.y),
							static_cast<int>(Xscroller_.getSize().x),
							static_cast<int>(Xscroller_.getSize().y) });
					}
					else if (XisPressed_ && event.type == sf::Event::MouseButtonReleased
						&& blockingException_ == -1)
					{
						XisActive_ = true;
					}
				}
			}
			else if(!XisPressed_) { // if !XisSelected_ && !XisPressed_
				Xscroller_.setOutlineThickness(0);
			}

			if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
			{
				XisPressed_ = false;

				Xscroller_.setTextureRect({
					0,
					static_cast<int>(outsideSize_.y),
					static_cast<int>(Xscroller_.getSize().x),
					static_cast<int>(Xscroller_.getSize().y) });
			}
			// --- X scroller END ---------------------------------------------

			// --- Y scroller START -------------------------------------------
			if (YisSelected_) {
				Yscroller_.setOutlineThickness(selectThickness_);

				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.type == sf::Event::MouseButtonPressed)
					{
						YisPressed_ = true;

						// used to caluclate offset when moving scrollers
						savedMousePosition_ = mouse;

						// audio feedback for pressing
						Cursor::playSound();

						// create the "pressed in" visual feedback
						Yscroller_.setTextureRect({
							static_cast<int>(outsideSize_.x),
							static_cast<int>(Yscroller_.getSize().y),
							static_cast<int>(Yscroller_.getSize().x),
							static_cast<int>(Yscroller_.getSize().y) });
					}
					else if (YisPressed_ && event.type == sf::Event::MouseButtonReleased
						&& blockingException_ == -1)
					{
						YisActive_ = true;
					}
				}
			}
			else if(!YisPressed_) { // if !YisSelected_ and !YisPressed_
				Yscroller_.setOutlineThickness(0);
			}

			// If left mouse button released or unselected...
			if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
			{
				YisPressed_ = false;
				Yscroller_.setTextureRect({
					static_cast<int>(outsideSize_.x),
					0,
					static_cast<int>(Yscroller_.getSize().x),
					static_cast<int>(Yscroller_.getSize().y) });
			}
			// --- Y scroller END ---------------------------------------------
		}
	}

	void ScrollBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(container_);

		if (XisUsed_) {
			target.draw(Xscroller_);
		}

		if (YisUsed_) {
			target.draw(Yscroller_);
		}

		for (auto it : subsRects_) {
			// draw only if container "contains" the rectangle
			if (container_.getPosition().x < it->getPosition().x &&
				container_.getPosition().y < it->getPosition().y &&
				container_.getPosition().x + container_.getGlobalBounds().width >
				it->getPosition().x + it->getGlobalBounds().width &&
				container_.getPosition().y + container_.getGlobalBounds().height >
				it->getPosition().y + it->getGlobalBounds().height)
			{
				target.draw(*it);
			}
		}

		for (auto it : subsTexts_) {
			// draw only if container "contains" the text
			if (container_.getPosition().x < it->getPosition().x &&
				container_.getPosition().y < it->getPosition().y &&
				container_.getPosition().x + container_.getGlobalBounds().width >
				it->getPosition().x + it->getGlobalBounds().width &&
				container_.getPosition().y + container_.getGlobalBounds().height >
				it->getPosition().y + it->getGlobalBounds().height)
			{
				target.draw(*it);
			}
		}
	}

	bool ScrollBox::addElement(sf::RectangleShape& rectangle, const sf::Vector2f& relativePosition)
	{
		subsRects_.push_back(&rectangle);
		subsRectPositions_.push_back({relativePosition});

		if (relativePosition.x + rectangle.getGlobalBounds().width  > insideSize_.x ||
			relativePosition.y + rectangle.getGlobalBounds().height > insideSize_.y)
		{
			NG_LOG_WARN("Rectangle nr.", subsRects_.size() - 1,
				" subscribed to scrollbox nr.", getUIElementIndex(),
				" with position{", relativePosition.x, ", ", relativePosition.y, "} out of reach");

			return false;
		}

		rectangle.setPosition({
			container_.getPosition().x + relativePosition.x,
			container_.getPosition().y + relativePosition.y
		});

		return true;
	}

	bool ScrollBox::addElement(sf::Text& text, const sf::Vector2f& relativePosition)
	{
		subsTexts_.push_back(&text);
		subsTextPositions_.push_back({ relativePosition });

		// TODO: FIX THIS SHIT
		if (relativePosition.x + text.getGlobalBounds().width > insideSize_.x ||
			relativePosition.y +
			text.getGlobalBounds().height -
			text.getGlobalBounds().top > insideSize_.y)
		{
			NG_LOG_WARN("Text nr.", subsTexts_.size() - 1,
				" subscribed to scrollbox nr.", getUIElementIndex(),
				" with position{", relativePosition.x, ", ", relativePosition.y, "} out of reach");

			return false;
		}

		text.setPosition({
			container_.getPosition().x + relativePosition.x,
			container_.getPosition().y + relativePosition.y
			});

		return true;
	}

	bool ScrollBox::addElement(sf::Text& text)
	{
		sf::Vector2f relativePosition = {
			text.getPosition().x - container_.getPosition().x,
			text.getPosition().y - container_.getPosition().y,
		};
		return addElement(text, relativePosition);
	}

	bool ScrollBox::addElement(sf::RectangleShape& rectangle)
	{
		sf::Vector2f relativePosition = {
			rectangle.getPosition().x - container_.getPosition().x,
			rectangle.getPosition().y - container_.getPosition().y,
		};
		return addElement(rectangle, relativePosition);
	}

	int ScrollBox::getElementID(sf::Text& text) const
	{
		// iterate through each pointer
		for (int i = 0; i < subsTexts_.size(); i++)
		{
			// if ID of pointer is found
			if (subsTexts_[i] == &text) {
				return i;
			}
		}
		return -1; // not found
	}

	int ScrollBox::getElementID(sf::RectangleShape& rectangle) const
	{
		// iterate through each pointer
		for (int i = 0; i < subsRects_.size(); i++)
		{
			// if ID of pointer is found
			if (subsRects_[i] == &rectangle) {
				return i;
			}
		}
		return -1; // not found
	}

	void ScrollBox::setTexture(const sf::Texture& texture)
	{
		container_.setTexture(&texture);
		Xscroller_.setTexture(&texture);
		Yscroller_.setTexture(&texture);

		container_.setTextureRect({
			0,
			0,
			static_cast<int>(outsideSize_.x),
			static_cast<int>(outsideSize_.y) });

		Yscroller_.setTextureRect({
			static_cast<int>(outsideSize_.x),
			0,
			static_cast<int>(Yscroller_.getSize().x),
			static_cast<int>(Yscroller_.getSize().y) });

		Xscroller_.setTextureRect({
			0,
			static_cast<int>(outsideSize_.y),
			static_cast<int>(Xscroller_.getSize().x),
			static_cast<int>(Xscroller_.getSize().y) });
	}

	void ScrollBox::setPosition(const sf::Vector2f& position)
	{
		container_.setPosition(position);

		sf::Vector2f Xoffset;
		sf::Vector2f Yoffset;

		Xoffset.y = container_.getGlobalBounds().height - Xscroller_.getGlobalBounds().height;
		if (!YisUsed_) {
			Xoffset.x = scrollPercent_.x *
				(container_.getGlobalBounds().width - Xscroller_.getGlobalBounds().width);
		}
		else {
			Xoffset.x = scrollPercent_.x *
				(container_.getGlobalBounds().width -
				 Xscroller_.getGlobalBounds().width -
				 Yscroller_.getGlobalBounds().width);
		}

		Yoffset.x = container_.getGlobalBounds().width - Yscroller_.getGlobalBounds().width;
		if (!XisUsed_) {
			Yoffset.y = scrollPercent_.y *
				(container_.getGlobalBounds().height - Yscroller_.getGlobalBounds().height);
		}
		else {
			Yoffset.y = scrollPercent_.y *
				(container_.getGlobalBounds().height -
				 Yscroller_.getGlobalBounds().height - 
				 Xscroller_.getGlobalBounds().height);
		}

		// bottom
		Xscroller_.setPosition({ position.x + Xoffset.x, position.y + Xoffset.y });
		// right side
		Yscroller_.setPosition({ position.x + Yoffset.x, position.y + Yoffset.y });

		for (int i = 0; i < static_cast<int>(subsRects_.size()); i++) {
			subsRects_[i]->setPosition({
				position.x + subsRectPositions_[i].x - (scrollPercent_.x * (insideSize_.x - outsideSize_.x)),
				position.y + subsRectPositions_[i].y - (scrollPercent_.y * (insideSize_.y - outsideSize_.y))
			});
		}
		for (int i = 0; i < static_cast<int>(subsTexts_.size()); i++) {
			subsTexts_[i]->setPosition({
				position.x + subsTextPositions_[i].x - (scrollPercent_.x * (insideSize_.x - outsideSize_.x)),
				position.y + subsTextPositions_[i].y - (scrollPercent_.y * (insideSize_.y - outsideSize_.y))
			});
		}
	}
}