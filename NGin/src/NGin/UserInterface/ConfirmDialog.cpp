#include "ConfirmDialog.h"
#include "../Levels/Main.h"

namespace ng
{
	void ConfirmDialog::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
	{
		response_ = RESPONSE::RESPONSE_NONE;

		if (isActive_)
		{
			switch (type_)
			{
			case DIALOG_TYPE::DIALOG_YES_OR_CLOSE:
				okButton_.handleEvents(event, mouse);

				if (okButton_.isActive()) {
					response_ = RESPONSE::RESPONSE_OK;
				}
			case DIALOG_TYPE::DIALOG_CLOSE_ONLY:
				closeButton_.handleEvents(event, mouse);

				if (closeButton_.isActive()) {
					response_ = RESPONSE::RESPONSE_CLOSE;
				}
				break;
			}

			if (response_ != RESPONSE::RESPONSE_NONE) {
				isActive_ = false;
			}
		}
	}
	void ConfirmDialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (isActive_)
		{
			target.draw(shape_);

			switch (type_)
			{
			case DIALOG_TYPE::DIALOG_YES_OR_CLOSE:
				target.draw(okButton_);

			case DIALOG_TYPE::DIALOG_CLOSE_ONLY:
				target.draw(closeButton_);
				break;
			}

			target.draw(text_);
		}
	}
	void ConfirmDialog::drawInWindow(const std::string& windowName)
	{
		sf::Vector2f proportions = {
			static_cast<float>(sf::VideoMode::getDesktopMode().width)
			/ ng::Main::getWindowView().getSize().x,
			static_cast<float>(sf::VideoMode::getDesktopMode().height)
			/ ng::Main::getWindowView().getSize().y
		};

		sf::View view{ {0.0F, 0.0F,
			shape_.getGlobalBounds().width,
			shape_.getGlobalBounds().height} };

		sf::RenderWindow window
		{ {static_cast<unsigned>(shape_.getGlobalBounds().width * proportions.x),
			static_cast<unsigned>(shape_.getGlobalBounds().height * proportions.y)},
			windowName,
			sf::Style::Titlebar | sf::Style::Close
		};
		window.setView(view);

		const sf::Vector2f position = getPosition();
		setPosition({ 0.0F, 0.0F });

		// inherit main window icon (if there is any)
		if(ng::Main::getWinIconPtr() != nullptr)
			window.setIcon(
				ng::Main::getWinIconPtr()->getSize().x, 
				ng::Main::getWinIconPtr()->getSize().y,
				ng::Main::getWinIconPtr()->getPixelsPtr());

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				ng::Cursor::followMouse(window);

				handleEvents(event, ng::Cursor::getPosition());

				if (event.type == sf::Event::Closed || isActive_ == false) {
					isActive_ = false;
					window.close();
				}
			}

			window.clear();
			window.draw(*this);
			ng::Cursor::draw(window);
			window.display();
		}

		setPosition(position);
	}
	void ConfirmDialog::setPosition(const sf::Vector2f& position)
	{
		shape_.setPosition(position);

		if (type_ == DIALOG_TYPE::DIALOG_YES_OR_CLOSE)
		{
			closeButton_.setPosition({ shape_.getPosition().x + buttonOffset_.x,
				shape_.getPosition().y + shape_.getGlobalBounds().height
				- closeButton_.getGlobalBounds().height - buttonOffset_.y });

			okButton_.setPosition({ shape_.getPosition().x + shape_.getGlobalBounds().width
				- okButton_.getGlobalBounds().width - buttonOffset_.x,
				shape_.getPosition().y + shape_.getGlobalBounds().height
				- okButton_.getGlobalBounds().height - buttonOffset_.y });
		} 
		else if(type_ == DIALOG_TYPE::DIALOG_CLOSE_ONLY)
		{
			closeButton_.setPosition({
				ng::getCenterOf(shape_).x - closeButton_.getGlobalBounds().width / 2,
				shape_.getPosition().y + shape_.getGlobalBounds().height
				- closeButton_.getGlobalBounds().height - buttonOffset_.y });
		}

		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setButtonSize(const sf::Vector2f& size)
	{
		okButton_.setSize(size);
		closeButton_.setSize(size);
	}
	void ConfirmDialog::setSize(const sf::Vector2f& size)
	{
		shape_.setSize(size);
		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setButtonTexture(const ng::TexturePtr texture)
	{
		buttonTexture_ = texture;
		okButton_.setTexture(buttonTexture_);
		closeButton_.setTexture(buttonTexture_);
	}
	void ConfirmDialog::setShapeTexture(const ng::TexturePtr texture)
	{
		shapeTexture_ = texture;
		shape_.setTexture(&*shapeTexture_);
	}
	void ConfirmDialog::setTextures(const ng::TexturePtr buttonTexture,
		const ng::TexturePtr shapeTexture)
	{
		setButtonTexture(buttonTexture);
		setShapeTexture(shapeTexture);
	}
	void ConfirmDialog::setButtonOffset(const sf::Vector2f& offset)
	{
		buttonOffset_ = offset;
		setPosition(getPosition());
	}
	void ConfirmDialog::setString(const std::string& string)
	{
		text_.setString(string);
		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setTextYOffset(const float textYOffset)
	{
		textYOffset_ = textYOffset;
		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setFont(const ng::FontPtr font)
	{
		font_ = font;
		okButton_.setFont(font_);
		closeButton_.setFont(font_);
		text_.setFont(*font_);
		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setButtonTextColor(const sf::Color color)
	{
		okButton_.setTextColor(color);
		closeButton_.setTextColor(color);
	}
	void ConfirmDialog::setCharacterSize(const unsigned characterSize)
	{
		okButton_.setCharacterSize(characterSize);
		closeButton_.setCharacterSize(characterSize);
		text_.setCharacterSize(characterSize);
		ng::centerTextInShape(text_, shape_, textYOffset_);
	}
	void ConfirmDialog::setShapeScale(const sf::Vector2f& scale)
	{
		shape_.setScale(scale);
	}
	void ConfirmDialog::setButtonScale(const sf::Vector2f& buttonScale)
	{
		okButton_.setScale(buttonScale);
		closeButton_.setScale(buttonScale);
	}
	void ConfirmDialog::setTextColor(const sf::Color& color) {
		okButton_.setTextColor(color);
		closeButton_.setTextColor(color);
		text_.setFillColor(color);
	}
	void ConfirmDialog::setSelectColor(const sf::Color& color) {
		okButton_.setSelectColor(color);
		closeButton_.setSelectColor(color);
	}
}
