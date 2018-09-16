#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

namespace UI
{
	class TextHolder : public sf::Drawable
	{
	private:
		sf::Vector2f size{365, 32}; // the default size of a textholder
		sf::RectangleShape sprite{ size }; 

		sf::Text maintext; // text above the textholder
		sf::Text cursor; // just a | to show off cursor position
		sf::Text text; // text the object contains

		bool isSelected = false; // true when the mouse is hovered on the TextHolder
		bool isActive = false; // true when string is under editing
		bool hasChanged = false; // true if the string has been modified

		unsigned int textsize = 32; // the default size of texts
		sf::Vector2f lastscale; //holds the last scale in case of change of resolution
	public:
		TextHolder()
		{
			sprite.setOrigin(sf::Vector2f(float(size.x / 2), float(size.y / 2)));
			sprite.setOutlineColor(sf::Color::Yellow);
			text.setFillColor(sf::Color::Yellow);
			maintext.setFillColor(sf::Color::Yellow);
		}
		TextHolder(const std::string text) : TextHolder()
		{
			maintext.setString(text);

			this->maintext.setOrigin(this->maintext.getLocalBounds().left + this->maintext.getLocalBounds().width / 2.0f,
				this->maintext.getLocalBounds().top + this->maintext.getLocalBounds().height / 2.0f);
		}
		TextHolder(const std::string text, const sf::Vector2f &position) : TextHolder(text)
		{
			sprite.setPosition(position);
			this->text.setPosition(position);
			maintext.setPosition(sf::Vector2f(position.x, position.y - size.y * sprite.getScale().y));
			cursor.setPosition(sf::Vector2f(position.x + this->text.getLocalBounds().width / 2 + 2 * sprite.getScale().x, position.y));
		}
		void setSelected(const sf::Vector2f & mouse);
		void handleInput(const sf::Event &event, sf::Sound & pressbutton);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//setters
		void setTexture(const sf::Texture &texture, const sf::Font &font);
		void setPosition(const sf::Vector2f &position);
		void setScale(const sf::Vector2f &scale);
		void setString(const std::string & text);
		void setMaintext(const std::string & text);
		void setChanged(const bool & hasChanged) { this->hasChanged = hasChanged; }
		
		//getters
		bool getChanged() const { return hasChanged; }
		sf::Vector2f getScale() const { return sprite.getScale(); }
		sf::Vector2f getPosition() const { return sprite.getPosition(); }
		sf::Vector2f getSize() const { return size; }
		std::string getString() const { return text.getString(); }
	};
}