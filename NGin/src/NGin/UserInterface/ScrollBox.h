#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include "../System/Console.h"

// This UI Element has to be inherited in order to be used properly

namespace ngin {

	class ScrollBox : public ngin::UIElement {
	public:
		ScrollBox() : ScrollBox({ 1000, 1000 }, { 500, 500 }, { 150, 30 }, { 30, 150 }) {}
		// flips the X scroller size coordinates to read in the Y scroller
		ScrollBox(const sf::Vector2f& insideSize, const sf::Vector2f& outsideSize, const sf::Vector2f& XscrollerSize)
			: ScrollBox(insideSize, outsideSize, { XscrollerSize.x, XscrollerSize.y }, { XscrollerSize.y, XscrollerSize.x }){}
		ScrollBox(const sf::Vector2f& insideSize, const sf::Vector2f& outsideSize,
			const sf::Vector2f& XscrollerSize, const sf::Vector2f& YscrollerSize)
		{
			setInsideSize(insideSize);
			setOutsideSize(outsideSize);
			setXScrollerSize(XscrollerSize);
			setYScrollerSize(YscrollerSize);
			setPosition({0, 0});
		
			if (outsideSize.x > insideSize.x) {
				NG_LOG_WARN("Scrollbox nr.", getUIElementIndex(),
					" -- outsideSize.x should be smaller or equal to insideSize.x!");
			} 
			if (outsideSize.y > insideSize.y) {
				NG_LOG_WARN("Scrollbox nr.", getUIElementIndex(),
					" -- outsideSize.x should be smaller or equal to insideSize.x!");
			}
			if (outsideSize.x == insideSize.x) {
				XisUsed_ = false;  
			}
			if (outsideSize.y == insideSize.y) {
				YisUsed_ = false;
			}
		}

		void handleEvents(const sf::Event& event, const sf::Vector2f& mouse);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// add elements to scrollbox by this
		// arg1: an sfml rectangle
		// arg2: the position relative to the inside of scrollbox
		// -- positions outside of bounds will result in warning message and false return
		// -- makes ScrollBox responsible for drawing the object passed in
		bool addElement(sf::RectangleShape& rectangle, const sf::Vector2f& relativePosition);
		// add elements to scrollbox by this
		// arg1: an sfml text
		// arg2: the position relative to the inside of scrollbox
		// -- positions outside of bounds will result in warning message and false return
		// -- makes ScrollBox responsible for drawing the object passed in
		bool addElement(sf::Text& text, const sf::Vector2f& relativePosition);

		// -- converts object's global position to relative position
        // aka. object at position x and y will only be available if
        // is inside container + the insideSize expansion
		bool addElement(sf::Text& text);
		// -- converts object's global position to relative position
		// aka. object at position x and y will only be available if
		// is inside container + the insideSize expansion
		bool addElement(sf::RectangleShape& rectangle);

		// returns the index of the given subscribed element
		// if not found returns -1
		int getElementID(sf::Text& text) const;
		// returns the index of the given subscribed element
		// if not found returns -1
		int getElementID(sf::RectangleShape& rectangle) const;

		sf::Text* getTextWithID(int index) const { return subsTexts_[index]; }

		// deletes all elements off of subsRects_ vector
		void clearRectangles() { subsRects_.clear(); }
		// deletes all elements off of subsTexts_ vector
		void clearTexts() { subsTexts_.clear(); }
		// deletes all elements off of subsRects_ and subsTexts_ vector
		void clearElements() { clearRectangles(); clearTexts(); }

		void setXScrollerSize(const sf::Vector2f& size) { Xscroller_.setSize(size); }
		void setYScrollerSize(const sf::Vector2f& size) { Yscroller_.setSize(size); }
		void setInsideSize(const sf::Vector2f& insideSize) { insideSize_ = insideSize; }	
		void setOutsideSize(const sf::Vector2f& outsideSize) {
			outsideSize_ = outsideSize;
			container_.setSize(outsideSize);
		}
		// Composition:
		// background of outsideSize
		// scrollbar of Yscrollersize(next to background)
		// scrollbar of Xscrollersize(under background)
		void setTexture(const sf::Texture& texture);
		void setPosition(const sf::Vector2f& position);
		void setScrollSpeed(const float speedPercent) { scrollSpeed_ = speedPercent; }
		void setSelectColor(const sf::Color& color) {
			Yscroller_.setOutlineColor(color);
			Xscroller_.setOutlineColor(color);
		}

		bool XisActive() const { return XisActive_; }
		bool YisActive() const { return YisActive_; }
		bool isFocused() const { return isFocused_; }
		sf::Vector2f getScrollPercent() { return scrollPercent_; }
		sf::Vector2f getPosition() const { return container_.getPosition(); }
		sf::Vector2f getOutsideSize() const { return outsideSize_; }
		sf::Vector2f getInsideSize() const { return insideSize_; }
		// gets the global bounds of the container
		sf::FloatRect getGlobalBounds() { return container_.getGlobalBounds(); }

	private:
		// outsideSize_ < insideSize_
		sf::Vector2f insideSize_; // the hidden size of container
		sf::Vector2f outsideSize_; // the size of the container seen by user

		sf::RectangleShape container_;
		
		bool isFocused_ = false; // true when mouse is on container
		
		float selectThickness_ = -2.5F; // the thickenss of the outline of selected items
		
		sf::Vector2f savedMousePosition_;
		sf::Vector2f scrollPercent_; // the offset of scrolling in percentage
		float scrollSpeed_ = 0.15F; // scroll speed for mouse wheel

		sf::RectangleShape Xscroller_; // bottom scroller
		bool XisUsed_ = true;
		bool XisSelected_ = false;
		bool XisActive_ = false;
		bool XisPressed_ = false;
		
		sf::RectangleShape Yscroller_; // right scroller
		bool YisUsed_ = true;
		bool YisSelected_ = false;
		bool YisActive_ = false;
		bool YisPressed_ = false;

		bool isDisabled_ = false;

		// rectangle subscriptions
		std::vector<sf::RectangleShape*> subsRects_;
		// contains position relative to scrollbox inside
		std::vector<sf::Vector2f> subsRectPositions_;

		// rectangle subscriptions
		std::vector<sf::Text*> subsTexts_;
		// contains position relative to scrollbox inside
		std::vector<sf::Vector2f> subsTextPositions_;
	};
}